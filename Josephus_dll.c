#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the circular doubly linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node with the given data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode;
    newNode->prev = newNode;
    return newNode;
}

// Function to add a new node to the circular doubly linked list
void addNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* tail = (*head)->prev;  // Tail is the previous node to head
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = *head;
        (*head)->prev = newNode;
    }
}

// Function to print the circular doubly linked list
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
    while (current->next != current) {  // While more than one node is left
        // Traverse k-1 steps
        for (int i = 1; i < k; i++) {
            current = current->next;
        }
        // Delete the k-th node
        Node* temp = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
        free(temp);
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

    // Create the circular doubly linked list with n nodes
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
