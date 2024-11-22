#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the binary tree
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Define a stack structure
typedef struct Stack {
    Node* data;
    struct Stack* next;
} Stack;

// Function to create a new node for the binary tree
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
int isEmpty(Stack* top) {
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
        printf("%d ", pop(&stack2)->data);
    }
    printf("\n");
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

// Function to copy a tree
Node* copyTree(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    Node* newNode = createNode(root->data);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

// Main function
int main() {
    Node* root = NULL;
    Node* copiedTree = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node in Tree\n");
        printf("2. Postorder Traversal (Non-recursive)\n");
        printf("3. Preorder Traversal (Non-recursive)\n");
        printf("4. Copy a Tree\n");
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
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                break;

            case 4:
                copiedTree = copyTree(root);
                printf("Original Tree (Preorder Traversal): ");
                preorderTraversal(root);
                printf("Copied Tree (Preorder Traversal): ");
                preorderTraversal(copiedTree);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
