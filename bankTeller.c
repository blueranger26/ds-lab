#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the structure for a customer
typedef struct Customer {
    int customerID;          // Customer ID
    int arrivalTime;         // Time of arrival
    int serviceTime;         // Time required for service
    int waitTime;            // Wait time in the queue
} Customer;

// Define the structure for a priority queue (min-heap)
typedef struct PriorityQueue {
    Customer *customers;     // Array of customers
    int size;                // Current size of the queue
    int capacity;            // Maximum capacity of the queue
} PriorityQueue;

// Function to create a priority queue
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->customers = (Customer*)malloc(capacity * sizeof(Customer));
    return pq;
}

// Function to swap two customers (used for heap property)
void swap(Customer *a, Customer *b) {
    Customer temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the priority queue (min-heap based on arrivalTime)
void heapify(PriorityQueue *pq, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < pq->size && pq->customers[left].arrivalTime < pq->customers[smallest].arrivalTime) {
        smallest = left;
    }
    if (right < pq->size && pq->customers[right].arrivalTime < pq->customers[smallest].arrivalTime) {
        smallest = right;
    }
    if (smallest != idx) {
        swap(&pq->customers[idx], &pq->customers[smallest]);
        heapify(pq, smallest);
    }
}

// Function to insert a customer into the priority queue
void insertCustomer(PriorityQueue *pq, Customer c) {
    if (pq->size == pq->capacity) {
        printf("Priority Queue is full!\n");
        return;
    }

    pq->size++;
    int idx = pq->size - 1;
    pq->customers[idx] = c;

    // Fix the heap property
    while (idx != 0 && pq->customers[(idx - 1) / 2].arrivalTime > pq->customers[idx].arrivalTime) {
        swap(&pq->customers[idx], &pq->customers[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

// Function to extract the customer with the earliest arrival time (min-heap)
Customer extractMin(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Queue is empty!\n");
        Customer emptyCustomer = {0, 0, 0, 0};
        return emptyCustomer;
    }

    // The root contains the minimum arrival time
    Customer root = pq->customers[0];

    // Replace root with the last customer
    pq->customers[0] = pq->customers[pq->size - 1];
    pq->size--;

    // Heapify the root element
    heapify(pq, 0);

    return root;
}

// Function to simulate the bank teller process
void simulateBankTellers(PriorityQueue *pq, int numTellers) {
    int totalWaitTime = 0;
    int totalCustomers = pq->size;
    int servedCustomers = 0;

    printf("Simulating bank teller operation...\n");

    // Create an array of available tellers
    int *tellers = (int*)malloc(numTellers * sizeof(int)); // Keep track of when each teller will be free
    for (int i = 0; i < numTellers; i++) {
        tellers[i] = 0; // Initially all tellers are free at time 0
    }

    while (pq->size > 0) {
        // Extract the customer with the earliest arrival time
        Customer currentCustomer = extractMin(pq);
        
        // Find the next available teller (who is free the earliest)
        int minWaitTime = tellers[0];
        int selectedTeller = 0;
        for (int i = 1; i < numTellers; i++) {
            if (tellers[i] < minWaitTime) {
                minWaitTime = tellers[i];
                selectedTeller = i;
            }
        }

        // Calculate the wait time for this customer
        currentCustomer.waitTime = (minWaitTime > currentCustomer.arrivalTime) ? (minWaitTime - currentCustomer.arrivalTime) : 0;
        totalWaitTime += currentCustomer.waitTime;

        // Update the selected teller's available time
        tellers[selectedTeller] = currentCustomer.arrivalTime + currentCustomer.waitTime + currentCustomer.serviceTime;

        // Print the customer details and wait time
        printf("Customer %d arrived at %d, wait time: %d minutes, served by Teller %d\n", 
               currentCustomer.customerID, currentCustomer.arrivalTime, currentCustomer.waitTime, selectedTeller + 1);

        servedCustomers++;
    }

    printf("\nTotal number of customers served: %d\n", servedCustomers);
    printf("Average wait time: %.2f minutes\n", (double)totalWaitTime / servedCustomers);

    free(tellers);
}

int main() {
    // Set up the priority queue for customers
    PriorityQueue *pq = createPriorityQueue(10);

    // Seed random number generator
    srand(time(0));

    // Simulate adding customers to the queue with random arrival and service times
    for (int i = 0; i < 10; i++) {
        Customer c;
        c.customerID = i + 1;
        c.arrivalTime = rand() % 100;  // Random arrival time (0-99)
        c.serviceTime = rand() % 10 + 1;  // Random service time (1-10)
        insertCustomer(pq, c);
    }

    // Simulate the bank teller process with 2 tellers
    simulateBankTellers(pq, 2);  // Use 2 tellers to see the effect on wait times

    // Clean up
    free(pq->customers);
    free(pq);

    return 0;
}
