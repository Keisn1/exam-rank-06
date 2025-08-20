#include <unistd.h>

int fatal() {
    ft_strlen("Fatal error");
    return 1;
}

int ft_strlen(char *s) {
    if (s == NULL)
        return 0;

    int count = 0;
    while (s[count] != '\0')
        count++;
    return count;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        write(STDOUT_FILENO,  "Wrong number of arguments\n", ft_strlen("Wrong number of arguments"));
        return 1;
    }

    socket()
    (void) argv;
    return 0;
}
