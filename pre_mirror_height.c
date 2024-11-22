#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the binary tree
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Stack structure for non-recursive traversal
typedef struct Stack {
    Node* data;
    struct Stack* next;
} Stack;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to push a node onto the stack
void push(Stack** top, Node* node) {
    Stack* newStackNode = (Stack*)malloc(sizeof(Stack));
    newStackNode->data = node;
    newStackNode->next = *top;
    *top = newStackNode;
}

// Function to pop a node from the stack
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

// Function to check if the stack is empty
int isEmpty(Stack* top) {
    return top == NULL;
}

// Function to insert a node into the binary tree
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

// Non-recursive preorder traversal
void preorderTraversal(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    Stack* stack = NULL;
    push(&stack, root);
    while (!isEmpty(stack)) {
        Node* current = pop(&stack);
        printf("%d ", current->data);
        if (current->right) {
            push(&stack, current->right);
        }
        if (current->left) {
            push(&stack, current->left);
        }
    }
    printf("\n");
}

// Function to display the mirror image of the tree without creating a new tree
void mirrorImage(Node* root) {
    if (root == NULL) {
        return;
    }
    Stack* stack = NULL;
    push(&stack, root);
    while (!isEmpty(stack)) {
        Node* current = pop(&stack);
        // Swap left and right children
        Node* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->right) {
            push(&stack, current->right);
        }
        if (current->left) {
            push(&stack, current->left);
        }
    }
    printf("Tree has been mirrored successfully.\n");
}

// Function to calculate the height of the tree
int height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Main function
int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node\n");
        printf("2. Preorder Traversal (Non-recursive)\n");
        printf("3. Display Mirror Image of Tree\n");
        printf("4. Display Height of Tree\n");
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
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                break;
            case 3:
                mirrorImage(root);
                printf("Preorder Traversal of Mirrored Tree: ");
                preorderTraversal(root);
                break;
            case 4:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
