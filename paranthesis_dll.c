#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the doubly linked list (stack)
typedef struct Node {
    char data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node with the given data
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to push an element onto the stack
void push(Node** top, char data) {
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
char pop(Node** top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return -1; // Error value
    }
    Node* temp = *top;
    char poppedData = temp->data;
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

// Function to check the validity of parentheses
int checkParenthesesValidity(char* expression) {
    Node* stack = NULL;

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        // If the character is an opening parenthesis, push it onto the stack
        if (ch == '(') {
            push(&stack, ch);
        }
        // If the character is a closing parenthesis, check if it matches the opening parenthesis
        else if (ch == ')') {
            // If stack is empty, no matching opening parenthesis
            if (isEmpty(stack)) {
                return 0; // Invalid
            }
            pop(&stack);
        }
    }

    // If the stack is empty, all parentheses are matched; otherwise, it's invalid
    return isEmpty(stack);
}

// Main function to test the stack operations
int main() {
    char expression[100];

    printf("Enter a string of parentheses: ");
    scanf("%s", expression);

    if (checkParenthesesValidity(expression)) {
        printf("The parentheses are valid.\n");
    } else {
        printf("The parentheses are invalid.\n");
    }

    return 0;
}
