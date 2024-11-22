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
    newNode->next = newNode;  // The node points to itself initially
    return newNode;
}

// Function to add a new node to the circular singly linked list
void addNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        // Traverse the list to find the last node (the node whose next is head)
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;  // Link last node to the new node
        newNode->next = *head; // Make the new node point to the head to maintain circular structure
    }
}

// Function to print the circular singly linked list
void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Function to solve the Josephus problem
int josephusProblem(Node** head, int k) {
    Node* current = *head;
    Node* prev = NULL;  // To keep track of the previous node

    while (current->next != current) {  // While more than one node is left
        // Traverse k-1 steps
        for (int i = 1; i < k; i++) {
            prev = current;
            current = current->next;
        }
        // Delete the k-th node
        prev->next = current->next;  // The previous node points to the next node
        free(current);  // Free the memory of the deleted node
        current = prev->next;  // Move to the next node after the deletion
    }
    return current->data;  // The last remaining person
}

// Main function to test the Josephus problem
int main() {
    Node* head = NULL;
    int n, k;

    printf("Enter the number of people: ");
    scanf("%d", &n);
    printf("Enter the step size (k): ");
    scanf("%d", &k);

    // Create the circular singly linked list with n nodes
    for (int i = 1; i <= n; i++) {
        addNode(&head, i);
    }

    printf("Initial list: ");
    displayList(head);

    // Solve the Josephus problem
    int lastPerson = josephusProblem(&head, k);
    printf("The last remaining person is: %d\n", lastPerson);

    return 0;
}
