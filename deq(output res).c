#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Maximum size of the deque

// Declare a deque structure
struct Deque {
    int arr[MAX];
    int front;
    int rear;
};

// Initialize the deque
void initDeque(struct Deque* dq) {
    dq->front = -1;
    dq->rear = -1;
}

// Check if the deque is full
int isFull(struct Deque* dq) {
    return (dq->rear + 1) % MAX == dq->front;
}

// Check if the deque is empty
int isEmpty(struct Deque* dq) {
    return dq->front == -1;
}

// Add element at the front of the deque
void insertFront(struct Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Deque is full. Cannot insert at front.\n");
        return;
    }
    if (isEmpty(dq)) {
        dq->front = dq->rear = 0;
    } else {
        dq->front = (dq->front - 1 + MAX) % MAX;
    }
    dq->arr[dq->front] = value;
}

// Add element at the rear of the deque
void insertRear(struct Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Deque is full. Cannot insert at rear.\n");
        return;
    }
    if (isEmpty(dq)) {
        dq->front = dq->rear = 0;
    } else {
        dq->rear = (dq->rear + 1) % MAX;
    }
    dq->arr[dq->rear] = value;
}

// Remove element from the front of the deque
void deleteFront(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty. Cannot delete from front.\n");
        return;
    }
    printf("Deleted element from front: %d\n", dq->arr[dq->front]);
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1; // Deque becomes empty
    } else {
        dq->front = (dq->front + 1) % MAX;
    }
}

// Remove element from the rear of the deque
void deleteRear(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty. Cannot delete from rear.\n");
        return;
    }
    printf("Deleted element from rear: %d\n", dq->arr[dq->rear]);
    if (dq->front == dq->rear) {
        dq->front = dq->rear = -1; // Deque becomes empty
    } else {
        dq->rear = (dq->rear - 1 + MAX) % MAX;
    }
}

// Display the elements of the deque
void display(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque elements: ");
    int i = dq->front;
    while (i != dq->rear) {
        printf("%d ", dq->arr[i]);
        i = (i + 1) % MAX;
    }
    printf("%d\n", dq->arr[dq->rear]);
}

// Main function to test the deque implementation
int main() {
    struct Deque dq;
    initDeque(&dq);
    
    int choice, value;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert at Front\n");
        printf("2. Insert at Rear\n");
        printf("3. Delete from Front\n");
        printf("4. Delete from Rear\n");
        printf("5. Display Deque\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(&dq, value);
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(&dq, value);
                break;
            case 3:
                deleteFront(&dq);
                break;
            case 4:
                deleteRear(&dq);
                break;
            case 5:
                display(&dq);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
