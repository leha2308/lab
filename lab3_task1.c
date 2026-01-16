#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(fd[1]);
        char buf[256];
        ssize_t r = read(fd[0], buf, sizeof(buf) - 1);
        if (r > 0) {
            buf[r] = '\0';
            printf("%s\n", buf);
        }
        close(fd[0]);
    } else {
        close(fd[0]);
        const char *msg = "Hello from parent";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}
