#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_USERS 10
#define MAX_LOGIN 7

typedef struct {
    char login[MAX_LOGIN];
    int pin;
    int limit;
} User;

User users[MAX_USERS];
int user_count = 0;

int find_user(const char *login) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].login, login) == 0)
            return i;
    }
    return -1;
}

void show_time() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void show_date() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%02d:%02d:%04d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
}

int main() {
    char login[MAX_LOGIN];
    int pin;

    while (1) {
        printf("1 - Register\n2 - Login\nChoice: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            if (user_count >= MAX_USERS) continue;
            printf("Login: ");
            scanf("%6s", users[user_count].login);
            printf("PIN: ");
            scanf("%d", &users[user_count].pin);
            users[user_count].limit = 100;
            user_count++;
        }
        else if (choice == 2) {
            printf("Login: ");
            scanf("%6s", login);
            printf("PIN: ");
            scanf("%d", &pin);

            int idx = find_user(login);
            if (idx == -1 || users[idx].pin != pin) {
                printf("Auth failed\n");
                continue;
            }

            char cmd[32];
            while (1) {
                printf("> ");
                scanf("%31s", cmd);

                if (strcmp(cmd, "Time") == 0)
                    show_time();
                else if (strcmp(cmd, "Date") == 0)
                    show_date();
                else if (strcmp(cmd, "Logout") == 0)
                    break;
                else
                    printf("Unknown command\n");
            }
        }
    }
}
