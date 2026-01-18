#include <stdio.h>

#define DATA_SIZ 11

void print_file_attrs(FILE *f);

int main(int argc, char *argv[])
{
    int i;
    FILE *file = NULL;
    unsigned char byte = 0;
    unsigned char buf[4];

    const unsigned char bytes[DATA_SIZ] =
            {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    if (argc != 2)
    {
        fprintf(stderr, "Incorrect args count\n");
        return 1;
    }

    /* Запись файла */
    file = fopen(argv[1], "wb");
    if (file == NULL)
    {
        fprintf(stderr, "File not open for writing\n");
        return 2;
    }

    fwrite(bytes, sizeof(unsigned char), DATA_SIZ, file);
    fclose(file);

    /* Чтение по байтам */
    file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        fprintf(stderr, "File not open for reading\n");
        return 3;
    }

    while (fread(&byte, sizeof(unsigned char), 1, file) == 1)
    {
        printf("byte = %u\n", byte);
        print_file_attrs(file);
    }

    fclose(file);

    /* Чтение блока с fseek */
    file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        fprintf(stderr, "File not open for reading\n");
        return 4;
    }

    fseek(file, 3, SEEK_SET);
    fread(buf, sizeof(unsigned char), 4, file);

    printf("buffer contains: [ ");
    for (i = 0; i < 4; ++i)
    {
        printf("%u ", buf[i]);
    }
    printf("]\n");

    fclose(file);
    return 0;
}

void print_file_attrs(FILE *f)
{
    long pos = ftell(f);

    printf("  ftell        : %ld\n", pos);
    printf("  feof         : %d\n", feof(f));
    printf("  ferror       : %d\n", ferror(f));
    printf("\n");
}
