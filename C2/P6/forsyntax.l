//Stolen from https://github.com/csc-mec/CD_LAB
%{
    #include "y.tab.h"
%}
%option noyywrap

%%
"for"       { return FOR; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
";"         { return SEMI; }
"="         { return ASSIGN; }
"<"         { return LT; }
">"         { return GT; }
"++"        { return INC; }
"--"        { return DEC; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
[0-9]+      { return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
[ \t\n]     ;
.
%%
