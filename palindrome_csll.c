#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a node in the circular singly linked list
typedef struct Node {
    char data;
    struct Node* next;
} Node;

// Function to create a new node with the given character
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode;  // Points to itself initially
    return newNode;
}

// Function to add a node at the end of the circular singly linked list
void addNode(Node** head, char data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;  // Makes it circular
    }
}

// Function to check if the string is a palindrome
int isPalindrome(Node* head) {
    if (head == NULL || head->next == head) {
        return 1;  // Empty list or single character is always a palindrome
    }

    // Find the middle of the circular list using slow and fast pointers
    Node *slow = head, *fast = head;
    while (fast != NULL && fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Slow pointer is now at the middle of the list
    Node* secondHalf = slow->next;
    slow->next = head;  // Break the circular link for the first half
    Node* prev = NULL;
    Node* current = secondHalf;

    // Reverse the second half of the list
    while (current != head) {
        Node* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    // Compare the first half and the reversed second half
    Node* firstHalf = head;
    Node* secondHalfReversed = prev;
    while (secondHalfReversed != NULL) {
        if (firstHalf->data != secondHalfReversed->data) {
            return 0;  // Not a palindrome
        }
        firstHalf = firstHalf->next;
        secondHalfReversed = secondHalfReversed->next;
    }

    return 1;  // Palindrome
}

// Function to display the circular linked list
void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* temp = head;
    do {
        printf("%c ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main() {
    char str[100];
    Node* head = NULL;

    printf("Enter a string: ");
    scanf("%s", str);

    // Store each character of the string in a circular linked list
    for (int i = 0; i < strlen(str); i++) {
        addNode(&head, str[i]);
    }

    // Display the circular linked list
    printf("Circular Linked List: ");
    displayList(head);

    // Check if the string is a palindrome
    if (isPalindrome(head)) {
        printf("The string is a palindrome.\n");
    } else {
        printf("The string is not a palindrome.\n");
    }

    return 0;
}
