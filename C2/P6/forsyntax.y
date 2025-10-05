//Stolen from https://github.com/csc-mec/CD_LAB
%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex(void);
    void yyerror(const char *s);
%}


%token FOR LPAREN RPAREN SEMI ASSIGN LT GT PLUS MINUS MUL DIV
%token NUM ID LBRACE RBRACE
%token INC DEC

%left LT GT
%left PLUS MINUS
%left MUL DIV
%right ASSIGN
%left INC DEC
%%

S   : FOR LPAREN E SEMI E SEMI E RPAREN BODY
        { printf("Valid Syntax \n"); }
    ;

BODY
    : LBRACE STMT_LIST RBRACE
    |
    ;

STMT_LIST
    : STMT
    | STMT_LIST STMT
    ;

STMT
    : E SEMI
    | S
    ;

E   : ID
    | NUM
    | ID ASSIGN E
    | E LT E
    | E GT E
    | E PLUS E
    | E MINUS E
    | E MUL E
    | E DIV E
    | ID INC
    | ID DEC
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "%s : Invalid Statement\n", s);
}

int main() {
    printf("Enter a FOR statement:\n");
    yyparse();
    return 0;
}
