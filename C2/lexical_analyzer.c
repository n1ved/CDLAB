#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256
char line[MAX_LINE_LENGTH];

bool is_operator(char c){
    char operators[] = "+-/*&|?=";

    for(int i= 0 ; i<strlen(operators) ; i++){
        if(c == operators[i])
            return true;
    }

    return false;
}

bool is_delimiter(char c){
    char delimiter[] = "[]{}()<>;:\'\",";

    for(int i= 0 ; i<strlen(delimiter) ; i++){
        if(c == delimiter[i])
            return true;
    }

    return false;
}

bool is_keyword(char token[]){
    char keyword[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for",
        "goto", "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    for(int i=0 ; i<32 ; i++){
        if(!strcmp(token, keyword[i]))
            return true;
    }

    return false;
}

bool is_int(char token[]){
    for(int i=0 ; i<strlen(token) ; i++){
        if(token[i] < '0' || token[i] > '9')
            return false;
    }
    return true;
}

bool is_float(char token[]){
    for(int i=0 ; i<strlen(token) ; i++){
        if((token[i] < '0' || token[i] > '9') && token[i] != '.')
            return false;
        if(token[i] == '.' && i == strlen(token) - 1)
            return false;
    }

    return true;
}


int main() {

    FILE *file = fopen("input.c", "r");
    if (file == NULL) {
        printf("Error opening file");
        return -1;
    }

    while(fgets(line,  sizeof(line ), file)){
        bool flag = 0;
        for(int i = 0 ; i < strlen(line) ; i++){
            if(line[i] == '/' && line[i+1] == '/'){
                printf("Single line comment found skipping\n");
                flag = true;
                break;
            }
        }

        if (flag) continue;

        for(int i= 0 ; i <strlen(line) ; i++){
            if(line[i] == '/' && line[i+1] == '*'){
                printf("Multi-line comment found skipping untill end\n");
                while(fgets(line , sizeof(line) , file)){
                    bool end_flag = false;
                    for(int j = 0 ; j < strlen(line) ; j++){
                        if(line[j] == '*' && line[j+1] == '/'){
                            end_flag = true;
                            break;
                        }
                    }
                    if(end_flag) break;
                }
                flag = true;
                break;
            }
        }

        if(flag) continue;

        char token[MAX_LINE_LENGTH];
        int token_index = 0;

        for(int i=0 ; i<strlen(line) ; i++){
            if(
                line[i] == ' ' || line[i] == '\n' || line[i] == '\t' || line[i] == '\n' ||
                is_operator(line[i]) || is_delimiter(line[i])
            ){
                if(strcmp(token, "") != 0){
                    if(is_keyword(token))
                        printf("Keyword \t: %s\n", token);
                    else if(is_int(token) || is_float(token))
                        printf("Number \t\t: %s\n" , token);
                    else
                        printf("Identifier \t: %s\n" , token);
                }
                strcpy(token, "");
                token_index = 0;
            }else{
                token[token_index++] = line[i];
                token[token_index] = '\0';
            }
        }
    }
    fclose(file);
    return 0;
}
