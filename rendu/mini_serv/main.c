#include "mini_serv.h"
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

typedef struct conn {
	int fd;
	int client_id;
} t_conn;

typedef struct s_conns {
	t_conn* conns;
	int size;
} t_conns;

void add_to_conns(int connfd, t_conns conns) {
	conns.conns = realloc(conns.conns, sizeof(t_conn) * (conns.size + 1));
	if (!conns.conns)
		exit(fatal_err());
	conns.conns[conns.size].fd = connfd;
	conns.conns[conns.size].client_id = get_client_id();
	conns.size++;
}

void remove_from_conns(int connfd, t_conns conns) {
	t_conn* new_conns = malloc(sizeof(t_conn) * (conns.size - 1));
	if (!new_conns)
		exit(fatal_err());

	for (int i = 0; i < conns.size ; i++) {
		if (conns.conns[i].fd != connfd)
			new_conns[i] = conns.conns[i];
	}
	free(conns.conns);
	conns.conns = new_conns;
	conns.size--;
}


int serv(int sockfd) {
	int retval;					/* nbr of file descriptors contained in the three descriptor sets */
	int connfd;
	socklen_t len;
	t_conns conns = {NULL, 0};

	/* listen for new connections with multiplexing select */
	fd_set rfds;				/* reqpresents a set of filedescriptors*/
	fd_set wfds;				/* reqpresents a set of filedescriptors*/
	FD_ZERO(&rfds);				/* clears rfds */
	FD_SET(sockfd, &rfds);		/* set rfds to first reading socket */

	conns.conns = malloc(sizeof(t_conn));
	conns.conns[0].fd = sockfd;
	conns.conns[0].client_id = get_client_id();

	struct sockaddr_in servaddr, cli;
	len = sizeof(cli);
	while (true) {
		FD_SET(sockfd, &rfds);
		for (int i = 0; i < conns.size; i++) {
			FD_SET(conns.conns[i].fd, &rfds);
			FD_SET(conns.conns[i].fd, &wfds);
		}
		retval = select(sockfd+1, rfds, NULL, NULL, NULL);

		if (retval == -1)
			exit(fatal_err());
		if (retval > 0) {
			if (FD_ISSET(sockfd, &rfds)) {
				connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				add_to_conns(connfd, conns);
			}
			for (int i = 0; i < conns.size ; i++) {
				char buf[500];
				if (FD_ISSET(conns.conns[i], &rfds)) {
					ssize_t nbytes = recv(conns.conns[i], buf, 500, NULL);
					buf[nbytes] = "\0";
					ft_putstr(buf);
				}

			}
			/* check rfds */
			/* check wfds */
		}
	}

	/* need to reinitialize the descriptor sets in any loop */
	/* need to track the fds */
	/* readfds writefds are set by select to those which are writable/readable */

	/* accept a new connection if the fd is actually sockfd  */

	/* file-descriptor is ready to read on END_OF_FILE -> remove the connection */
	/* read from the fd if it is in readfds
	/* write to the fd if it is in writefds */
}

int main(int argc, char** argv) {
	if (argc != 2)
		return ft_puterror("Wrong number of arguments\n");

	int port = atoi(argv[1]);
	if (port == 0)
		exit(fatal_err());

	int sockfd = get_socket(port);
	listen_to_socket(sockfd);

	serv(sockfd);
}
