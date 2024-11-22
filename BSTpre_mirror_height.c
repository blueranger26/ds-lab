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

// Function to insert a node into the BST
Node* insertNode(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }
    Node* current = root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            printf("Duplicate values are not allowed.\n");
            return root;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
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

// Display the mirror image of the tree without creating a new tree
void displayMirror(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Stack* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        Node* current = pop(&stack);
        printf("%d ", current->data);

        // Push left and right children in swapped order
        if (current->left) {
            push(&stack, current->left);
        }
        if (current->right) {
            push(&stack, current->right);
        }
    }
    printf("\n");
}

// Display the height of the tree
int calculateHeight(Node* root) {
    if (root == NULL) {
        return 0;
    }

    Stack* stack = NULL;
    Stack* tempStack = NULL;
    push(&stack, root);
    int maxDepth = 0;

    while (!isEmpty(stack)) {
        Node* current = pop(&stack);
        push(&tempStack, current);

        if (current->left) {
            push(&stack, current->left);
        }
        if (current->right) {
            push(&stack, current->right);
        }
    }

    while (!isEmpty(tempStack)) {
        Node* current = pop(&tempStack);
        int depth = 1;

        while (current != root) {
            depth++;
            current = current->right ? current->right : current->left;
        }

        if (depth > maxDepth) {
            maxDepth = depth;
        }
    }

    return maxDepth;
}

// Main function
int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node in Tree\n");
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
                printf("Mirror Image of Tree (Preorder Traversal): ");
                displayMirror(root);
                break;

            case 4:
                printf("Height of Tree: %d\n", calculateHeight(root));
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
