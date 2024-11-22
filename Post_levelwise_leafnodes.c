#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the structure for a node in the binary tree
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Define a structure for the stack
typedef struct Stack {
    Node* data;
    struct Stack* next;
} Stack;

// Function to create a new binary tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Stack operations: Push
void push(Stack** top, Node* node) {
    Stack* newStackNode = (Stack*)malloc(sizeof(Stack));
    newStackNode->data = node;
    newStackNode->next = *top;
    *top = newStackNode;
}

// Stack operations: Pop
Node* pop(Stack** top) {
    if (*top == NULL) {
        return NULL;
    }
    Stack* temp = *top;
    Node* node = temp->data;
    *top = temp->next;
    free(temp);
    return node;
}

// Stack operations: Check if empty
bool isEmpty(Stack* top) {
    return top == NULL;
}

// Function to insert a node in the binary tree
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    char direction;
    printf("Enter 'L' to insert to the left of %d or 'R' to insert to the right: ", root->data);
    scanf(" %c", &direction);
    if (direction == 'L' || direction == 'l') {
        root->left = insertNode(root->left, data);
    } else if (direction == 'R' || direction == 'r') {
        root->right = insertNode(root->right, data);
    } else {
        printf("Invalid direction! Try again.\n");
    }
    return root;
}

// Non-recursive postorder traversal
void postorderTraversal(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Stack* stack1 = NULL;
    Stack* stack2 = NULL;

    push(&stack1, root);
    while (!isEmpty(stack1)) {
        Node* current = pop(&stack1);
        push(&stack2, current);

        if (current->left) {
            push(&stack1, current->left);
        }
        if (current->right) {
            push(&stack1, current->right);
        }
    }

    while (!isEmpty(stack2)) {
        Node* current = pop(&stack2);
        printf("%d ", current->data);
    }
    printf("\n");
}

// Function to display the tree level-wise
void displayLevelwise(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Node* queue[100]; // Simple array-based queue
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->left) {
            queue[rear++] = current->left;
        }
        if (current->right) {
            queue[rear++] = current->right;
        }
    }
    printf("\n");
}

// Function to display all leaf nodes of the tree
void displayLeafNodes(Node* root) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
        return;
    }
    displayLeafNodes(root->left);
    displayLeafNodes(root->right);
}

// Main function
int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node\n");
        printf("2. Postorder Traversal (Non-recursive)\n");
        printf("3. Display Tree Level-wise\n");
        printf("4. Display Leaf Nodes of Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                break;
            case 3:
                printf("Level-wise Traversal: ");
                displayLevelwise(root);
                break;
            case 4:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
