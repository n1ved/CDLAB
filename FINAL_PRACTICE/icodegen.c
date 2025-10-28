#include <stdio.h>
#include <string.h>

#define MAX_SIZE 256

char expr[MAX_SIZE];
char iexp[MAX_SIZE];
char reg = 'Z';

char stack[MAX_SIZE];
int tos = -1;

char op[3];

int pkidx = -1;

void prntr(char op , char d , char a , char b){
    printf("%c\t%c\t%c\t%c\n",op,d,a,b);
}

void push(char c){
    stack[++tos] = c;
}

char pop(){
    return stack[tos--];
}

char peek(){
    return stack[tos];
}

void reverse(){
    char rstr[MAX_SIZE];
    for(int i=strlen(iexp)-1 ; i>=0 ; i-- ){
        rstr[strlen(iexp)-1 - i] = iexp[i];
    }
    rstr[strlen(iexp)] = '\0';
    strcpy(iexp , rstr);
}
void solve(char op){
    int i=0 , j =0 ;
    char tstr[MAX_SIZE];
    while(iexp[i] != '\0'){
        if(iexp[i] == op){
            prntr(op , reg , iexp[i-1] , iexp[i+1]);
            tstr[j-1] = reg--;
            i += 2;
            continue;
        }
        tstr[j++] = iexp[i++];
    }
    tstr[j] = '\0';
    strcpy(iexp , tstr);
}

void precedence_solver(){
    solve('/' );
    solve('*' );
    solve('+' );
    solve('-' );
    solve('=' );
}

void clean_paranthesis(){
    for(int i=0 ; i<strlen(expr) ; i++){
        if(expr[i] == ')' && tos>=2){
            pkidx = 0;
            while(peek() != '('){
                iexp[pkidx++] = pop();
            }
            iexp[pkidx] = '\0';
            reverse();
            pop();
            precedence_solver();
            for(int j=0 ; j<strlen(iexp) ; j++){
                push(iexp[j]);
            }
        }else{
            push(expr[i]);
        }
    }
    int i=0;
    while(tos >= 0){
        iexp[i++] = pop();
    }
    iexp[i] = '\0';
    reverse();
    strcpy(expr,iexp);
}

int main(){
    printf("Enter expression : ");
    scanf("%s",expr);
    clean_paranthesis();
    strcpy(iexp , expr);
    precedence_solver();
    return 0;
}
