#include <stdio.h>
#include <string.h>

char expr[100];
char reg = 'Z';

void gen_op(char operator){
    int i = 0, j = 0;
    char temp[100];
    while(expr[i] != '\0'){
        if(expr[i] == operator){
            printf("%c\t%c\t%c\t%c\n", operator, reg, expr[i-1], expr[i+1]);
            temp[j-1] = reg;
            i += 2;
            reg--;
            continue;
        }
        temp[j++] = expr[i++];
    }
    temp[j] = '\0';
    strcpy(expr, temp);
}

void gen_code(){
    gen_op('/');
    gen_op('*');
    gen_op('+');
    gen_op('-');
    gen_op('=');
}

int main(){
    printf("Enter expression:\n");
    scanf("%s", expr);
    printf("Oprtr\tDestn\tOp1\tOp2\n");
    gen_code();
    return 0;
}
