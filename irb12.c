#include <stdio.h>
#include <string.h>


int search(const char * str1,const char * str2 ){

    if(str2 == NULL){
        return -2;
    }
    if(strlen(str2) == 0 || strlen(str1) == 0){
        return -4;
    }

    if(str1 == NULL){
        return -1;
    }
    int j = 0;
   for (int i = 0; i < strlen(str1); i++ ){

       if (str1[i] != str2[j]){
           j = 0;
       }
       else{
           j++;
           if(j == strlen(str2)){
               return i - j + 1;
               break;
           }
       }
   } if(j < strlen(str2)) {
        return  -3;
    }
}


int main(){
char str1[] = {"Hello"};
char str2[] = {""};
int a = search(str1, str2);
    printf("Inddex: %d", a);

    return 0;
}
