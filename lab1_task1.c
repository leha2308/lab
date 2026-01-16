#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    unsigned char data[] = {3,1,4,1,5,9,2,6,5,3,5};
    FILE *file = fopen(argv[1], "wb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    fwrite(data, sizeof(unsigned char), sizeof(data), file);
    fclose(file);

    file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    unsigned char byte;
    while (fread(&byte, 1, 1, file) == 1) {
        printf("Byte: %u\n", byte);
        printf("FILE ptr: %p\n", (void *)file);
    }
    fclose(file);

    file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    fseek(file, 3, SEEK_SET);
    unsigned char buffer[4];
    fread(buffer, 1, 4, file);

    printf("Buffer after fread:\n");
    for (int i = 0; i < 4; i++) {
        printf("%u ", buffer[i]);
    }
    printf("\n");

    fclose(file);
    return 0;
}
