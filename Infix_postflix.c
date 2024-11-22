#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack structure for operators and operands
typedef struct Stack {
    int top;
    float items[MAX];
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

void push(Stack *s, float item) {
    if (isFull(s)) {
        printf("Stack overflow\n");
    } else {
        s->items[++(s->top)] = item;
    }
}

float pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1; // Error value
    } else {
        return s->items[(s->top)--];
    }
}

// Function to check operator precedence
int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    return 0;
}

// Function to perform arithmetic operations
float applyOperator(float a, float b, char operator) {
    switch (operator) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
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

// Function to evaluate postfix expression
float evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0;
    float a, b, result;
    char symbol;
    
    while ((symbol = postfix[i++]) != '\0') {
        if (isalnum(symbol)) {
            printf("Enter value for %c: ", symbol); // Prompt for operand value
            scanf("%f", &result);
            push(&s, result); // Push operand value onto stack
        } else {
            b = pop(&s);
            a = pop(&s);
            result = applyOperator(a, b, symbol); // Apply the operator
            push(&s, result);
        }
    }
    return pop(&s); // Final result is the last item on the stack
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter the infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0; // Remove trailing newline character
    
    // Convert to postfix
    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);
    
    // Evaluate postfix
    float result = evaluatePostfix(postfix);
    printf("Result of evaluation: %.2f\n", result);

    return 0;
}
