### 5. P1 : Write Simple Lexical Analyzer in C
```
main:
    1. Start.
    2. Declare and initialize necessary headers and variables:
        a. line[] buffer for input lines.
        b. token[] buffer for extracted tokens.
        c. Various flags and indices.
    3. Open "input.c" file for reading.
    4. If file opening fails, print error and stop.
    5. For each line read from the file:
        a. Check if the line contains a single-line comment ('//'):
            i. If found, print message and skip to next line.
        b. Check if the line contains the start of a multi-line comment ('/*'):
            i. If found, print message and skip lines until end of comment ('*/').
        c. If no comment found, proceed to token extraction:
            i. For each character in the line:
                - If character is space, newline, tab, operator, or delimiter:
                    * Analyze the accumulated token:
                        - If token is a keyword, print as keyword.
                        - Else if token is integer or float, print as number.
                        - Else, print as identifier.
                    * Reset token buffer and token_index.
                - Else, add character to token buffer and increment token_index.
    6. Close the file.
    7. Stop.

is_operator(char c)
    1. For each operator in "+-/*&|?=":
        a. If c matches current operator, return true.
    2. If no match, return false.

is_delimiter(char c)
    1. For each delimiter in "[]{}()<>;:'\",":
        a. If c matches current delimiter, return true.
    2. If no match, return false.

is_keyword(char token[])
    1. For each keyword in keyword list:
        a. If token matches keyword, return true.
    2. If no match, return false.

is_int(char token[])
    1. For each character in token:
        a. If not a digit, return false.
    2. If all characters are digits, return true.

is_float(char token[])
    1. For each character in token:
        a. If not digit and not '.', return false.
        b. If '.' is at the end of the token, return false.
    2. If valid float, return true.
```

### 6. P2 : Write a lex program to recognize all strings which does not contain first four characters of your name as a substring.

```
1. Start.
2. Declare and initialize necessary headers and variables:
    a. name[] for storing input name.
    b. first[] for storing the first four letters of name.
3. Prompt and read name from user.
4. Copy the first four letters of the entered name into first[].
5. Prompt user to enter the string to be scanned.
6. Call yylex() to start lexical analysis on input.
7. For each token matched by [a-zA-Z]+:
    a. Use strstr() to check if the token (yytext) contains first[] as a substring.
    b. If yes, print "<token> contain '<first>' as a substring".
    c. Else, print "<token> does not contain '<first>' as substring".
8. Ignore newlines and other characters.
9. Stop.
```

### 7. P3 : Write a YACC program to recognize a valid variable which starts with a letter followed by any number of letters or digits.

```
1. The program begins in main() where the user is prompted to input an identifier to be tested.
2. yyparse() is called to start the parsing process.
3. The lexical analyzer (lex file) scans the input and identifies tokens:
    - Returns 'letter' for patterns matching [a-zA-Z_][a-zA-Z0-9_]*.
    - Returns 'digit' for patterns matching [0-9]+.
    - Returns ASCII value for any other character.
4. The parser (yacc file) uses the following grammar rules to validate the identifier:
    - start → letter s
    - s → digit s | letter s | ε
5. The parser checks if the input follows these rules, ensuring a valid identifier starts with a letter and can be followed by any number of letters or digits.
6. If the input matches the grammar, parsing completes successfully.
7. If the input does not match, yyerror() is called, which sets valid = 0 and prints an error message.
8. After parsing, main() checks the valid flag.
9. If valid, it prints "Valid identifier"; otherwise, it prints an error message.
```

### 8. P4 : Implementation of Calculator using LEX and YACC

```
1. The program begins in main() where the user is prompted to enter an arithmetic expression.
2. yyparse() is called to start the parsing process.
3. The lexical analyzer (calc.l) scans the input and identifies tokens:
    - Returns digit for patterns matching [0-9]+ and stores the value in yylval.
    - Ignores whitespace.
    - Returns ASCII value for any other character.
    - Returns 0 for newline.
4. The parser (calc.y) uses the following grammar rules to evaluate the expression:
    - start → E { print result }
    - E → E '+' T | E '-' T | T
    - T → T '*' F | T '/' F | F
    - F → '(' E ')' | digit
    - Each rule computes the value and propagates it upwards.
5. If the input matches the grammar, parsing completes successfully and the result is printed.
6. If the input does not match, yyerror() is called, which prints an error message.
7. The program ends.
```

### 9. P5 : Convert the BNF rules into YACC form and write code to generate  abstract syntax tree

```
1. The program begins execution in main(),reading input from a file which name is passed as command line argument.
2. The lexical analyzer (ast.l) scans the input and identifies tokens:
    - Returns MAIN, IF, ELSE, WHILE, TYPE for reserved words.
    - Returns VAR for identifiers and NUM for numbers, storing their values in yylval.var.
    - Returns RELOP for relational operators.
    - Ignores whitespace and tracks line numbers.
3. The parser (ast.y) uses grammar rules to recognize program structure and build quadruples (intermediate code):
    - PROGRAM consists of MAIN followed by a BLOCK.
    - BLOCK consists of statements enclosed in braces.
    - Statements include declarations, assignments, conditionals, and loops.
    - Assignment and expression rules generate quadruples using AddQuadruple and assignment logic.
    - IF, ELSE, and WHILE statements generate conditional and jump quadruples, managing jump targets on a stack.
    - Expressions and conditions are parsed and produce arithmetic/relation quadruples.
4. The parser stores each quadruple (operation, arguments, result) in the QUAD array as parsing proceeds.
5. After parsing, main() prints the quadruple table showing operator, arguments, and result for each step.
6. If there are syntax errors, yyerror() reports them with the line number.
7. Stop
```

### 10. P6 : Write a YACC program to check the syntax of FOR statement in C

```
1. Read FOR statement from user
2. yyparse() is called to start the parsing process.
3. The lexical analyzer (forsyntax.l) scans the input and identifies tokens:
    - Returns FOR for "for", LPAREN for "(", RPAREN for ")", LBRACE/RBRACE for braces.
    - Returns SEMI for ";", ASSIGN for "=", LT/GT for "<" or ">", INC/DEC for "++"/"--".
    - Returns PLUS, MINUS, MUL, DIV for respective operators.
    - Returns NUM for numbers and ID for identifiers.
    - Ignores whitespace.
4. The parser (forsyntax.y) uses grammar rules to validate the syntax of the FOR statement:
    - S → FOR LPAREN E SEMI E SEMI E RPAREN BODY
    - BODY → LBRACE STMT_LIST RBRACE | (empty)
    - STMT_LIST → STMT | STMT_LIST STMT
    - STMT → E SEMI | S
    - E → ID | NUM | ID ASSIGN E | E LT E | E GT E | E PLUS E | E MINUS E | E MUL E | E DIV E | ID INC | ID DEC
5. If the input matches the grammar, parsing completes successfully and prints "Valid Syntax".
6. If the input does not match, yyerror() is called to print an error message.
7. The program ends.
```
