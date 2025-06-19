#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

enum {MAX_FD = 65535, RBUF_SIZE = 1000};

int max_fd;
int next_id;

int ids[MAX_FD + 1];
char* pend[MAX_FD + 1];

fd_set master, rset, wset;

char rbuf[RBUF_SIZE + 1];
char wbuf[64];



void fatal(void) {
  write(2, "Fatal error\n", 12);
  exit(1);
}

int extract_message(char **buf, char **msg)
{
    char	*newbuf;
    int	i;

    *msg = 0;
    if (*buf == 0)
        return (0);
    i = 0;
    while ((*buf)[i])
    {
        if ((*buf)[i] == '\n')
        {
            newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
            if (newbuf == 0)
                return (-1);
            strcpy(newbuf, *buf + i + 1);
            *msg = *buf;
            (*msg)[i + 1] = 0;
            *buf = newbuf;
            return (1);
        }
        i++;
    }
    return (0);
}

char *str_join(char *buf, char *add)
{
    char	*newbuf;
    int		len;

    if (buf == 0)
        len = 0;
    else
        len = strlen(buf);
    newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
    if (newbuf == 0)
        return (0);
    newbuf[0] = 0;
    if (buf != 0)
        strcat(newbuf, buf);
    free(buf);
    strcat(newbuf, add);
    return (newbuf);
}

void broadcast(int except_fd, char*msg) {
  for(int fd = 0; fd <= max_fd; ++fd) {
    if (FD_ISSET(fd, &wset) && fd != except_fd)
      send(fd, msg, strlen(msg), 0);
  }
}

void add_client(int fd) {
  max_fd = (fd > max_fd) ? fd : max_fd;
  FD_SET(fd, &master);
  pend[fd] = NULL;
  ids[fd] = next_id++;
  sprintf(wbuf, "server: client %d just arrived\n", ids[fd]);
  broadcast(fd, wbuf);
}

void drop_client(int fd) {
  sprintf(wbuf, "server: client %d just left\n", ids[fd]);
  broadcast(fd, wbuf);
  free(pend[fd]);
  pend[fd] = NULL;
  FD_CLR(fd, &master);
}

void flush_message(int fd) {
  char* msg;
  int ret;
  while((ret = extract_message(&pend[fd], &msg))) {
    if (ret == -1)
      fatal();
    sprintf(wbuf, "client %d: ", ids[fd]);
    broadcast(fd, wbuf);
    broadcast(fd, msg);
  }
}

int get_socket(char* port) {
  FD_ZERO(&master);
  struct sockaddr_in servaddr;
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1)
    fatal();

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
  servaddr.sin_port = htons(atoi(port));
  //bind and listen
  if (bind(s, (const struct sockaddr*) &servaddr, sizeof(servaddr)) || listen(s, 10))
    fatal();
  FD_SET(s, &master);
  max_fd = s;
  return (s);
}

int main(int ac, char**avc) {
  if (ac != 2) {
    write(2, "Wrong number of arguments\n", 26);
    return (1);
  }

  FD_ZERO(&master);
  int srv = get_socket(avc[1]);

  while(1) {
    rset = master;
    wset = master;

    if (select(max_fd + 1, &rset, &wset, NULL, NULL) == -1)
      fatal();

    for (int fd = 0; fd <= max_fd; ++fd) {
      if (!FD_ISSET(fd, &rset))
        continue;

      if (fd == srv) {
        int cfd = accept(srv, NULL, NULL);
        if (cfd >= 0)
          add_client(cfd);
      }
      else {
        int n = recv(fd, rbuf, RBUF_SIZE, 0);
        if (n <= 0)
          drop_client(fd);
        else {
          rbuf[n] = '\0';
          pend[fd] = str_join(pend[fd], rbuf);
          if (!pend[fd])
            fatal();
          flush_message(fd);
        }
      }
    }
  }
  return (0);
}