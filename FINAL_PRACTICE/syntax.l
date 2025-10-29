%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
"("                 return LP;
")"                 return RP;
">"                 return GT;
"<"                 return LT;
"+"                 return ADD;
"-"                 return SUB;
"*"                 return MUL;
"/"                 return DIV;
"&&"                return AND;
"||"                return OR;
"=="                return EQ;
"!="                return NQ;
"="                 return AS;
[a-zA-Z0-9]+        return ID;
[\t ]               ;
[\n]                return 0;
.                   return yytext[0];
%%

int yywrap(){
    return 1;
}
