#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int tos = -1;
char input[MAX_SIZE];
int iptr = 0;
char printbfr[3];

void push(char c){
    stack[++tos] = c;
}

int pop(){
    return stack[tos--];
}

bool is_reducable(){
    if(tos >= 0 && stack[tos] == 'i')
        return true;
    if(tos >= 2){
        if(stack[tos-2] == 'E' && ( stack[tos-1] == '*' || stack[tos-1] == '+') && stack[tos] == 'E')
            return true;
        if(stack[tos-2] == '(' && stack[tos-1] == 'E' && stack[tos] == ')')
            return true;
    }

    return false;
}

void reduce(){
    if(stack[tos] == 'i'){
        pop();
        push('E');
        printf("E -> i\n");
    }else if(tos >= 2){
        printbfr[0] = stack[tos-2];
        printbfr[1] = stack[tos-1];
        if(
            (
                stack[tos-2] == 'E' &&
                (stack[tos-1] == '*' || stack[tos-1] == '+') &&
                stack[tos] == 'E'
            ) ||
            (
                stack[tos-2] == '(' &&
                stack[tos-1] == 'E'&&
                stack[tos] == ')'
            )
        ) {
            pop();pop();pop();
            push('E');
            if(printbfr[0] == 'E'){
                printf("E -> E%cE\n",printbfr[1]);
            }else {
                printf("E -> (E)\n");
            }
        }
    }
}

int main(){
    printf("Enter expression : ");
    scanf("%s" , input);

    while(input[iptr] != '$'){
        //shift
        printf("Push %c\n",input[iptr]);
        push(input[iptr++]);
        while(is_reducable()){
            printf("R %d %c\n",tos,stack[tos]);
            reduce();
        }
    }

    while(is_reducable()){
        reduce();
    }

    if(tos == 0 && stack[tos] == 'E'){
        printf("Accepeted\n");
    }else{
        printf("Failed\n");
    }

    return 0;
}
