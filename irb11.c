#include <stdio.h>

int main() {
    char elements[100];
    int i = 0;

    printf("������ ⥪�� (������ Enter ��� ����砭�� �����):\n");

    while ((elements[i] = getchar()) != '\n' && i < 99) {
        i++;
    }
    elements[i] = '\0';

    printf("��⠭�� ⥪��: %s\n", elements);

    int size = i;  

    for (int j = 0; j < size; j++) {
        printf("������ %d: %c\n", j + 1, elements[j]);
    }
    printf("��饥 ���-�� ᨬ�����: %d\n", i);
    return 0;
}
