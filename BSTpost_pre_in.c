#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
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

// Stack structure for non-recursive traversal
typedef struct Stack {
    Node* data;
    struct Stack* next;
} Stack;

// Stack operations
void pushStack(Stack** top, Node* node) {
    Stack* newStackNode = (Stack*)malloc(sizeof(Stack));
    newStackNode->data = node;
    newStackNode->next = *top;
    *top = newStackNode;
}

Node* popStack(Stack** top) {
    if (*top == NULL) {
        return NULL;
    }
    Stack* temp = *top;
    *top = (*top)->next;
    Node* node = temp->data;
    free(temp);
    return node;
}

int isStackEmpty(Stack* top) {
    return top == NULL;
}

// Function for non-recursive inorder traversal
void inorderTraversal(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Stack* stack = NULL;
    Node* current = root;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            pushStack(&stack, current);
            current = current->left;
        }

        current = popStack(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// Function for non-recursive preorder traversal
void preorderTraversal(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Stack* stack = NULL;
    pushStack(&stack, root);

    while (!isStackEmpty(stack)) {
        Node* current = popStack(&stack);
        printf("%d ", current->data);

        if (current->right) {
            pushStack(&stack, current->right);
        }
        if (current->left) {
            pushStack(&stack, current->left);
        }
    }
    printf("\n");
}

// Function for non-recursive postorder traversal
void postorderTraversal(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Stack* stack1 = NULL;
    Stack* stack2 = NULL;

    pushStack(&stack1, root);
    while (!isStackEmpty(stack1)) {
        Node* current = popStack(&stack1);
        pushStack(&stack2, current);

        if (current->left) {
            pushStack(&stack1, current->left);
        }
        if (current->right) {
            pushStack(&stack1, current->right);
        }
    }

    while (!isStackEmpty(stack2)) {
        Node* current = popStack(&stack2);
        printf("%d ", current->data);
    }
    printf("\n");
}

// Main function
int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node in Tree\n");
        printf("2. Postorder Traversal (Non-recursive)\n");
        printf("3. Preorder Traversal (Non-recursive)\n");
        printf("4. Inorder Traversal (Non-recursive)\n");
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
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
