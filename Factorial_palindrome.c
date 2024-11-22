#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure
typedef struct Stack {
    int top;
    int items[MAX];
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

void push(Stack *s, int item) {
    if (isFull(s)) {
        printf("Stack overflow\n");
    } else {
        s->items[++(s->top)] = item;
    }
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1; // Returning -1 when the stack is empty
    } else {
        return s->items[(s->top)--];
    }
}

// A. Factorial of a given number
int factorial(int n) {
    Stack s;
    initStack(&s);
    int result = 1;
    for (int i = 1; i <= n; i++) {
        push(&s, i);
    }
    while (!isEmpty(&s)) {
        result *= pop(&s);
    }
    return result;
}

// B. Decimal to Binary Conversion
void decimalToBinary(int n) {
    Stack s;
    initStack(&s);
    if (n == 0) {
        printf("Binary: 0\n");
        return;
    }
    while (n > 0) {
        push(&s, n % 2);
        n /= 2;
    }
    printf("Binary: ");
    while (!isEmpty(&s)) {
        printf("%d", pop(&s));
    }
    printf("\n");
}

// C. Palindrome checking of a String
int isPalindrome(char str[]) {
    Stack s;
    initStack(&s);
    int length = strlen(str);
    
    // Push all characters of the string onto the stack
    for (int i = 0; i < length; i++) {
        push(&s, str[i]);
    }
    
    // Pop characters and compare with the original string
    for (int i = 0; i < length; i++) {
        if (str[i] != pop(&s)) {
            return 0; // Not a palindrome
        }
    }
    return 1; // Palindrome
}

int main() {
    int choice, n;
    char str[MAX];

    while (1) {
        // Menu display
        printf("\nMenu:\n");
        printf("1. Factorial of a given number\n");
        printf("2. Decimal to Binary Conversion\n");
        printf("3. Palindrome checking of a string\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to calculate factorial: ");
                scanf("%d", &n);
                printf("Factorial of %d is %d\n", n, factorial(n));
                break;
            case 2:
                printf("Enter a decimal number: ");
                scanf("%d", &n);
                decimalToBinary(n);
                break;
            case 3:
                printf("Enter a string to check palindrome: ");
                getchar(); // To consume newline from previous input
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = 0;  // Remove trailing newline
                if (isPalindrome(str)) {
                    printf("The string is a palindrome.\n");
                } else {
                    printf("The string is not a palindrome.\n");
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
