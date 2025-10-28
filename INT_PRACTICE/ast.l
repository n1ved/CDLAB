%{
    #include "y.tab.h"
    #include <stdio.h>
    #include <stdlib.h>
    int line = 1;
%}

identifier [a-zA-Z_][a-zA-Z_0-9]*
number [0-9]+|([0-9]+\.[0-9]+)

%%

"main"          return MAIN;
"if"            return IF;
"else"          return ELSE;
"while"         return WHILE;
"int" | "char" | "float" return DTYPE;
{identifier}    {strcpy(yylval.var , yytext); return VAR ;}
{number}        {strcpy(yylval,var , yytext); return NUM ;}
"<" | "<=" | ">=" | ">" | "==" | "!=" return RELOP;
[ \t\r]            ;
\n              line++;
.               return yytext[0];

%%

int yywrap(){
    return 1;
}
