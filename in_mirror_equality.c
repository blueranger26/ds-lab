#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Non-recursive inorder traversal
void inorderTraversal(Node* root) {
    Stack* stack = NULL;
    Node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// Function to create the mirror image of a tree
Node* createMirror(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    Node* newRoot = createNode(root->data);
    newRoot->left = createMirror(root->right);
    newRoot->right = createMirror(root->left);
    return newRoot;
}

// Function to check if two trees are equal
bool areTreesEqual(Node* tree1, Node* tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        return true;
    }
    if (tree1 == NULL || tree2 == NULL) {
        return false;
    }
    return (tree1->data == tree2->data) &&
           areTreesEqual(tree1->left, tree2->left) &&
           areTreesEqual(tree1->right, tree2->right);
}

// Function to display the tree (inorder)
void displayTree(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    inorderTraversal(root);
}

// Main function
int main() {
    Node* root = NULL;
    Node* mirrorRoot = NULL;
    Node* secondTree = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Node in Tree\n");
        printf("2. Inorder Traversal (Non-recursive)\n");
        printf("3. Display Mirror Image of Tree (Create New Tree)\n");
        printf("4. Check Equality of Two Trees\n");
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
                printf("Creating and displaying mirror image of the tree...\n");
                mirrorRoot = createMirror(root);
                printf("Mirror Tree (Inorder Traversal): ");
                inorderTraversal(mirrorRoot);
                break;

            case 4:
                printf("Creating a new tree for comparison.\n");
                while (1) {
                    printf("Enter data to insert into the second tree (-1 to stop): ");
                    scanf("%d", &data);
                    if (data == -1) {
                        break;
                    }
                    secondTree = insertNode(secondTree, data);
                }
                if (areTreesEqual(root, secondTree)) {
                    printf("The two trees are equal.\n");
                } else {
                    printf("The two trees are not equal.\n");
                }
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
