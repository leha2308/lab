#include <stdio.h>
#include <string.h>
#include <ctype.h>


char registr(char * str){
    size_t ln =  strlen(str);
    int i;
    for(i = 0; i < ln; i += 2)
    {
        str[i] = toupper(str[i]);
    }
    return *str;
}



int main(){

    char str[] = "gotrtrekkdvmty";

    registr(str);
    printf("%s", str);

    return 0;
}