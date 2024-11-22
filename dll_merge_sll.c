#include <stdio.h>
#include <stdlib.h>

// Define the structure for each node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node with the given data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the end of a doubly linked list
void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to display the doubly linked list
void displayList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to merge two sorted doubly linked lists into one sorted list
Node* mergeSortedLists(Node* head1, Node* head2) {
    // If either of the lists is empty, return the other list
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    // Initialize a dummy node to help in merging
    Node* mergedHead = NULL;
    Node* mergedTail = NULL;

    // Traverse both lists and merge them in sorted order
    while (head1 != NULL && head2 != NULL) {
        Node* temp;
        if (head1->data <= head2->data) {
            temp = head1;
            head1 = head1->next;
        } else {
            temp = head2;
            head2 = head2->next;
        }

        // If merged list is empty, set the first node
        if (mergedHead == NULL) {
            mergedHead = temp;
            mergedTail = temp;
        } else {
            mergedTail->next = temp;
            temp->prev = mergedTail;
            mergedTail = temp;
        }
    }

    // If there are any remaining nodes in either list, append them
    if (head1 != NULL) {
        mergedTail->next = head1;
        head1->prev = mergedTail;
    } else if (head2 != NULL) {
        mergedTail->next = head2;
        head2->prev = mergedTail;
    }

    return mergedHead;
}

// Main function to drive the program
int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    int n1, n2, data;

    // Input the first sorted doubly linked list
    printf("Enter number of elements in the first sorted list: ");
    scanf("%d", &n1);
    printf("Enter elements for the first sorted list: ");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &data);
        append(&list1, data);
    }

    // Input the second sorted doubly linked list
    printf("Enter number of elements in the second sorted list: ");
    scanf("%d", &n2);
    printf("Enter elements for the second sorted list: ");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &data);
        append(&list2, data);
    }

    // Display the input lists
    printf("\nFirst sorted list: ");
    displayList(list1);

    printf("Second sorted list: ");
    displayList(list2);

    // Merge the two sorted lists
    Node* mergedList = mergeSortedLists(list1, list2);

    // Display the merged sorted list
    printf("\nMerged sorted list: ");
    displayList(mergedList);

    return 0;
}
