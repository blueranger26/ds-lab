#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in a threaded binary tree
typedef struct Node {
    int data;
    struct Node *left, *right;
    int rightThread;  // If 1, the right pointer is a thread (points to inorder successor)
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->rightThread = 0; // Initially the right child is not a thread
    return newNode;
}

// Function to insert a node in the threaded binary tree
void insert(Node** root, int data) {
    Node* newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    Node* current = *root;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            if (current->left == NULL) break;
            current = current->left;
        } else {
            if (current->right == NULL || current->rightThread == 1) break;
            current = current->right;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->rightThread = parent->rightThread;
        parent->right = newNode;
        parent->rightThread = 1; // Mark the right pointer as a thread
    }
}

// Function to set the inorder threads
void setInorderThreads(Node* root) {
    Node* prev = NULL;
    Node* current = root;
    
    // Inorder traversal to set the threads
    while (current != NULL) {
        if (current->left == NULL) {
            if (prev != NULL) {
                prev->right = current;
                prev->rightThread = 1;
            }
            prev = current;
            current = current->right;
        } else {
            Node* predecessor = current->left;
            while (predecessor->right != NULL && predecessor->right != current) {
                predecessor = predecessor->right;
            }
            if (predecessor->right == NULL) {
                predecessor->right = current;
                predecessor->rightThread = 0;
                current = current->left;
            } else {
                predecessor->right = NULL;
                predecessor->rightThread = 1;
                if (prev != NULL) {
                    prev->right = current;
                    prev->rightThread = 1;
                }
                prev = current;
                current = current->right;
            }
        }
    }
}

// Function to perform inorder traversal using threads
void inorderTraversal(Node* root) {
    Node* current = root;
    while (current != NULL) {
        while (current->left != NULL) {
            current = current->left;
        }
        
        printf("%d ", current->data);
        
        while (current->rightThread == 1) {
            current = current->right;
            printf("%d ", current->data);
        }
        
        current = current->right;
    }
}

// Preorder traversal using inorder threads
void preorderTraversal(Node* root) {
    Node* current = root;
    while (current != NULL) {
        printf("%d ", current->data);
        
        if (current->left != NULL) {
            current = current->left;
        } else if (current->rightThread == 1) {
            current = current->right;
        } else {
            break;
        }
    }
}

// Postorder traversal using inorder threads
void postorderTraversal(Node* root) {
    Node* current = root;
    Node* prev = NULL;
    
    while (current != NULL) {
        while (current->left != NULL) {
            current = current->left;
        }
        
        if (current->rightThread == 1 || current->right == prev) {
            printf("%d ", current->data);
            prev = current;
            current = current->right;
        } else {
            current = current->right;
        }
    }
}

// Main menu driven function
int main() {
    Node* root = NULL;
    int choice, value;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert a node\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(&root, value);
                setInorderThreads(root);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
