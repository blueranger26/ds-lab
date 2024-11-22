#include <stdio.h>
#include <stdlib.h>

// Define structure for polynomial node
typedef struct Node {
    int coeff;      // Coefficient
    int powX;       // Power of x
    int powY;       // Power of y
    struct Node* next; // Pointer to the next node
} Node;

// Function to create a new node
Node* createNode(int coeff, int powX, int powY) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->powX = powX;
    newNode->powY = powY;
    newNode->next = NULL;
    return newNode;
}

// Function to accept a polynomial
Node* acceptPolynomial() {
    Node* head = NULL;
    Node* temp = NULL;
    int n, coeff, powX, powY;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient, power of x, and power of y (e.g., coeff powX powY): ");
        scanf("%d %d %d", &coeff, &powX, &powY);

        Node* newNode = createNode(coeff, powX, powY);

        if (head == NULL) {
            head = temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
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
    Node* temp = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        Node* newNode;
        if (poly1->powX == poly2->powX && poly1->powY == poly2->powY) {
            newNode = createNode(poly1->coeff + poly2->coeff, poly1->powX, poly1->powY);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->powX > poly2->powX || 
                  (poly1->powX == poly2->powX && poly1->powY > poly2->powY)) {
            newNode = createNode(poly1->coeff, poly1->powX, poly1->powY);
            poly1 = poly1->next;
        } else {
            newNode = createNode(poly2->coeff, poly2->powX, poly2->powY);
            poly2 = poly2->next;
        }

        if (result == NULL) {
            result = temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }

    while (poly1 != NULL) {
        Node* newNode = createNode(poly1->coeff, poly1->powX, poly1->powY);
        temp->next = newNode;
        temp = newNode;
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        Node* newNode = createNode(poly2->coeff, poly2->powX, poly2->powY);
        temp->next = newNode;
        temp = newNode;
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
