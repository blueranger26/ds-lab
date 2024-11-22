#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack structure
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
        return -1; // Returning -1 when the stack is empty
    } else {
        return s->items[(s->top)--];
    }
}

// A. String Reverse
void reverseString(char str[]) {
    Stack s;
    initStack(&s);
    int i = 0;
    while (str[i] != '\0') {
        push(&s, str[i]);
        i++;
    }
    i = 0;
    while (!isEmpty(&s)) {
        str[i++] = pop(&s);
    }
    str[i] = '\0';
}

// B. Fibonacci Series Generation
void generateFibonacci(int n) {
    int a = 0, b = 1, next;
    printf("Fibonacci Series: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        next = a + b;
        a = b;
        b = next;
    }
    printf("\n");
}

// C. Balancing Parentheses
int isBalanced(char expr[]) {
    Stack s;
    initStack(&s);
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') {
            push(&s, expr[i]);
        } else if (expr[i] == ')') {
            if (isEmpty(&s)) {
                return 0; // Unbalanced
            }
            pop(&s);
        }
    }
    return isEmpty(&s); // If stack is empty, parentheses are balanced
}

int main() {
    int choice, n;
    char str[MAX], expr[MAX];

    while (1) {
        // Menu display
        printf("\nMenu:\n");
        printf("1. String Reverse\n");
        printf("2. Fibonacci Series\n");
        printf("3. Balancing Parentheses\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a string: ");
                getchar();  // To consume newline from previous input
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = 0;  // Remove trailing newline
                reverseString(str);
                printf("Reversed String: %s\n", str);
                break;
            case 2:
                printf("Enter the number of terms for Fibonacci series: ");
                scanf("%d", &n);
                generateFibonacci(n);
                break;
            case 3:
                printf("Enter an expression to check parentheses: ");
                getchar();  // To consume newline from previous input
                fgets(expr, sizeof(expr), stdin);
                expr[strcspn(expr, "\n")] = 0;  // Remove trailing newline
                if (isBalanced(expr)) {
                    printf("The parentheses are balanced.\n");
                } else {
                    printf("The parentheses are not balanced.\n");
                }
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}
