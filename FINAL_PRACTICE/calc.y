%{
#include <stdio.h>
%}

%token digit

%%
    start   : E {printf("%d\n",$1);}
            ;

    E : E '+' T   {$$ = $1 + $3;}
        | E '-' T {$$ = $1 - $3;}
        | T       {$$ = $1;}
    ;

    T : T '*' F {$$ = $1 * $3;}
        | T '/' F {$$ = $1 / $3;}
        | F       {$$ = $1;}
    ;

    F : '(' E ')' {$$ = $2;}
        | digit   {$$ = $1;}
    ;
%%

int yyerror(const char *s){
    printf("Error : %s\n",s);
    return 0;
}

int main(){
    printf("Enter Expression : ");
    yyparse();
    return 0;
}
