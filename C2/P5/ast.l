//Stolen from https://github.com/csc-mec/CD_LAB
%{
    #include "y.tab.h"
    #include <stdio.h>
    #include <string.h>

    int cur_line = 1;
%}

identifier [a-zA-Z_][a-zA-Z0-9]*
number     [0-9]+|([0-9]*\.[0-9]+)

%%
"main"                      return MAIN;
"if"                        return IF;
"else"                      return ELSE;
"while"                     return WHILE;
"int"|"char"|"float"        return TYPE;
{identifier}                { strcpy(yylval.var , yytext); return VAR; }
{number}                    { strcpy(yylval.var , yytext) ; return NUM; }
"<"|"<="|">"|">="|"=="|"!=" return RELOP;
[ \t\r]                     ;
\n                          cur_line++;
.                           return yytext[0];
%%

int yywrap() {
    return 1;
}
