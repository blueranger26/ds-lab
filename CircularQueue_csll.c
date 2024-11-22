#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the circular singly linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node with the given data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode;  // For a circular list, the next points to itself initially
    return newNode;
}

// Function to add (enqueue) an element to the queue
void enqueue(Node** front, Node** rear, int data) {
    Node* newNode = createNode(data);

    if (*front == NULL) {
        *front = *rear = newNode;  // If the queue is empty, the front and rear both point to the new node
    } else {
        (*rear)->next = newNode;  // Rear's next points to the new node
        *rear = newNode;          // Update rear to the new node
        (*rear)->next = *front;   // Rear's next points to front to maintain the circular nature
    }
}

// Function to delete (dequeue) an element from the queue
int dequeue(Node** front, Node** rear) {
    if (*front == NULL) {
        printf("Queue is empty!\n");
        return -1;  // Error value
    }

    int data = (*front)->data;
    if (*front == *rear) {
        // If there's only one element in the queue
        free(*front);
        *front = *rear = NULL;
    } else {
        // Move the front pointer to the next node
        Node* temp = *front;
        *front = (*front)->next;
        (*rear)->next = *front;  // Rear's next points to the new front
        free(temp);
    }
    return data;
}

// Function to display all elements in the queue
void display(Node* front) {
    if (front == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    Node* temp = front;
    printf("Queue elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);  // Stop when we reach the front node again
    printf("\n");
}

// Main function to test the circular queue operations
int main() {
    Node* front = NULL;
    Node* rear = NULL;
    int choice, value;

    while (1) {
        printf("\nCircular Queue Operations Menu:\n");
        printf("1. Add (Enqueue)\n");
        printf("2. Delete (Dequeue)\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to add: ");
                scanf("%d", &value);
                enqueue(&front, &rear, value);
                break;

            case 2:
                value = dequeue(&front, &rear);
                if (value != -1) {
                    printf("Deleted value: %d\n", value);
                }
                break;

            case 3:
                display(front);
                break;

            case 4:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
