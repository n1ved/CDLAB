### 11. P1 : Develop an operator precedence parser for a given language.

```
1. The program begins in main() where the user is prompted to enter the number of terminals and the terminals themselves.
2. The user enters the operator precedence table values for each terminal pair, which are stored in optable.
3. The precedence table is printed for reference.
4. The stack is initialized with '$' and the user is prompted to enter an input string (expression).
5. The parsing process begins, displaying the stack, input, and actions at each step:
    a. Find the column and row for the top of the stack and current input symbol in the precedence table.
    b. If both stack top and input symbol are '$', print "Accept" and stop.
    c. If the table value is '<' or '=', shift the input symbol and precedence marker onto the stack and print "Shift".
    d. If the table value is '>', repeatedly pop the stack until a '<' marker is found (or the bottom is reached), then print "Reduce".
    e. If the table value is invalid, print "Not accepted" and stop.
    f. After each operation, print the current status of stack and input.
6. The program ends when input is accepted or rejected.
```

### 12. P2 : Write a program to find Simulate First and Follow of any given grammar.

```
1. The program begins in main() where the user is prompted to enter the number of productions and the productions themselves.
2. For each non-terminal in the productions, the program computes FIRST sets:
    a. For each production with the current non-terminal on the left-hand side:
        i. If the next symbol is a terminal, add it to the FIRST set.
        ii. If the next symbol is a non-terminal, recursively compute its FIRST set and add all symbols from its FIRST set except epsilon; if epsilon is present, check the next symbol.
3. For each non-terminal in the productions, the program computes FOLLOW sets:
    a. If the non-terminal is the start symbol, add '$' to its FOLLOW set.
    b. For each occurrence of the non-terminal in the right-hand side of a production:
        i. If the next symbol is a terminal, add it to the FOLLOW set.
        ii. If the next symbol is a non-terminal, add all symbols from its FIRST set except epsilon; if epsilon is present or it is the end of the production, add FOLLOW of the left-hand side to the FOLLOW set.
        iii. Avoid duplicates when adding symbols.
4. After computing FIRST and FOLLOW sets for all non-terminals, print the results for each non-terminal.
5. The program ends.
```

### 13. P3 :Construct a recursive descent parser for an expression.


```
1. Start.
2. Declare necessary headers.
3. Define global variables:
    a) input[] array to store the user-provided input string.
    b) ip pointer to track the current position in the input.
    c) lookahead character to hold the current symbol being parsed.
4. Prompt the user to enter an expression (using 'i' for id, operators +, *, parentheses, ending with $).
5. Read the input string and initialize parsing pointer and lookahead.
6. Define E():
    a) Apply the rule E -> T E'.
    b) Print the production used.
    c) Call T() to parse a term.
    d) Call Eprime() to process additional '+' terms.
7. Define Eprime():
    a) Apply the rule E' -> + T E' | ε.
    b) If lookahead is '+', print the production, match '+', call T(), and recursively call Eprime().
    c) If lookahead is not '+', print the epsilon production and return.
8. Define T():
    a) Apply the rule T -> F T'.
    b) Print the production used.
    c) Call F() to parse a factor.
    d) Call Tprime() to process additional '*' factors.
9. Define Tprime():
    a) Apply the rule T' -> * F T' | ε.
    b) If lookahead is '*', print the production, match '*', call F(), and recursively call Tprime().
    c) If lookahead is not '*', print the epsilon production and return.
10. Define F():
    a) Apply the rule F -> i | ( E ).
    b) If lookahead is 'i', print the production and match 'i'.
    c) If lookahead is '(', print the production, match '(', recursively call E(), and match ')'.
    d) If neither, report a syntax error and exit.
11. Define match(expected_symbol):
    a) If lookahead matches the expected symbol, advance to the next symbol.
    b) If not, print a syntax error and exit.
12. Begin parsing by calling E().
13. After parsing, if lookahead is '$', print "Parsing successful!".
14. If not, print "Syntax Error at end of input".
15. Stop.
```

### 14. P4 : Construct a Shift Reduce Parser for a given language.

```
1. Start.
2. Declare necessary headers.
3. Prepare global variables:
    a) stack[] to hold parsing symbols.
    b) input[] to store the input string.
    c) Variables to track the stack top and input pointer.
4. Prompt the user to enter an expression (using 'i' for id, operators +, *, parentheses, ending with $).
5. Print the parsing table headers for stack, input, and action.
6. While there is input left to process (input[input_ptr] != '$'):
    a) Print current stack, input, and action ("Shift").
    b) Shift the next input symbol onto the stack.
    c) Advance input pointer.
    d) While the stack contains a reducible pattern:
        i. Apply the appropriate reduction:
            - If top of stack is 'i', reduce to E → i.
            - If top three stack symbols match E + E, reduce to E → E + E.
            - If top three stack symbols match E * E, reduce to E → E * E.
            - If top three stack symbols match ( E ), reduce to E → ( E ).
        ii. Print the stack, input, and action ("Reduce").
7. After all input is shifted, repeatedly apply reductions for any remaining reducible patterns.
8. Print the final stack, input, and action ("End").
9. If the stack contains a single symbol 'E', print "Parsing successful!".
10. Otherwise, print "Syntax Error".
11. Stop.
```
