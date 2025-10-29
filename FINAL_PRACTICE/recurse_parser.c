// Rules
// E -> TE'
// E'-> +TE' | e
// T -> FT'
// T'->*FT' | e
// F -> (E) | i

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 128
char input[MAX_SIZE];
int iptr = 0;
char lahead;

void next(){
    lahead = input[iptr++];
}

void match(char c){
    if(lahead == c){
        next();
    }else{
        printf("Syntax Error: expected '%c', got '%c'\n", c, lahead);
        exit(1);
    }
}

void E();
void Ed();
void T();
void Td();
void F();

void Td(){
    if(lahead == '*'){
        printf("T' -> * F T'\n");
        match('*');
        F();
        Td();
    }else{
        printf("T' -> e\n");
    }
}

void Ed(){
    if(lahead == '+'){
        printf("E' -> + T E'\n");
        match('+');
        T();
        Ed();
    }else{
        printf("E' -> e\n");
    }
}

void F(){
    if(lahead == '('){
        printf("F -> (E)\n");
        match('(');
        E();
        match(')');
    }else if(lahead == 'i'){
        printf("F -> i\n");
        match('i');
    }else{
        printf("Syntax Error in F at '%c'\n", lahead);
        exit(1);
    }
}

void T(){
    printf("T -> F T'\n");
    F();
    Td();
}

void E(){
    printf("E -> T E'\n");
    T();
    Ed();
}

int main(){
    printf("Enter the string : ");
    scanf("%s",input);
    next();
    E();
    if(lahead == '$')
        printf("Accepted\n");
    else
        printf("Rejected\n");
    return 0;
}
