#include <stdio.h>
#include <unistd.h>

int main(void) {
    fork();
    printf("Hi\n");
    fork();
    printf("Hi\n");
    return 0;
}