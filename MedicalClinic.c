#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a patient
typedef struct Patient {
    int patientID;        // Unique ID for each patient
    char name[50];        // Patient's name
    int arrivalTime;      // Time the patient arrives at the clinic
} Patient;

// Define the structure for the queue (linear queue)
typedef struct Queue {
    Patient *patients;    // Array to hold the patients
    int front;            // Index for the front of the queue
    int rear;             // Index for the rear of the queue
    int capacity;         // Maximum capacity of the queue
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = -1;
    q->rear = -1;
    q->patients = (Patient*)malloc(capacity * sizeof(Patient));
    return q;
}

// Function to check if the queue is full
int isFull(Queue *q) {
    return (q->rear == q->capacity - 1);
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    return (q->front == -1);
}

// Function to enqueue a patient
void enqueue(Queue *q, Patient p) {
    if (isFull(q)) {
        printf("Queue is full. Cannot accept more patients.\n");
        return;
    }

    if (q->front == -1) {
        q->front = 0;  // Queue is empty, so set front to 0
    }
    q->rear++;
    q->patients[q->rear] = p;
}

// Function to dequeue a patient (assign to doctor)
Patient dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. No patients to assign.\n");
        Patient emptyPatient = {0, "", 0};
        return emptyPatient;
    }

    Patient p = q->patients[q->front];
    q->front++;

    if (q->front > q->rear) {
        q->front = q->rear = -1;  // Reset queue if all patients are served
    }

    return p;
}

// Function to display the queue
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\nCurrent patients in the queue:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("Patient ID: %d, Name: %s, Arrival Time: %d\n", q->patients[i].patientID, q->patients[i].name, q->patients[i].arrivalTime);
    }
}

// Function to simulate the clinic and assign patients to doctors
void simulateClinic(Queue *q) {
    int doctorID = 1;

    while (!isEmpty(q)) {
        Patient p = dequeue(q);
        printf("\nAssigning Patient %d (%s) to Doctor %d\n", p.patientID, p.name, doctorID);
        doctorID = (doctorID == 3) ? 1 : doctorID + 1;  // Assume 3 doctors, rotate between them
    }
}

int main() {
    // Create a queue with a maximum capacity of 5 patients
    Queue *q = createQueue(5);

    // Simulate patients entering the clinic
    Patient p1 = {1, "John Doe", 10};
    Patient p2 = {2, "Jane Smith", 15};
    Patient p3 = {3, "Alice Brown", 20};
    Patient p4 = {4, "Bob White", 25};
    Patient p5 = {5, "Charlie Green", 30};

    enqueue(q, p1);
    enqueue(q, p2);
    enqueue(q, p3);
    enqueue(q, p4);
    enqueue(q, p5);

    // Display the current patients in the queue
    displayQueue(q);

    // Simulate the doctor assignments
    simulateClinic(q);

    // Free memory
    free(q->patients);
    free(q);

    return 0;
}
