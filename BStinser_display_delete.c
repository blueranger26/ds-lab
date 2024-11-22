#include <stdio.h>
#include <stdlib.h>

// Node structure for the Binary Search Tree (BST)
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert a node into the BST
Node* insertNode(Node* root, int data) {
    Node *newNode = createNode(data), *parent = NULL, *current = root;

    while (current != NULL) {
        parent = current;
        current = (data < current->data) ? current->left : current->right;
    }
    if (parent == NULL) return newNode;

    if (data < parent->data) parent->left = newNode;
    else parent->right = newNode;

    return root;
}

// Calculate height of the tree
int height(Node* root) {
    if (!root) return 0;
    Node* stack[100];
    int top = -1, h = 0;
    stack[++top] = root;

    while (top >= 0) {
        Node* current = stack[top--];
        if (current) {
            h++;
            stack[++top] = current->left;
            stack[++top] = current->right;
        }
    }
    return h;
}

// Find minimum value node
Node* findMin(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

// Delete a node from the tree
Node* deleteNode(Node* root, int data) {
    if (!root) return NULL;
    Node *parent = NULL, *current = root;

    while (current && current->data != data) {
        parent = current;
        current = (data < current->data) ? current->left : current->right;
    }

    if (!current) return root;

    if (!current->left && !current->right) {
        if (!parent) return NULL;
        if (parent->left == current) parent->left = NULL;
        else parent->right = NULL;
    } else if (!current->left || !current->right) {
        Node* child = (current->left) ? current->left : current->right;
        if (!parent) return child;
        if (parent->left == current) parent->left = child;
        else parent->right = child;
    } else {
        Node* temp = findMin(current->right);
        current->data = temp->data;
        root = deleteNode(root, temp->data);
    }
    free(current);
    return root;
}

// Inorder traversal of the tree
void inorderTraversal(Node* root) {
    if (!root) return;
    Node* stack[100];
    int top = -1;
    Node* current = root;
    while (top >= 0 || current) {
        while (current) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// Main function to handle the menu-driven program
int main() {
    Node* root = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n1. Insert Node\n2. Height of Tree\n3. Delete Node\n4. Inorder Traversal\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Enter data: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                printf("Height of tree: %d\n", height(root));
                break;
            case 3:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            case 4:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
