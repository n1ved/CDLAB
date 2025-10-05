%{
    #include <stdio.h>
    int valid = 1;
    int yyerror(const char *s);
%}

%token digit letter

%%
    start   : letter s
    s       : digit s | letter s |
    ;
%%

int yyerror(const char *s) {printf("%s : not an identifier !!\n",s) ; valid = 0 ; return 0 ;}

int main(){
    printf("Enter identifier to be tested : ");
    yyparse();
    if(valid){
        printf("Valid identifier \n");
    }
    return 0;
}
