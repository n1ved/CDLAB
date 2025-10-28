#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINES 256
char line[MAX_LINES];

bool is_delim(char c){
    char delim[] = " ;:{[()]}\n\t<>\"\',";
    for(int i=0 ; i<strlen(delim) ; i++){
        if(c == delim[i])
            return true;
    }
    return false;
}

bool is_op(char c){
    char op[]  = "+=/?|<>!%&*:";
    for(int i=0 ; i<strlen(op) ; i++){
        if(c == op[i])
            return true;
    }
    return false;

}

bool is_kw(char token[]){
    int kw_n = 12;
    char kws[][10] = {
        "auto" , "int" , "float" , "double" , "bool",
        "string" , "char", "if", "else", "case",
        "return" , "main"
    };

    for(int i=0 ; i<kw_n ; i++){
        if(strcmp(token , kws[i]) == 0)
            return true;
    }
    return false;
}

bool is_int(char token[]){
    for(int i=0 ; i<strlen(token) ; i++)
        if(token[i] < '0' || token[i] > '9')
            return false;
    return true;
}

bool is_float(char token[]){
    if(token[0] == '.')
        return false;
    for(int i=0 ; i<strlen(token) ; i++){
        if(token[i]<'0' || token[i] > '9')
            if(token[i] != 'e' || token[i] != '.' || token[i] != '-')
                if(i == strlen(token)-1 )
                    return false;
    }
    return true;
}

int main(){

    FILE *file = fopen("lexical_input.c" , "r");
    if (file == NULL){
        printf("Error opening !!\n");
        return -1;
    }

    while(fgets(line , sizeof(line) , file)){
        bool comment = 0;
        for(int i=0 ; i<strlen(line) - 1;i++){
            if(line[i] == '/' && line[i+1] == '/'){
                printf("Skipping comment\n");
                comment = true;
                break;
            }
        }

        if(comment) continue;

        for(int i=0 ; i<strlen(line)-1 ; i++){
            if(line[i] == '/' && line[i+1] == '*'){
                printf("Multiline comment found \n");
                while(fgets(line,sizeof(line),file)){
                    bool comment_end = false;
                    for(int j=0 ; j<strlen(line) - 1 ; j++){
                        if(line[j] == '*' && line[j+1] =='/'){
                            comment_end = true;
                            break;
                        }
                    }
                    if(comment_end) break;
                }
                comment=true;
                break;
            }
        }

        if(comment) continue;

        char token[MAX_LINES];
        int token_index = 0;

        for(int i=0 ; i<strlen(line) ; i++){
            if( is_delim(line[i]) || is_op(line[i]) ){
                if(strcmp(token , "") != 0){
                    if(is_kw(token)){
                        printf("KW : %s\n",token);
                    }
                    else if(is_int(token) || is_float(token)){
                        printf("NUM: %s\n",token);
                    }else{
                        printf("ID : %s\n",token);
                    }
                }
                strcpy(token , "\0");
                token_index = 0;
            }else{
                token[token_index++] = line[i];
                token[token_index] = '\0';
            }
        }
    }

}
