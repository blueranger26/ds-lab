#include <stdio.h>
#include <stdlib.h>

// Define the structure for each node in the circular singly linked list
typedef struct Node {
    int digit;        // Store a single digit
    struct Node* next;
} Node;

// Function to create a new node with the given digit
Node* createNode(int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->digit = digit;
    newNode->next = NULL;
    return newNode;
}

// Function to create a circular singly linked list from a number
Node* createCircularList(int num) {
    Node* head = NULL;
    Node* tail = NULL;

    // Process each digit of the number
    while (num > 0) {
        int digit = num % 10;
        Node* newNode = createNode(digit);

        // If the list is empty, make this the first node
        if (head == NULL) {
            head = tail = newNode;
            head->next = head;  // Point to itself, making it circular
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;  // Circular link
        }

        num /= 10;
    }

    return head;
}

// Function to display the circular singly linked list
void displayList(Node* head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    Node* temp = head;
    do {
        printf("%d ", temp->digit);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Function to add two circular singly linked lists (handling carry)
Node* addLists(Node* head1, Node* head2) {
    Node* result = NULL;
    Node* tail = NULL;
    int carry = 0;

    Node* temp1 = head1;
    Node* temp2 = head2;

    // Traverse both lists and add the digits
    do {
        int sum = temp1->digit + temp2->digit + carry;
        carry = sum / 10;  // Calculate the new carry
        sum = sum % 10;    // Get the digit to store

        Node* newNode = createNode(sum);

        if (result == NULL) {
            result = tail = newNode;
            result->next = result;  // Circular link
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = result;  // Circular link
        }

        temp1 = temp1->next;
        temp2 = temp2->next;
    } while (temp1 != head1 || temp2 != head2); // Continue until both lists are fully traversed

    // If there is a carry left, add it as a new node
    if (carry != 0) {
        Node* newNode = createNode(carry);
        tail->next = newNode;
        tail = newNode;
        tail->next = result;  // Circular link
    }

    return result;
}

// Function to subtract one circular singly linked list from another (handling borrow)
Node* subtractLists(Node* head1, Node* head2) {
    Node* result = NULL;
    Node* tail = NULL;
    int borrow = 0;

    Node* temp1 = head1;
    Node* temp2 = head2;

    // Traverse both lists and subtract the digits
    do {
        int diff = temp1->digit - temp2->digit - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;  // Set borrow if difference is negative
        } else {
            borrow = 0;  // Reset borrow if difference is non-negative
        }

        Node* newNode = createNode(diff);

        if (result == NULL) {
            result = tail = newNode;
            result->next = result;  // Circular link
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = result;  // Circular link
        }

        temp1 = temp1->next;
        temp2 = temp2->next;
    } while (temp1 != head1 || temp2 != head2); // Continue until both lists are fully traversed

    // If there's a borrow left, adjust (not likely for positive integers)
    if (borrow != 0) {
        printf("Subtraction result would be negative. Unable to process.\n");
        return NULL;
    }

    return result;
}

// Main function to drive the program
int main() {
    int num1, num2;

    printf("Enter first six-digit number: ");
    scanf("%d", &num1);
    printf("Enter second six-digit number: ");
    scanf("%d", &num2);

    // Create circular singly linked lists for both numbers
    Node* head1 = createCircularList(num1);
    Node* head2 = createCircularList(num2);

    printf("\nFirst number as list: ");
    displayList(head1);

    printf("Second number as list: ");
    displayList(head2);

    // Add the two numbers
    Node* sum = addLists(head1, head2);
    printf("\nSum of the two numbers: ");
    displayList(sum);

    // Subtract the two numbers
    Node* diff = subtractLists(head1, head2);
    if (diff != NULL) {
        printf("\nDifference of the two numbers: ");
        displayList(diff);
    }

    return 0;
}
