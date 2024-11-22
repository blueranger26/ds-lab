#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Define maximum size of the deque

// Double Ended Queue (Deque) structure
struct Deque {
    int arr[MAX];
    int front, rear;
};

// Function to initialize the deque
void initDeque(struct Deque *d) {
    d->front = d->rear = -1;
}

// Function to check if the deque is full
int isFull(struct Deque *d) {
    return d->rear == MAX - 1;
}

// Function to check if the deque is empty
int isEmpty(struct Deque *d) {
    return d->front == -1;
}

// Function to add an element at the rear end (add to queue)
void addRear(struct Deque *d, int value) {
    if (isFull(d)) {
        printf("Deque is Full. Cannot add element at rear.\n");
    } else {
        if (d->front == -1) {  // If the deque is empty
            d->front = 0;
        }
        d->rear++;
        d->arr[d->rear] = value;
        printf("Added %d at the rear.\n", value);
    }
}

// Function to remove an element from the front (remove from queue)
void removeFront(struct Deque *d) {
    if (isEmpty(d)) {
        printf("Deque is Empty. Cannot remove element from front.\n");
    } else {
        int removedValue = d->arr[d->front];
        if (d->front == d->rear) {  // If there's only one element
            d->front = d->rear = -1;
        } else {
            d->front++;
        }
        printf("Removed %d from the front.\n", removedValue);
    }
}

// Function to remove an element from the rear (remove from queue)
void removeRear(struct Deque *d) {
    if (isEmpty(d)) {
        printf("Deque is Empty. Cannot remove element from rear.\n");
    } else {
        int removedValue = d->arr[d->rear];
        if (d->front == d->rear) {  // If there's only one element
            d->front = d->rear = -1;
        } else {
            d->rear--;
        }
        printf("Removed %d from the rear.\n", removedValue);
    }
}

// Function to display the elements in the deque
void displayDeque(struct Deque *d) {
    if (isEmpty(d)) {
        printf("Deque is Empty.\n");
    } else {
        printf("Deque elements: ");
        for (int i = d->front; i <= d->rear; i++) {
            printf("%d ", d->arr[i]);
        }
        printf("\n");
    }
}

int main() {
    struct Deque d;
    initDeque(&d);

    int choice, value;

    do {
        printf("\nDouble Ended Queue Operations (Input Restricted):\n");
        printf("1. Add element at Rear\n");
        printf("2. Remove element from Front\n");
        printf("3. Remove element from Rear\n");
        printf("4. Display Deque\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to add at rear: ");
                scanf("%d", &value);
                addRear(&d, value);
                break;

            case 2:
                removeFront(&d);
                break;

            case 3:
                removeRear(&d);
                break;

            case 4:
                displayDeque(&d);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}
