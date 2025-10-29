%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%token LP RP GT LT ADD SUB MUL DIV
%token AND OR EQ NQ AS ID

%left OR AND
%left EQ NQ
%left LT GT
%left ADD SUB
%left MUL DIV
%right AS

%%
 E  : E EQ E
    | E NQ E
    | E ADD E
    | E SUB E
    | E MUL E
    | E DIV E
    | E AND E
    | E OR E
    | E AS E
    | E LT E
    | E GT E
    | LP E RP
    | ID
    ;
%%

void yyerror(const char* s){
    printf("rejected : %s\n",s);
}

int main(){
    printf("Enter expression :");
    yyparse();
    printf("Accepted\n");
    return 0;
}
