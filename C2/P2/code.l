%{
    #include <stdio.h>
    #include <string.h>
    char name[20];
    char first[5];
%}

%%
[a-zA-Z]+   {
                if(strstr(yytext, first) != NULL){
                    printf("%s contain '%s' as a substring\n", yytext, first);
                } else {
                    printf("%s does not contain '%s' as substring\n" , yytext , first);
                }
            }

\n
.
%%

int yywrap(void){
    return 1;
}

int main(){
    printf("Enter name : ");
    scanf("%s", name);
    strncpy(first, name, 4);
    first[4] = '\0';
    printf("Enter string : ");
    yylex();
    return 0;
}
