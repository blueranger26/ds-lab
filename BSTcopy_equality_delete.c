#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Function to copy a tree (non-recursive)
Node* copyTree(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    Node* copyRoot = createNode(root->data);
    Node* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;
    
    stack1[++top1] = root;
    stack2[++top2] = copyRoot;

    while (top1 >= 0) {
        Node* current = stack1[top1--];
        Node* currentCopy = stack2[top2--];

        if (current->left != NULL) {
            currentCopy->left = createNode(current->left->data);
            stack1[++top1] = current->left;
            stack2[++top2] = currentCopy->left;
        }

        if (current->right != NULL) {
            currentCopy->right = createNode(current->right->data);
            stack1[++top1] = current->right;
            stack2[++top2] = currentCopy->right;
        }
    }

    return copyRoot;
}

// Function to check if two trees are equal (non-recursive)
bool areEqual(Node* root1, Node* root2) {
    if (root1 == NULL && root2 == NULL) {
        return true;
    }

    if (root1 == NULL || root2 == NULL) {
        return false;
    }

    Node* stack1[100], *stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root1;
    stack2[++top2] = root2;

    while (top1 >= 0) {
        Node* current1 = stack1[top1--];
        Node* current2 = stack2[top2--];

        if (current1->data != current2->data) {
            return false;
        }

        if (current1->left != NULL && current2->left != NULL) {
            stack1[++top1] = current1->left;
            stack2[++top2] = current2->left;
        } else if (current1->left != NULL || current2->left != NULL) {
            return false;
        }

        if (current1->right != NULL && current2->right != NULL) {
            stack1[++top1] = current1->right;
            stack2[++top2] = current2->right;
        } else if (current1->right != NULL || current2->right != NULL) {
            return false;
        }
    }

    return true;
}

// Function to find the minimum value node (for deletion)
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the tree
Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return NULL;
    }

    // Non-recursive approach to find the node to delete
    Node* parent = NULL;
    Node* current = root;

    while (current != NULL && current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Node with value %d not found.\n", data);
        return root;
    }

    // Case 1: Node with only one child or no child
    if (current->left == NULL) {
        if (parent == NULL) {
            Node* temp = current->right;
            free(current);
            return temp;
        } else if (current == parent->left) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    } else if (current->right == NULL) {
        if (parent == NULL) {
            Node* temp = current->left;
            free(current);
            return temp;
        } else if (current == parent->left) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    }

    // Case 2: Node with two children
    else {
        Node* temp = findMin(current->right);
        int minValue = temp->data;
        root = deleteNode(root, temp->data);
        current->data = minValue;
    }

    return root;
}

// Function to display the tree (Inorder traversal for simplicity)
void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }

    Node* stack[100];
    int top = -1;
    Node* current = root;

    while (top >= 0 || current != NULL) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }

    printf("\n");
}

// Main function
int main() {
    Node* root1 = NULL;
    Node* root2 = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node in Tree 1\n");
        printf("2. Insert Node in Tree 2\n");
        printf("3. Copy Tree\n");
        printf("4. Check Equality of Two Trees\n");
        printf("5. Delete Node from Tree\n");
        printf("6. Inorder Traversal of Tree 1\n");
        printf("7. Inorder Traversal of Tree 2\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert in Tree 1: ");
                scanf("%d", &data);
                root1 = insertNode(root1, data);
                break;

            case 2:
                printf("Enter data to insert in Tree 2: ");
                scanf("%d", &data);
                root2 = insertNode(root2, data);
                break;

            case 3:
                {
                    Node* copiedTree = copyTree(root1);
                    printf("Copied Tree (Inorder Traversal): ");
                    inorderTraversal(copiedTree);
                }
                break;

            case 4:
                if (areEqual(root1, root2)) {
                    printf("The trees are equal.\n");
                } else {
                    printf("The trees are not equal.\n");
                }
                break;

            case 5:
                printf("Enter data to delete from Tree 1: ");
                scanf("%d", &data);
                root1 = deleteNode(root1, data);
                break;

            case 6:
                printf("Inorder Traversal of Tree 1: ");
                inorderTraversal(root1);
                break;

            case 7:
                printf("Inorder Traversal of Tree 2: ");
                inorderTraversal(root2);
                break;

            case 8:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
