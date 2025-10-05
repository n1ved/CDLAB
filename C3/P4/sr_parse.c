#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int stack_top = -1;
char input[MAX_SIZE];
int input_ptr = 0;

int is_reducible(){
    if(stack_top >= 0 && stack[stack_top] == 'i')
        return 1;
    if(stack_top >= 2){
        if(stack[stack_top-2] == 'E' && (stack[stack_top-1] == '+' || stack[stack_top-1] == '*') && stack[stack_top] == 'E')
            return 1;
        if(stack[stack_top-2] == '(' && stack[stack_top-1] == 'E' && stack[stack_top] == ')')
            return 1;
    }
    return 0;
}

void push(char c){
    stack[++stack_top] = c;
}

char pop(){
    if(stack_top == -1) return '\0';
    return stack[stack_top--];
}

void reduce(){
    if(stack[stack_top] == 'i'){
        pop();
        push('E');
        printf("Reduce: E -> i\n");
    }
    else if(stack_top >= 2){
        if(stack[stack_top-2] == 'E' && stack[stack_top-1] == '+' && stack[stack_top] == 'E'){
            pop(); pop(); pop();
            push('E');
            printf("Reduce: E -> E+E\n");
        }
        else if(stack[stack_top-2] == 'E' && stack[stack_top-1] == '*' && stack[stack_top] == 'E'){
            pop(); pop(); pop();
            push('E');
            printf("Reduce: E -> E*E\n");
        }
        else if(stack[stack_top-2] == '(' && stack[stack_top-1] == 'E' && stack[stack_top] == ')'){
            pop(); pop(); pop();
            push('E');
            printf("Reduce: E -> (E)\n");
        }
    }
}

void print_status(const char *action){
    char stack_str[MAX_SIZE] = "";
    char input_str[MAX_SIZE] = "";
    int i;
    for(i=0; i<=stack_top; i++)
        stack_str[i] = stack[i];
    stack_str[i] = '\0';
    for(i=0; i<strlen(input)-input_ptr; i++)
        input_str[i] = input[input_ptr + i];
    input_str[i] = '\0';
    printf("%-30s%-30s%-30s\n", stack_str, input_str, action);
}

int main(){
    printf("Enter expression (use i for id, +, *, (, ), end with $): ");
    scanf("%s", input);

    printf("\n%-30s%-30s%-30s\n", "STACK", "INPUT", "ACTION");
    printf("-----------------------------------------------------------------------------\n");

    while(input[input_ptr] != '$'){
        print_status("Shift");
        push(input[input_ptr]);
        input_ptr++;
        while(is_reducible()){
            reduce();
            print_status("Reduce");
        }
    }

    while(is_reducible()){
        reduce();
        print_status("Reduce");
    }

    print_status("End");

    if(stack_top == 0 && stack[stack_top] == 'E'){
        printf("\nParsing successful!\n");
    }else{
        printf("\nSyntax Error\n");
    }
    return 0;
}
