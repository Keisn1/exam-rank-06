#include "mini_serv.h"
#include <string.h>


int main(int argc, char** argv) {
	if (argc != 2)
		return ft_puterror("Wrong number of arguments\n");

	int port = atoi(argv[1]);
	if (port == 0)
		return ft_puterror("Fatal error\n")

	int sockfd = get_socket(port);
	listen_to_socket(sockfd);

}

int serv() {
	/* listen for new connections with multiplexing select */
	fd_set rfds;				/* reqpresents a set of filedescriptors*/
	FT_ZERO(&rfds);				/* clears rfds */


	/* need to track the fds */
	/* readfds writefds are set by select to those which are writable/readable */

	/* accept a new connection if the fd is actually sockfd  */


	/* read from the fd if it is in readfds
	/* write to the fd if it is in writefds */
}
