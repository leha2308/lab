#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_USERS 10
#define MAX_LOGIN 7
#define MAX_CMD 100

typedef struct {
    char login[MAX_LOGIN];  // Логин пользователя
    int pin;                // PIN-код
    int limit_cmds;         // Ограничение на число команд в сессии (0 = нет)
} User;

User users[MAX_USERS];
int user_count = 0;

// Найти пользователя по логину
int find_user(const char* login) {
    for (int i=0; i<user_count; i++)
        if(strcmp(users[i].login, login)==0)
            return i;
    return -1;
}

// Проверка корректности логина (только латинские буквы и цифры, до 6 символов)
int valid_login(const char* login) {
    int len = strlen(login);
    if(len==0 || len>=MAX_LOGIN) return 0;
    for(int i=0;i<len;i++) {
        if(!((login[i]>='a' && login[i]<='z') ||
             (login[i]>='A' && login[i]<='Z') ||
             (login[i]>='0' && login[i]<='9')))
            return 0;
    }
    return 1;
}

// Проверка корректности PIN (0..100000)
int valid_pin(int pin) {
    return pin>=0 && pin<=100000;
}

// Проверка корректности даты
int valid_date(int day,int month,int year) {
    if(year<1900 || year>2100) return 0;
    if(month<1 || month>12) return 0;
    int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if((year%4==0 && year%100!=0) || year%400==0) days_in_month[1]=29;
    return day>=1 && day<=days_in_month[month-1];
}

// Проверка корректности времени
int valid_time(int hour,int min,int sec) {
    return hour>=0 && hour<=23 && min>=0 && min<=59 && sec>=0 && sec<=59;
}

// Вывод текущего времени
void cmd_time() {
    time_t t=time(NULL);
    struct tm *tm=localtime(&t);
    printf("%02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
}

// Вывод текущей даты
void cmd_date() {
    time_t t=time(NULL);
    struct tm *tm=localtime(&t);
    printf("%02d:%02d:%04d\n", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
}

// Вычисление прошедшего времени с указанного datetime в нужных единицах
// Вычисление прошедшего времени с указанного datetime в нужных единицах
void cmd_howmuch() {
    char input[32];
    char flag[3];

    printf("Enter datetime (dd:MM:yyyy hh:mm:ss) and flag (-s -m -h -y): ");
    if(scanf(" %31[^\n]", input)!=1) { // читаем всю строку до конца
        printf("Input error.\n");
        return;
    }

    // Разделяем на datetime и flag
    char *flag_ptr = strrchr(input, ' '); // ищем последний пробел
    if(!flag_ptr) {
        printf("Invalid input format.\n");
        return;
    }

    strcpy(flag, flag_ptr + 1);  // копируем флаг
    *flag_ptr = '\0'; // обрезаем строку, чтобы осталась только дата и время

    int day, month, year, hour, min, sec;
    if(sscanf(input, "%2d:%2d:%4d %2d:%2d:%2d",
              &day,&month,&year,&hour,&min,&sec)!=6) {
        printf("Invalid datetime format. Use dd:MM:yyyy hh:mm:ss\n");
        return;
    }

    if(!valid_date(day,month,year) || !valid_time(hour,min,sec)) {
        printf("Invalid datetime values.\n");
        return;
    }

    struct tm tm0={0};
    tm0.tm_mday = day;
    tm0.tm_mon  = month-1;
    tm0.tm_year = year-1900;
    tm0.tm_hour = hour;
    tm0.tm_min  = min;
    tm0.tm_sec  = sec;

    time_t t0 = mktime(&tm0);
    if(t0==-1) { printf("Error converting datetime.\n"); return; }

    time_t now=time(NULL);
    double diff=difftime(now,t0);

    if(strcmp(flag,"-s")==0) printf("Elapsed: %.0f seconds\n", diff);
    else if(strcmp(flag,"-m")==0) printf("Elapsed: %.0f minutes\n", diff/60);
    else if(strcmp(flag,"-h")==0) printf("Elapsed: %.0f hours\n", diff/3600);
    else if(strcmp(flag,"-y")==0) printf("Elapsed: %.2f years\n", diff/(3600*24*365.25));
    else printf("Unknown flag. Use -s -m -h -y\n");
}


// Санкции: ограничение числа команд для пользователя
void cmd_sanctions() {
    char username[MAX_LOGIN];
    int code;
    printf("Enter username to sanction: ");
    scanf("%6s", username);
    int idx=find_user(username);
    if(idx==-1) { printf("User not found.\n"); return; }
    printf("Enter confirmation code: ");
    if(scanf("%d",&code)!=1 || code!=52) { printf("Incorrect confirmation code.\n"); return; }
    printf("Enter max commands per session: ");
    int limit;
    if(scanf("%d",&limit)!=1 || limit<=0) { printf("Invalid limit.\n"); return; }
    users[idx].limit_cmds=limit;
    printf("Sanctions applied to user %s\n",username);
}

int main() {
    char login[MAX_LOGIN];
    int pin;

    while(1) {
        printf("\n=== SHELL MENU ===\n1 - Register\n2 - Login\n3 - Exit\nChoice: ");
        int choice;
        if(scanf("%d",&choice)!=1){ while(getchar()!='\n'); continue; }

        if(choice==1) {
            if(user_count>=MAX_USERS){ printf("User limit reached.\n"); continue; }
            printf("Login (max 6 letters/numbers): ");
            scanf("%6s", users[user_count].login);
            if(!valid_login(users[user_count].login)) { printf("Invalid login.\n"); continue; }
            if(find_user(users[user_count].login)!=-1){ printf("User already exists.\n"); continue; }
            printf("PIN (0..100000): ");
            if(scanf("%d",&users[user_count].pin)!=1 || !valid_pin(users[user_count].pin)){ while(getchar()!='\n'); printf("Invalid PIN.\n"); continue;}
            users[user_count].limit_cmds=0;
            user_count++;
            printf("User registered successfully.\n");
        }
        else if(choice==2) {
            printf("Login: "); scanf("%6s", login);
            printf("PIN: "); if(scanf("%d",&pin)!=1){ while(getchar()!='\n'); continue; }
            int idx=find_user(login);
            if(idx==-1 || users[idx].pin!=pin){ printf("Auth failed\n"); continue; }

            printf("Welcome %s! Type 'Help' to see commands.\n",login);
            char cmd[MAX_CMD];
            int cmd_count=0;

            while(1){
                if(users[idx].limit_cmds>0 && cmd_count>=users[idx].limit_cmds){
                    printf("Command limit reached. Logging out.\n"); break;
                }
                printf("> "); scanf(" %99[^\n]",cmd); // читаем всю строку команды

                // парсим команду и аргументы
                char* token=strtok(cmd," ");
                if(!token) continue;

                if(strcmp(token,"Time")==0) { cmd_time(); cmd_count++; }
                else if(strcmp(token,"Date")==0) { cmd_date(); cmd_count++; }
                else if(strcmp(token,"Howmuch")==0) {
                    char* dt=strtok(NULL," ");
                    char* fl=strtok(NULL," ");
                    if(!dt || !fl){ printf("Usage: Howmuch <datetime> <flag>\n"); continue; }
                    cmd_howmuch(dt,fl);
                    cmd_count++;
                }
                else if(strcmp(token,"Logout")==0) break;
                else if(strcmp(token,"Sanctions")==0){ cmd_sanctions(); cmd_count++; }
                else if(strcmp(token,"Help")==0){
                    printf("Available commands:\nTime\nDate\nHowmuch <datetime> <flag>\nLogout\nSanctions <username>\nHelp\n");
                }
                else printf("Unknown command. Type 'Help' to see commands.\n");
            }
        }
        else if(choice==3){ printf("Goodbye!\n"); break; }
        else printf("Invalid choice\n");
    }
    return 0;
}
