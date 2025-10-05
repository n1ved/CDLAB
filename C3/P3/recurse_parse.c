#include <stdio.h>
#include <stdlib.h>

char input[100];
int ip = 0;
char lookahead;

void next(){
    lookahead = input[ip++];
}

void match(char t){
    if(lookahead == t){
        next();
    }else{
        printf("Syntax Error: expected '%c', got '%c'\n", t, lookahead);
        exit(1);
    }
}

void E();
void Eprime();
void T();
void Tprime();
void F();

void F(){
    if(lookahead == 'i'){
        printf("F -> i\n");
        match('i');
    }else if(lookahead == '('){
        printf("F -> (E)\n");
        match('(');
        E();
        match(')');
    }else{
        printf("Syntax Error in F at '%c'\n", lookahead);
        exit(1);
    }
}

void Tprime(){
    if(lookahead == '*'){
        printf("T' -> *F T'\n");
        match('*');
        F();
        Tprime();
    }else{
        printf("T' -> ε\n");
    }
}

void T(){
    printf("T -> F T'\n");
    F();
    Tprime();
}

void Eprime(){
    if(lookahead == '+'){
        printf("E' -> + T E'\n");
        match('+');
        T();
        Eprime();
    }else{
        printf("E' -> ε\n");
    }
}

void E(){
    printf("E -> T E'\n");
    T();
    Eprime();
}

int main(){
    printf("Enter expression (use i for id, operators + * ( ), end with $): ");
    scanf("%s", input);
    ip = 0;
    next();
    E();
    if(lookahead == '$'){
        printf("Parsing successful!\n");
    }else{
        printf("Syntax Error at end of input\n");
    }
    return 0;
}
