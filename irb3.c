#include <stdio.h>

void a2b(int * pa, int * pb){
int temp;
temp = *pa;
*pa = *pb;
*pb = temp;
}

int main(){
    int a, b;

    printf("Enter a, b:\n", a, b);
    scanf("%d%d", &a, &b);

    printf("Before reverse: a = %d, b = %d\n", a, b);
    a2b(&a, &b);

    printf("After reverse: a = %d, B = %d\n", a, b);

    return 0;
}