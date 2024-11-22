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

// Function to create the mirror image of the tree
Node* createMirror(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    Node* mirrorRoot = createNode(root->data);
    mirrorRoot->left = createMirror(root->right);
    mirrorRoot->right = createMirror(root->left);

    return mirrorRoot;
}

// Function to find the minimum value node in a tree
Node* findMin(Node* root) {
    Node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a node from the tree
Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        printf("Value not found in the tree.\n");
        return root;
    }

    Node* current = root;
    Node* parent = NULL;

    // Find the node to delete and its parent
    while (current != NULL && current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Value not found in the tree.\n");
        return root;
    }

    // Case 1: Node with no children
    if (current->left == NULL && current->right == NULL) {
        if (current == root) {
            root = NULL;
        } else if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    }
    // Case 2: Node with one child
    else if (current->left == NULL || current->right == NULL) {
        Node* child = (current->left != NULL) ? current->left : current->right;
        if (current == root) {
            root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(current);
    }
    // Case 3: Node with two children
    else {
        Node* successor = findMin(current->right);
        int successorData = successor->data;
        root = deleteNode(root, successor->data);
        current->data = successorData;
    }

    return root;
}

// Main function
int main() {
    Node* root = NULL;
    Node* mirrorRoot = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node in Tree\n");
        printf("2. Inorder Traversal (Non-recursive)\n");
        printf("3. Display Mirror Image of Tree by Creating New Tree\n");
        printf("4. Delete a Node from Tree\n");
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
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                break;

            case 3:
                mirrorRoot = createMirror(root);
                printf("Mirror Tree (Inorder Traversal): ");
                inorderTraversal(mirrorRoot);
                break;

            case 4:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
