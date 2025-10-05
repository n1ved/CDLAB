#### 15. P1 : Implement Intermediate code generation for simple expressions.

```
1. Start.
2. Declare necessary headers.
3. Define global variables:
    a) expr[] array to store the input arithmetic expression.
    b) reg variable to represent temporary registers, initialized to 'Z'.
4. Prompt the user to enter an arithmetic expression.
5. Read the input expression into expr[].
6. Print table headers for intermediate code: Operator, Destination, Operand1, Operand2.
7. For each operator in precedence order ('/', '*', '+', '-', '='):
    a) Scan the expression from left to right.
    b) When the operator is found:
        i. Print a quadruple: operator, current register, left operand, right operand.
        ii. Replace the left operand, operator, and right operand in the expression with the current register.
        iii. Decrement the register for the next temporary.
    c) Continue scanning until all operators of current precedence are processed.
8. Repeat the process for the next operator in precedence.
9. After all operators are processed, the intermediate code is generated and displayed.
10. Stop.
```

### 16. P2 : Implement the back end of the compiler which takes the three address code and produces the 8086 assembly language instructions that can be assembled and run using an 8086 assembler. The target assembly instructions can be simple move, add, sub, jump etc


```
1. Start.
2. Declare necessary headers.
3. Define global variables:
    a) icode[][] array to store intermediate code statements.
    b) str[], opr[] arrays for temporary string and operator storage.
    c) Counter for input statements.
4. Prompt the user to enter a set of intermediate code statements (terminated by "exit").
5. Read and store each intermediate code statement into the icode array.
6. For each intermediate code statement:
    a) Copy the statement to a temporary string.
    b) Determine the operator in the statement (e.g., '+', '-', '*', '/').
    c) Map the operator to its target code equivalent (e.g., "ADD", "SUB", "MUL", "DIV").
    d) Print target code instructions to:
        i. Move the first operand to a register.
        ii. Perform the operation using the mapped instruction.
        iii. Store the result from the register to the destination variable.
7. After processing all statements, print the generated target code.
8. Stop.
```
