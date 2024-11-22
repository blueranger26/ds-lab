#include <stdio.h>
#include <stdlib.h>
// Define a structure for the Job
typedef struct Job {
int id;
int timeRemaining;
} Job;
// Node structure for queue
typedef struct Node {
Job job;
struct Node* next;
} Node;
// Queue structure
typedef struct Queue {
Node* front;
Node* rear;
} Queue;
// Function to initialize the queue
void initQueue(Queue* q) {
q->front = q->rear = NULL;
}
// Function to check if the queue is empty
int isEmpty(Queue* q) {
return (q->front == NULL);
}
// Function to add a job to the queue
void enqueue(Queue* q, Job job) {
Node* temp = (Node*)malloc(sizeof(Node));
temp->job = job;
temp->next = NULL;
if (q->rear == NULL) {
    q->front = q->rear = temp;
return;
}
q->rear->next = temp;
q->rear = temp;
}
// Function to remove a job from the queue
Job dequeue(Queue* q) {
if (isEmpty(q)) {
printf("Queue is empty!\n");
exit(1);
}
Node* temp = q->front;
Job job = temp->job;
q->front = q->front->next;
if (q->front == NULL) {
q->rear = NULL;
}
free(temp);
return job;
}
int main() {
int n; // Time quantum
int t1, t2, t3; // Job processing times
printf("Enter time quantum: ");
scanf("%d", &n);
printf("Enter time for Job 1: ");
scanf("%d", &t1);
printf("Enter time for Job 2: ");
scanf("%d", &t2);
printf("Enter time for Job 3: ");
scanf("%d", &t3);
// Create jobs
Job j1 = {1, t1};
Job j2 = {2, t2};
Job j3 = {3, t3};
// Initialize the queue and add jobs to it
Queue q;
initQueue(&q);
enqueue(&q, j1);
enqueue(&q, j2);
enqueue(&q, j3);
// Process jobs in round-robin manner
while (!isEmpty(&q)) {
Job currentJob = dequeue(&q);
printf("Processing Job %d for %d units of time.\n", currentJob.id,
(currentJob.timeRemaining > n) ? n : currentJob.timeRemaining);
if (currentJob.timeRemaining > n) {
currentJob.timeRemaining -= n;
enqueue(&q, currentJob); // Add remaining job back to the queue
} else {
printf("Job %d is completed.\n", currentJob.id);
}
}
return 0;
}
