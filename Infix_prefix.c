#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure for operators
typedef struct Stack {
    int top;
    char items[MAX];
} Stack;

// Stack operations
void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char item) {
    if (isFull(s)) {
        printf("Stack overflow\n");
    } else {
        s->items[++(s->top)] = item;
    }
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1; // Error value
    } else {
        return s->items[(s->top)--];
    }
}

// Function to check precedence of operators
int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    return 0;
}

// Function to apply the operator
int applyOperator(char operator, int operand1, int operand2) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: return 0;
    }
}

// Function to reverse a string
void reverse(char* exp) {
    int n = strlen(exp);
    for (int i = 0; i < n / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[n - i - 1];
        exp[n - i - 1] = temp;
    }
}

// Infix to Postfix Conversion
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0, k = 0;
    char symbol;

    while ((symbol = infix[i++]) != '\0') {
        if (isalnum(symbol)) {
            postfix[k++] = symbol; // If operand, add it to postfix
        } else if (symbol == '(') {
            push(&s, symbol); // Push '(' to stack
        } else if (symbol == ')') {
            while (!isEmpty(&s) && s.items[s.top] != '(') {
                postfix[k++] = pop(&s); // Pop operators until '('
            }
            pop(&s); // Discard '('
        } else {
            while (!isEmpty(&s) && precedence(s.items[s.top]) >= precedence(symbol)) {
                postfix[k++] = pop(&s); // Pop operators with higher or equal precedence
            }
            push(&s, symbol); // Push the current operator
        }
    }

    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s); // Pop any remaining operators
    }
    postfix[k] = '\0'; // Null-terminate the postfix expression
}

// Infix to Prefix Conversion
void infixToPrefix(char* infix, char* prefix) {
    // Reverse the infix expression
    reverse(infix);
    
    // Convert the reversed infix to postfix
    char postfix[MAX];
    infixToPostfix(infix, postfix);
    
    // Reverse the postfix expression to get the prefix
    reverse(postfix);
    strcpy(prefix, postfix);
}

int main() {
    char infix[MAX], prefix[MAX];

    printf("Enter the infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0; // Remove trailing newline character
    
    // Convert to prefix
    infixToPrefix(infix, prefix);
    printf("Prefix Expression: %s\n", prefix);

    return 0;
}
