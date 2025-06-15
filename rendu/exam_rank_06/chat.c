/* ************************************************************************** */
/*                                                                            */
/*                            mini_serv.c                                     */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

/* ───────── constants without #define ───────── */
enum { MAX_FD = 65535, RBUF_SIZE = 1000 };

/* ───────── global state ───────── */
static int      max_fd;                 /* highest descriptor in use           */
static int      next_id;                /* next sequential client ID           */
static int      ids[MAX_FD + 1];        /* ids[fd] -> client id                */
static char    *pend[MAX_FD + 1];       /* un-delivered data per fd            */
static fd_set   master, rset, wset;     /* descriptor sets                     */

static char     rbuf[RBUF_SIZE + 1];
static char     wbuf[64];

/* ───────── fatal helper ───────── */
static void fatal(void)
{
    write(2, "Fatal error\n", 12);
    exit(1);
}

/* ───────── helpers borrowed from provided main.c ───────── */
int extract_message(char **buf, char **msg)
{
    char *newbuf;
    int   i;

    *msg = 0;
    if (*buf == 0)
        return (0);
    i = 0;
    while ((*buf)[i])
    {
        if ((*buf)[i] == '\n')
        {
            newbuf = calloc(1, strlen(*buf + i + 1) + 1);
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
    char *newbuf;
    int   len = buf ? strlen(buf) : 0;

    newbuf = malloc(len + strlen(add) + 1);
    if (newbuf == 0)
        return (0);
    newbuf[0] = 0;
    if (buf)
        strcat(newbuf, buf);
    free(buf);
    strcat(newbuf, add);
    return (newbuf);
}
/* ───────── end borrowed helpers ───────── */

/* ───────── broadcast utility ───────── */
static void broadcast(int except_fd, const char *msg)
{
    for (int fd = 0; fd <= max_fd; ++fd)
        if (FD_ISSET(fd, &wset) && fd != except_fd)
            send(fd, msg, strlen(msg), 0);
}

/* ───────── per-client bookkeeping ───────── */
static void add_client(int fd)
{
    max_fd  = (fd > max_fd) ? fd : max_fd;
    ids[fd] = next_id++;
    pend[fd] = NULL;
    FD_SET(fd, &master);

    sprintf(wbuf, "server: client %d just arrived\n", ids[fd]);
    broadcast(fd, wbuf);
}

static void drop_client(int fd)
{
    sprintf(wbuf, "server: client %d just left\n", ids[fd]);
    broadcast(fd, wbuf);

    free(pend[fd]);
    pend[fd] = NULL;
    FD_CLR(fd, &master);
    close(fd);
}

/* ───────── flush messages already received from a client ───────── */
static void flush_messages(int fd)
{
    char *msg;
    int   ret;

    while ((ret = extract_message(&pend[fd], &msg)))
    {
        if (ret == -1)
            fatal();
        sprintf(wbuf, "client %d: ", ids[fd]);
        broadcast(fd, wbuf);
        broadcast(fd, msg);
        free(msg);
    }
}

/* ───────── server socket setup ───────── */
static int open_listening_socket(const char *port)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
        fatal();

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family      = AF_INET;
    sa.sin_addr.s_addr = htonl(2130706433);      /* 127.0.0.1            */
    sa.sin_port        = htons(atoi(port));

    if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) || listen(s, SOMAXCONN))
        fatal();

    FD_SET(s, &master);
    max_fd = s;
    return s;
}

/* ───────── main event loop ───────── */
int main(int ac, char **av)
{
    if (ac != 2)
    {
        write(2, "Wrong number of arguments\n", 26);
        return (1);
    }

    FD_ZERO(&master);
    int srv = open_listening_socket(av[1]);

    while (1)
    {
        rset = master;
        wset = master;

        if (select(max_fd + 1, &rset, &wset, NULL, NULL) < 0)
            fatal();

        for (int fd = 0; fd <= max_fd; ++fd)
        {
            if (!FD_ISSET(fd, &rset))
                continue;

            if (fd == srv)
            {
                int cfd = accept(srv, NULL, NULL);
                if (cfd >= 0)
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
