#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

// Stack data structure for storing strings (Postfix expression)
char stack[MAX][MAX];
int top = -1;

// Function to push a string onto the stack
void push(char *str) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
    } else {
        strcpy(stack[++top], str);
    }
}

// Function to pop a string from the stack
void pop(char *str) {
    if (top == -1) {
        printf("Stack Underflow\n");
    } else {
        strcpy(str, stack[top--]);
    }
}

// Function to check if the character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to convert Prefix expression to Postfix expression
void preToPost(char* pre_exp, char* post_exp) {
    int length = strlen(pre_exp);
    char temp[MAX], op1[MAX], op2[MAX];

    // Traverse the Prefix expression from right to left
    for (int i = length - 1; i >= 0; i--) {
        // If the character is an operator
        if (isOperator(pre_exp[i])) {
            // Pop two operands from the stack
            pop(op1);
            pop(op2);

            // Concatenate operands and operator to form Postfix
            sprintf(temp, "%s%s%c", op1, op2, pre_exp[i]);

            // Push the resulting Postfix expression back to the stack
            push(temp);
        } else {
            // If the character is an operand, push it to the stack
            char operand[2] = { pre_exp[i], '\0' };
            push(operand);
        }
    }

    // The final result is at the top of the stack
    strcpy(post_exp, stack[top]);
}

int main() {
    char pre_exp[MAX], post_exp[MAX];

    printf("Enter a Prefix expression: ");
    scanf("%s", pre_exp);

    // Convert Prefix to Postfix
    preToPost(pre_exp, post_exp);

    printf("Postfix Expression: %s\n", post_exp);

    return 0;
}
