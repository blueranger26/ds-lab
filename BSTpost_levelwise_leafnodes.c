#include <stdio.h>
#include <stdlib.h>

// Define the structure for a binary tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Define a queue structure for level-order traversal
typedef struct Queue {
    Node* data;
    struct Queue* next;
} Queue;

// Define a stack structure for non-recursive postorder traversal
typedef struct Stack {
    Node* data;
    struct Stack* next;
    int visited;
} Stack;

// Function to create a new node for the binary tree
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

// Stack operations for non-recursive postorder traversal
void pushStack(Stack** top, Node* node, int visited) {
    Stack* newStackNode = (Stack*)malloc(sizeof(Stack));
    newStackNode->data = node;
    newStackNode->visited = visited;
    newStackNode->next = *top;
    *top = newStackNode;
}

Stack* popStack(Stack** top) {
    if (*top == NULL) {
        return NULL;
    }
    Stack* temp = *top;
    *top = (*top)->next;
    return temp;
}

int isStackEmpty(Stack* top) {
    return top == NULL;
}

// Function for non-recursive postorder traversal
void postorderTraversal(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Stack* stack = NULL;
    pushStack(&stack, root, 0);

    while (!isStackEmpty(stack)) {
        Stack* topNode = popStack(&stack);
        if (topNode->visited == 1) {
            printf("%d ", topNode->data->data);
            free(topNode);
        } else {
            pushStack(&stack, topNode->data, 1);
            if (topNode->data->right) {
                pushStack(&stack, topNode->data->right, 0);
            }
            if (topNode->data->left) {
                pushStack(&stack, topNode->data->left, 0);
            }
            free(topNode);
        }
    }
    printf("\n");
}

// Queue operations for level-order traversal
void enqueue(Queue** front, Queue** rear, Node* node) {
    Queue* newQueueNode = (Queue*)malloc(sizeof(Queue));
    newQueueNode->data = node;
    newQueueNode->next = NULL;

    if (*rear == NULL) {
        *front = newQueueNode;
        *rear = newQueueNode;
    } else {
        (*rear)->next = newQueueNode;
        *rear = newQueueNode;
    }
}

Node* dequeue(Queue** front, Queue** rear) {
    if (*front == NULL) {
        return NULL;
    }

    Queue* temp = *front;
    Node* node = temp->data;
    *front = (*front)->next;
    if (*front == NULL) {
        *rear = NULL;
    }
    free(temp);
    return node;
}

int isQueueEmpty(Queue* front) {
    return front == NULL;
}

// Function for level-order traversal
void levelOrderTraversal(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Queue* front = NULL;
    Queue* rear = NULL;
    enqueue(&front, &rear, root);

    while (!isQueueEmpty(front)) {
        Node* current = dequeue(&front, &rear);
        printf("%d ", current->data);
        if (current->left) {
            enqueue(&front, &rear, current->left);
        }
        if (current->right) {
            enqueue(&front, &rear, current->right);
        }
    }
    printf("\n");
}

// Function to display leaf nodes
void displayLeafNodes(Node* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    Stack* stack = NULL;
    pushStack(&stack, root, 0);

    while (!isStackEmpty(stack)) {
        Stack* topNode = popStack(&stack);
        Node* current = topNode->data;

        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }

        if (current->right) {
            pushStack(&stack, current->right, 0);
        }
        if (current->left) {
            pushStack(&stack, current->left, 0);
        }

        free(topNode);
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
        printf("3. Level Order Traversal\n");
        printf("4. Display Leaf Nodes\n");
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
                printf("Level Order Traversal: ");
                levelOrderTraversal(root);
                break;

            case 4:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
