#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/select.h>

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

int ids[65536];
char *msgs[65536];

fd_set afds, wfds, rfds;
int max_fd = 0;
int count = 0;
char buff[1001];
char startMsg[42];


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

void fatal_error() {
	write(2, "Fatal error\n", 12);
	exit(1);
}

void notify_others(int author, char *msg)
{
	for(int fd = 0; fd <= max_fd; fd++)
	{
		if (FD_ISSET(fd, &wfds) && fd != author)
		{
			send(fd, msg, strlen(msg), 0);
		}
	}
}

void connectClient(int fd)
{
	if (fd > max_fd)
	{
		max_fd = fd;
	}
	ids[fd] = count++;
	msgs[fd] = NULL;
	FD_SET(fd, &afds);
	sprintf(startMsg, "server: client %d just arrived\n", ids[fd]);
	notify_others(fd, startMsg);
}

void send_message(int fd)
{
	char *newMsg;

	while (extract_message(&msgs[fd], &newMsg))
	{
		sprintf(startMsg, "client %d: ", ids[fd]);
		notify_others(fd, startMsg);
		notify_others(fd, newMsg);
		free(newMsg);
	}
}

void disconnect_client(int fd)
{
	sprintf(startMsg, "server: client %d just left\n", ids[fd]);
	notify_others(fd, startMsg);
	FD_CLR(fd, &afds);
	free(msgs[fd]);
	msgs[fd] = NULL;
	close(fd);
}


int main(int argc, char **argv) {
	int sockfd, connfd, len;
	struct sockaddr_in servaddr; 

	if (argc != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	// write(1,"test",5);
	FD_ZERO(&afds);
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		fatal_error();
	}
	max_fd = sockfd;
	FD_SET(sockfd, &afds);
	
	// write(1,"test2",5);


	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1])); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		fatal_error();
	}
	// write(1,"test3",5);


	if (listen(sockfd, 1024) != 0) {
		fatal_error();
	}

	while (1)
	{
		rfds = afds;
		wfds = afds;

		
		// write(1,"inside whileloop\n",17);

		if (select(max_fd + 1, &rfds, &wfds, NULL, NULL) < 0)
		{
			// write(1,"fatal error\n", 11);
			fatal_error();
		}
		// write(1,"after select\n", 13);
		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (FD_ISSET(fd, &rfds))
			{
				if (fd == sockfd)
				{
					// accept new client
					// write(1,"adding new client\n", 18);
	
					int lenServaddr = sizeof(servaddr);
					connfd = accept(sockfd, (struct sockaddr *)&servaddr, &lenServaddr);
					if (connfd < 0) { 
						fatal_error();
					}
					// write(1,"adding new client2\n", 19);
					connectClient(connfd);
					// write(1,"new client added\n", 17);
				}
				else
				{
					int buffLen = recv(fd, buff, 1000, 0);
					if (buffLen <= 0)
					{
						disconnect_client(fd);
					}
					else
					{
						buff[buffLen] = '\0';
						msgs[fd] = str_join(msgs[fd], buff);
						send_message(fd);
						//send message
					}
				}
			}
		}
	}
}