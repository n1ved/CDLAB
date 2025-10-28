%{
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>


    struct quad {
        char op[5];
        char arg1[10];
        char arg2[10];
        char result[10];
    } QUAD[30];


    struct stack {
        int items[100];
        int top;
    }STACK;

    extern int line;


    void push(int val);
    int pop();

    int index = 0;
    void addQdup(char* op , char* arg1 , char* arg2 , char* result);

    void yyerror(const char s*);
    int yylex(void);
%}

%union{
    char var[10];
};

%token <var> NUM VAR RELOP
%token MAIN IF ELSE WHILE DTYPE
%type <var> EXPR ASSIGNMENT CONDITION IFST ELSEST WHILELOOP

%left '-' '+'
%left '*' '/'

%%

PROGRAM: MAIN BLOCK
;

BLOCK: '{' CODE '}'
;

CODE: BLOCK | STATEMENT CODE | STATEMENT;

STATEMENT : DTSECT ';' | ASSIGNMENT ';' | CONDST | WHILEST ;

DTSECT : TYPE VARLIST ';' ;

VARLIST : VAR | VAR ',' VARLIST ;

ASSIGNMENT : VAR '=' EXPR {
    strcpy(QUAD[index].op , '=');
    strcpy(QUAD[index].arg1, $3);
    strcpy(QUAD[index].arg2, "");
    strcpy(QUAD[index].result, $1);
    strcpy($$ , QUAD[index].result);
    index++;
};

EXPR :  EXPR '+' EXPR {addQdup("+" , $1 , $3 , $$);} |
        EXPR '-' EXPR {addQdup("-" , $1 , $3 , $$);} |
        EXPR '*' EXPR {addQdup("*" , $1 , $3 , $$);} |
        EXPR '/' EXPR {addQdup("/" , $1 , $3 , $$);} |
        '-' EXPR {addQdup("UMIN" , $1 , "" , $$);} |
        '(' EXPR ')' {strcpy($$, $2)}
        VAR |
        NUM ;

CONDST : IFST {

        }
