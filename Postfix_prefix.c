#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

// Stack data structure for Prefix conversion
char prefix_stack[MAX][MAX];
int top_prefix = -1;

// Function to push a string onto the prefix stack
void prefix_push(char *str) {
    if (top_prefix == MAX - 1)
        printf("Stack Overflow\n");
    else
        strcpy(prefix_stack[++top_prefix], str);
}

// Function to pop a string from the prefix stack
void prefix_pop(char *str) {
    if (top_prefix == -1) {
        printf("Stack Underflow\n");
    } else {
        strcpy(str, prefix_stack[top_prefix--]);
    }
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to convert Postfix expression to Prefix expression
void postToPrefix(char *post_exp, char *prefix_exp) {
    char temp[MAX], op1[MAX], op2[MAX];
    for (int i = 0; i < strlen(post_exp); i++) {
        if (isOperator(post_exp[i])) {
            // Pop two operands from stack
            prefix_pop(op2);
            prefix_pop(op1);

            // Form the Prefix expression by adding operator before operands
            sprintf(temp, "%c%s%s", post_exp[i], op1, op2);

            // Push the resulting Prefix expression to the stack
            prefix_push(temp);
        } else {
            // If the character is an operand, push it to the stack
            char operand[2] = { post_exp[i], '\0' };
            prefix_push(operand);
        }
    }

    // The final result is at the top of the stack
    strcpy(prefix_exp, prefix_stack[top_prefix]);
}

int main() {
    char post_exp[MAX], prefix_exp[MAX];
    printf("Enter a Postfix expression: ");
    scanf("%s", post_exp);

    // Convert Postfix to Prefix
    postToPrefix(post_exp, prefix_exp);
    printf("Prefix Expression: %s\n", prefix_exp);

    return 0;
}
