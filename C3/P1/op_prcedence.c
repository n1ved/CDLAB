#include <stdio.h>
#include <string.h>

#define MAX_TERMS 10
#define MAX_STACK 20
#define MAX_INPUT 20

char stack[MAX_STACK] = {0};
char input[MAX_INPUT] = {0};
char optable[MAX_TERMS][MAX_TERMS][2] = {{0}};
char terminals[MAX_TERMS] = {0};

int n_terminals = 0;
int stack_top = 0;
int input_ptr = 0;
int table_col = 0;
int table_row = 0;

void print_table(){
    printf("\nOperator Precedence Table:\n\t");
    int t;
    for (t = 0; t < n_terminals; t++) {
        printf("%c\t", terminals[t]);
    }
    printf("\n");
    for (t = 0; t < n_terminals; t++) {
        printf("%c\t", terminals[t]);
        int s;
        for (s = 0; s < n_terminals; s++) {
            printf("%c\t", optable[t][s][0]);
        }
        printf("\n");
    }
}

void print_status(){
    int s;
    for (s = 0; s <= stack_top; s++) printf("%c", stack[s]);
    printf("%*s", 15 - (stack_top+1), "");
    int ip;
    for (ip = input_ptr; ip < strlen(input); ip++) printf("%c", input[ip]);
    printf("%*s", 15 - (int)strlen(input) + input_ptr, "");
    printf(" ");
}

int main() {
    printf("Enter number of terminals: ");
    scanf("%d", &n_terminals);
    printf("Enter terminals: ");
    scanf("%s", terminals);

    printf("Enter precedence table values:\n");
    int t, s;
    for (t = 0; t < n_terminals; t++) {
        for (s = 0; s < n_terminals; s++) {
            printf("precedence [%c,%c]: ", terminals[t], terminals[s]);
            scanf("%s", optable[t][s]);
        }
    }

    print_table();

    stack[stack_top] = '$';
    printf("\nEnter input string: ");
    scanf("%s", input);

    input_ptr = 0;
    printf("\n%-15s %-15s %-10s\n", "STACK", "INPUT", "ACTION");
    printf("%-15s %-15s ", stack, input);

    while (input_ptr <= strlen(input)) {
        int find_stack = 0, find_input = 0;
        for (t = 0; t < n_terminals; t++) {
            if (stack[stack_top] == terminals[t]) table_col = t;
            if (input[input_ptr] == terminals[t]) table_row = t;
        }

        if (stack[stack_top] == '$' && input[input_ptr] == '$') {
            printf("Accept\n");
            break;
        } else if (optable[table_col][table_row][0] == '<' || optable[table_col][table_row][0] == '=') {
            stack[++stack_top] = optable[table_col][table_row][0];
            stack[++stack_top] = input[input_ptr];
            printf("Shift %c", input[input_ptr]);
            input_ptr++;
        } else if (optable[table_col][table_row][0] == '>') {
            while (stack[stack_top] != '<' && stack_top > 0) {
                stack_top--;
            }
            if (stack[stack_top] == '<') stack_top--;
            printf("Reduce");
        } else {
            printf("\nNot accepted\n");
            break;
        }
        printf("\n");
        print_status();
    }
    return 0;
}
