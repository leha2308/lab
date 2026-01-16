#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

#define FIFO_NAME "/tmp/lab_fifo"

int main(void)
{
    srand(time(NULL));
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buf[100];
    while (1) {
        int len = rand() % 100 + 1;
        for (int i = 0; i < len; i++)
            buf[i] = 'A' + rand() % 26;
        write(fd, buf, len);
        usleep(100000);
    }

    close(fd);
    return 0;
}
