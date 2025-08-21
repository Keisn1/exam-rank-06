#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int get_client_id() {
	static int clientId = 0;
	return clientId++;
}

int ft_putstr(char* str) {
	write(STDOUT_FILENO, str, strlen(str));
	return 1;
}

int ft_puterror(char* err) {
	write(STDERR_FILENO, err, strlen(err));
	return 1;
}

int fatal_err() {
	return ft_puterror("Fatal error\n");
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == NULL)
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

/* will end if a newline is encountered */
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
				exit(fatal_err());
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

int get_socket(int port) {
	int sockfd;
	struct sockaddr_in servaddr;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		exit(fatal_err());
	else
		ft_putstr("Socket successfully created..\n");

	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		exit(fatal_err());
	else
		ft_putstr("Socket successfully binded..\n");

	return sockfd;
}

void listen_to_socket(int sockfd) {
	if (listen(sockfd, 10) != 0)
		exit(fatal_err());
}
