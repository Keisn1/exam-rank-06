#ifndef MINI_SERV_H
#define MINI_SERV_H

int extract_message(char **buf, char **msg);
char *str_join(char *buf, char *add);
int get_client_id();
int ft_puterror(char* err);
int fatal_err();
int get_socket(int port);
void listen_to_socket(int sockfd);

#endif // MINI_SERV_H
