#include <stdio.h>
#include <string.h>

char icode[10][30];
char str[30];
char opr[10];
int i = 0;

int main() {
    printf("Enter the set of intermediate code (terminated by exit):\n");
    while(1){
        scanf("%s", icode[i]);
        if(strcmp(icode[i], "exit") == 0)
            break;
        i++;
    }

    printf("\ntarget code generation");
    printf("\n----------------------\n");

    for(int j = 0; j < i; j++){
        strcpy(str, icode[j]);
        switch(str[3]){
            case '+': strcpy(opr, "ADD"); break;
            case '-': strcpy(opr, "SUB"); break;
            case '*': strcpy(opr, "MUL"); break;
            case '/': strcpy(opr, "DIV"); break;
            default: strcpy(opr, ""); break;
        }
        printf("\tMOV %c, R%d\n", str[2], j);
        printf("\t%s %c, R%d\n", opr, str[4], j);
        printf("\tMOV R%d, %c\n", j, str[0]);
    }

    return 0;
}
