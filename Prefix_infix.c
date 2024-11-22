#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

// Stack data structure for Infix conversion
char infix_stack[MAX][MAX];
int top_infix = -1;

// Function to push a string onto the infix stack
void infix_push(char *str) {
    if (top_infix == MAX - 1)
        printf("Stack Overflow\n");
    else
        strcpy(infix_stack[++top_infix], str);
}

// Function to pop a string from the infix stack
void infix_pop(char *str) {
    if (top_infix == -1) {
        printf("Stack Underflow\n");
    } else {
        strcpy(str, infix_stack[top_infix--]);
    }
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to convert Prefix expression to Infix expression
void preToInfix(char *pre_exp, char *infix_exp) {
    char temp[MAX], op1[MAX], op2[MAX];
    for (int i = strlen(pre_exp) - 1; i >= 0; i--) {
        if (isOperator(pre_exp[i])) {
            // Pop two operands from stack
            infix_pop(op1);
            infix_pop(op2);

            // Form the Infix expression by putting parentheses
            sprintf(temp, "(%s%c%s)", op1, pre_exp[i], op2);

            // Push the resulting Infix expression to the stack
            infix_push(temp);
        } else {
            // If the character is an operand, push it to the stack
            char operand[2] = { pre_exp[i], '\0' };
            infix_push(operand);
        }
    }

    // The final result is at the top of the stack
    strcpy(infix_exp, infix_stack[top_infix]);
}

int main() {
    char pre_exp[MAX], infix_exp[MAX];
    printf("Enter a Prefix expression: ");
    scanf("%s", pre_exp);

    // Convert Prefix to Infix
    preToInfix(pre_exp, infix_exp);
    printf("Infix Expression: %s\n", infix_exp);

    return 0;
}
