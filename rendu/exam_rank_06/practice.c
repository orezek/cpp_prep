#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

// close fd!!!!
enum{MAX_FD = 65535, RBUF_SIZE = 1000};

int ids[MAX_FD];
char *pend[MAX_FD];

int max_fd;
int next_id;

char rbuf[RBUF_SIZE];
char wbuf[64];

fd_set master, rset, wset;

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


void broadcast(int except_fd, char* msg)
{
  for (int fd = 0; fd <= max_fd; ++fd)
  {
      if (FD_ISSET(fd, &wset) && except_fd != fd)
        send(fd, msg, strlen(msg),0);
  }
}

void add_client(int fd)
{
    max_fd = (max_fd < fd) ? fd : max_fd;
    FD_SET(fd, &master);
    ids[fd] = next_id++;
    pend[fd] = NULL;
    sprintf(wbuf, "server: client %d just arrived\n", ids[fd]);
    broadcast(fd, wbuf);
}

void drop_client(int fd)
{
    sprintf(wbuf, "server: client %d just left\n", ids[fd]);
    broadcast(fd, wbuf);
    free(pend[fd]);
    pend[fd] = NULL;
    FD_CLR(fd, &master);
    close(fd);
}

void flush_messages(int fd)
{
  char* msg;
  int ret;
  while((ret = extract_message(&pend[fd], &msg)))
  {
    if (ret == -1)
      fatal();
    sprintf(wbuf, "client %d: ", ids[fd]);
    broadcast(fd, wbuf);
    broadcast(fd, msg);
  }
}

int get_socket(char* port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
      fatal();
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
    servaddr.sin_port = htons(atoi(port));

    if(bind(sockfd,  (const struct sockaddr *)&servaddr, sizeof(servaddr)) || listen(sockfd, 128) == -1)
      fatal();

    max_fd = sockfd;
    FD_SET(sockfd, &master);
    return (sockfd);
}

int main(int ac, char** avc)
{
  if (ac != 2)
  {
      write(2,"Wrong number of arguments\n", 26);
      return (1);
  }

  FD_ZERO(&master);
  int socket = get_socket(avc[1]);

  while(1)
  {
    rset = master;
    wset = master;
    if (select(max_fd + 1, &rset, &wset, NULL, NULL) == -1)
      fatal();

    for (int fd = 0; fd <= max_fd; ++fd)
    {
      if (!FD_ISSET(fd, &rset))
          continue;
      if (socket == fd)
      {
        int cfd = accept(socket, NULL, NULL);
        if (cfd > 0)
          add_client(cfd);
      }
      else
      {
        int n = recv(fd, rbuf, RBUF_SIZE, 0);
        if (n <= 0)
          drop_client(fd);
        else
        {
          rbuf[n] = '\0';
          pend[fd] = str_join(pend[fd], rbuf);
          if (!pend[fd])
            fatal();
          flush_messages(fd);
        }
      }
    }
  }
  return (0);
}
















