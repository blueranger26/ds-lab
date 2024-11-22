#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the doubly linked list (stack)
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node with the given data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to push an element onto the stack
void push(Node** top, int data) {
    Node* newNode = createNode(data);
    if (*top == NULL) {
        *top = newNode;
    } else {
        newNode->next = *top;
        (*top)->prev = newNode;
        *top = newNode;
    }
}

// Function to pop an element from the stack
int pop(Node** top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return -1; // Error value
    }
    Node* temp = *top;
    int poppedData = temp->data;
    *top = temp->next;
    if (*top != NULL) {
        (*top)->prev = NULL;
    }
    free(temp);
    return poppedData;
}

// Function to check if the stack is empty
int isEmpty(Node* top) {
    return top == NULL;
}

// Function to compute the factorial of a number using the stack
int factorial(int n) {
    Node* stack = NULL;
    int result = 1;

    // Push all numbers from 1 to n onto the stack
    for (int i = 1; i <= n; i++) {
        push(&stack, i);
    }

    // Pop elements from the stack and multiply to get the factorial
    while (!isEmpty(stack)) {
        result *= pop(&stack);
    }

    return result;
}

// Function to convert a decimal number to binary using the stack
void decimalToBinary(int n) {
    Node* stack = NULL;

    // Edge case for 0
    if (n == 0) {
        printf("Binary: 0\n");
        return;
    }

    // Push the remainders of the division by 2 onto the stack
    while (n > 0) {
        push(&stack, n % 2);
        n = n / 2;
    }

    // Pop and print the binary digits
    printf("Binary: ");
    while (!isEmpty(stack)) {
        printf("%d", pop(&stack));
    }
    printf("\n");
}

// Main function to test the stack operations
int main() {
    int choice, num;

    while (1) {
        printf("\nStack Operations Menu:\n");
        printf("1. Factorial of a given number\n");
        printf("2. Decimal to Binary Conversion\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to calculate its factorial: ");
                scanf("%d", &num);
                printf("Factorial of %d is %d\n", num, factorial(num));
                break;

            case 2:
                printf("Enter a decimal number: ");
                scanf("%d", &num);
                decimalToBinary(num);
                break;

            case 3:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
