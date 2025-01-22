#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void release_resources(int flag, ...) {
    va_list args;
    va_start(args, flag);

    while (1) {

        void *resource = va_arg(args, void *);

        if (resource == NULL) {
            break;
        }

        if (flag == 1) {

            if (resource != NULL) {
                free(resource);
                resource = NULL;
            }
        } else if (flag == 2) {
            FILE *file = (FILE *)resource;
            if (file != NULL) {
                fclose(file);
                resource = NULL;
            }
        } else {

            printf("Unknown action flag: %d\n", flag);
        }
    }

    va_end(args);
}

int main() {

    char *str = (char *)malloc(50 * sizeof(char));
    if (str) {
        snprintf(str, 50, "Hello, world!");
        printf("Allocated string: %s\n", str);
    }

    FILE *file = fopen("example.txt", "w");
    if (file) {
        fprintf(file, "This is a test file.\n");
        fclose(file);
        file = fopen("example.txt", "r");
        if (file) {
            char buffer[100];
            fgets(buffer, sizeof(buffer), file);
            printf("File contents: %s", buffer);
            fclose(file);
        } else {
            printf("Couldn't open the file for reading.\n");
        }
    } else {
        printf("Couldn't open the file for writing.\n");
    }

    release_resources(1, str, NULL);
    release_resources(2, file, NULL);

    return 0;
}
