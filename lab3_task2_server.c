#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_NAME "/tmp/lab_fifo"

int main(void)
{
    mkfifo(FIFO_NAME, 0666);
    int counts[101] = {0};

    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buf[128];
    while (1) {
        ssize_t r = read(fd, buf, sizeof(buf));
        if (r <= 0)
            continue;

        int len = r;
        counts[len]++;
        if (counts[len] >= 5)
            break;
    }

    close(fd);
    unlink(FIFO_NAME);
    return 0;
}
