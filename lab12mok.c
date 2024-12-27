#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void xor_encrypt_decrypt(const char *input_file, const char *output_file, const char *key) {
    FILE *in = fopen(input_file, "rb");
    if (!in) {
        perror("Ошибка открытия входного файла");
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(output_file, "wb");
    if (!out) {
        perror("Ошибка создания выходного файла");
        fclose(in);
        exit(EXIT_FAILURE);
    }

    size_t key_len = strlen(key);
    if (key_len == 0) {
        fprintf(stderr, "Ключ не может быть пустым.\n");
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }

    size_t i = 0;
    int ch;

    while ((ch = fgetc(in)) != EOF) {
        char encrypted_char = ch ^ key[i % key_len];
        fputc(encrypted_char, out);
        i++;
    }

    fclose(in);
    fclose(out);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Использование: %s [mode] [input_file] [output_file] [key]\n", argv[0]);
        fprintf(stderr, "Режимы:\n  encrypt - шифрование\n  decrypt - дешифрование\n");
        return EXIT_FAILURE;
    }

    const char *mode = argv[1];
    const char *input_file = argv[2];
    const char *output_file = argv[3];
    const char *key = argv[4];

    if (strcmp(mode, "encrypt") == 0 || strcmp(mode, "decrypt") == 0) {
        xor_encrypt_decrypt(input_file, output_file, key);
        printf("Операция %s успешно завершена.\n", mode);
    } else {
        fprintf(stderr, "Неверный режим: %s. Используйте 'encrypt' или 'decrypt'.\n", mode);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
