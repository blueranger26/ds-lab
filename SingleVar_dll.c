#include <stdio.h>
#include <stdlib.h>

// Define structure for polynomial node
typedef struct Node {
    int coeff;      // Coefficient
    int power;      // Power of the variable
    struct Node* next; // Pointer to the next node
    struct Node* prev; // Pointer to the previous node
} Node;

// Function to create a new node
Node* createNode(int coeff, int power) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to add a node in descending order of power
Node* addNode(Node* head, int coeff, int power) {
    if (coeff == 0) return head; // Ignore zero coefficient

    Node* newNode = createNode(coeff, power);
    if (head == NULL || head->power < power) {
        newNode->next = head;
        if (head) head->prev = newNode;
        return newNode;
    }

    Node* temp = head;
    while (temp->next != NULL && temp->next->power >= power) {
        temp = temp->next;
    }

    if (temp->power == power) {
        temp->coeff += coeff;
        if (temp->coeff == 0) { // Remove node if coefficient becomes zero
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == head) head = temp->next;
            free(temp);
        }
        return head;
    }

    newNode->next = temp->next;
    if (temp->next) temp->next->prev = newNode;
    temp->next = newNode;
    newNode->prev = temp;

    return head;
}

// Function to accept a polynomial
Node* acceptPolynomial() {
    Node* head = NULL;
    int n, coeff, power;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and power (e.g., coeff power): ");
        scanf("%d %d", &coeff, &power);
        head = addNode(head, coeff, power);
    }
    return head;
}

// Function to display a polynomial
void displayPolynomial(Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        printf("%d*x^%d", temp->coeff, temp->power);
        if (temp->next != NULL) printf(" + ");
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;

    while (poly1 != NULL) {
        result = addNode(result, poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        result = addNode(result, poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }

    return result;
}

// Main function
int main() {
    Node *poly1, *poly2, *sum;

    printf("Enter the first polynomial:\n");
    poly1 = acceptPolynomial();

    printf("Enter the second polynomial:\n");
    poly2 = acceptPolynomial();

    printf("\nFirst Polynomial: ");
    displayPolynomial(poly1);

    printf("Second Polynomial: ");
    displayPolynomial(poly2);

    sum = addPolynomials(poly1, poly2);

    printf("\nSum of Polynomials: ");
    displayPolynomial(sum);

    return 0;
}
