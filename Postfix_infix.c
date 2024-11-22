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

// Function to convert Postfix expression to Infix expression
void postToInfix(char *post_exp, char *infix_exp) {
    char temp[MAX], op1[MAX], op2[MAX];
    for (int i = 0; i < strlen(post_exp); i++) {
        if (isOperator(post_exp[i])) {
            // Pop two operands from stack
            infix_pop(op2);
            infix_pop(op1);

            // Form the Infix expression by adding parentheses around operands and operator
            sprintf(temp, "(%s%c%s)", op1, post_exp[i], op2);

            // Push the resulting Infix expression to the stack
            infix_push(temp);
        } else {
            // If the character is an operand, push it to the stack
            char operand[2] = { post_exp[i], '\0' };
            infix_push(operand);
        }
    }

    // The final result is at the top of the stack
    strcpy(infix_exp, infix_stack[top_infix]);
}

int main() {
    char post_exp[MAX], infix_exp[MAX];
    
    printf("Enter a Postfix expression: ");
    scanf("%s", post_exp);

    // Convert Postfix to Infix
    postToInfix(post_exp, infix_exp);
    printf("Infix Expression: %s\n", infix_exp);

    return 0;
}
