#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node with the given data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to add a node at the front of the deque
void addFront(Node** front, Node** rear, int data) {
    Node* newNode = createNode(data);
    if (*front == NULL) {
        *front = *rear = newNode;
    } else {
        newNode->next = *front;
        (*front)->prev = newNode;
        *front = newNode;
    }
    printf("Added %d to the front.\n", data);
}

// Function to add a node at the rear of the deque
void addRear(Node** front, Node** rear, int data) {
    Node* newNode = createNode(data);
    if (*rear == NULL) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        newNode->prev = *rear;
        *rear = newNode;
    }
    printf("Added %d to the rear.\n", data);
}

// Function to delete a node from the front of the deque
void deleteFront(Node** front, Node** rear) {
    if (*front == NULL) {
        printf("Deque is empty, nothing to delete.\n");
        return;
    }
    Node* temp = *front;
    if (*front == *rear) {  // Only one element
        *front = *rear = NULL;
    } else {
        *front = (*front)->next;
        (*front)->prev = NULL;
    }
    printf("Deleted %d from the front.\n", temp->data);
    free(temp);
}

// Function to delete a node from the rear of the deque
void deleteRear(Node** front, Node** rear) {
    if (*rear == NULL) {
        printf("Deque is empty, nothing to delete.\n");
        return;
    }
    Node* temp = *rear;
    if (*front == *rear) {  // Only one element
        *front = *rear = NULL;
    } else {
        *rear = (*rear)->prev;
        (*rear)->next = NULL;
    }
    printf("Deleted %d from the rear.\n", temp->data);
    free(temp);
}

// Function to display the elements in the deque
void displayDeque(Node* front) {
    if (front == NULL) {
        printf("Deque is empty.\n");
        return;
    }
    Node* temp = front;
    printf("Deque elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to test the deque operations
int main() {
    Node* front = NULL;
    Node* rear = NULL;
    int choice, data;

    while (1) {
        printf("\nDeque Operations Menu:\n");
        printf("1. Add to Front\n");
        printf("2. Add to Rear\n");
        printf("3. Delete from Front\n");
        printf("4. Delete from Rear\n");
        printf("5. Display Deque\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to add to front: ");
                scanf("%d", &data);
                addFront(&front, &rear, data);
                break;
            case 2:
                printf("Enter data to add to rear: ");
                scanf("%d", &data);
                addRear(&front, &rear, data);
                break;
            case 3:
                deleteFront(&front, &rear);
                break;
            case 4:
                deleteRear(&front, &rear);
                break;
            case 5:
                displayDeque(front);
                break;
            case 6:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
