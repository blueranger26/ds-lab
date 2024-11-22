#include <stdio.h>
#include <stdlib.h>

// Define structure for polynomial node
typedef struct Node {
    int coeff;      // Coefficient
    int powX;       // Power of x
    int powY;       // Power of y
    struct Node* next; // Pointer to the next node
    struct Node* prev; // Pointer to the previous node
} Node;

// Function to create a new node
Node* createNode(int coeff, int powX, int powY) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->powX = powX;
    newNode->powY = powY;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to add a node to the polynomial
Node* addNode(Node* head, int coeff, int powX, int powY) {
    if (coeff == 0) return head; // Ignore zero coefficient

    Node* newNode = createNode(coeff, powX, powY);
    if (head == NULL) {
        return newNode;
    }

    Node* temp = head;
    while (temp->next != NULL &&
           (temp->powX > powX || (temp->powX == powX && temp->powY > powY))) {
        temp = temp->next;
    }

    if (temp->powX == powX && temp->powY == powY) {
        temp->coeff += coeff;
        if (temp->coeff == 0) { // Remove node if coefficient becomes zero
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == head) head = temp->next;
            free(temp);
        }
        return head;
    }

    if (temp->powX < powX || (temp->powX == powX && temp->powY < powY)) {
        if (temp->prev) {
            temp->prev->next = newNode;
        } else {
            head = newNode;
        }
        newNode->prev = temp->prev;
        newNode->next = temp;
        temp->prev = newNode;
    } else {
        temp->next = newNode;
        newNode->prev = temp;
    }
    return head;
}

// Function to accept a polynomial
Node* acceptPolynomial() {
    Node* head = NULL;
    int n, coeff, powX, powY;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient, power of x, and power of y (e.g., coeff powX powY): ");
        scanf("%d %d %d", &coeff, &powX, &powY);
        head = addNode(head, coeff, powX, powY);
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
        printf("%d*x^%d*y^%d", temp->coeff, temp->powX, temp->powY);
        if (temp->next != NULL) printf(" + ");
        temp = temp->next;
    }
    printf("\n");
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;

    while (poly1 != NULL) {
        result = addNode(result, poly1->coeff, poly1->powX, poly1->powY);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        result = addNode(result, poly2->coeff, poly2->powX, poly2->powY);
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
