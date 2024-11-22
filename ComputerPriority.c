#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining the task priorities
#define DOWNLOAD_PRIORITY 3
#define MUSIC_PRIORITY 2
#define GAME_PRIORITY 1

// Structure to represent a task
typedef struct Task {
    char name[50];
    int priority;
} Task;

// Structure to represent a queue
typedef struct Queue {
    Task *tasks[100];
    int front;
    int rear;
} Queue;

// Function to create a queue
Queue* createQueue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue *queue) {
    return queue->front == queue->rear;
}

// Function to add a task to the queue
void enqueue(Queue *queue, Task task) {
    if (queue->rear == 100) {
        printf("Queue is full. Cannot add task.\n");
        return;
    }
    queue->tasks[queue->rear] = (Task*)malloc(sizeof(Task));
    *queue->tasks[queue->rear] = task;
    queue->rear++;
}

// Function to remove a task from the queue
Task dequeue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. No tasks to process.\n");
        Task emptyTask = {"", 0}; // Return an empty task
        return emptyTask;
    }
    Task task = *queue->tasks[queue->front];
    free(queue->tasks[queue->front]);
    queue->front++;
    return task;
}

// Function to simulate task processing based on priority
void processTasks(Queue *downloadQueue, Queue *musicQueue, Queue *gameQueue) {
    // Process download tasks first (highest priority)
    printf("Processing Download Tasks (Priority 3):\n");
    while (!isQueueEmpty(downloadQueue)) {
        Task task = dequeue(downloadQueue);
        printf("Task: %s (Download)\n", task.name);
    }

    // Then process music tasks (priority 2)
    printf("\nProcessing Music Tasks (Priority 2):\n");
    while (!isQueueEmpty(musicQueue)) {
        Task task = dequeue(musicQueue);
        printf("Task: %s (Music)\n", task.name);
    }

    // Finally, process game tasks (lowest priority)
    printf("\nProcessing Game Tasks (Priority 1):\n");
    while (!isQueueEmpty(gameQueue)) {
        Task task = dequeue(gameQueue);
        printf("Task: %s (Game)\n", task.name);
    }
}

int main() {
    Queue *downloadQueue = createQueue();
    Queue *musicQueue = createQueue();
    Queue *gameQueue = createQueue();

    int numTasks;
    printf("Enter the number of tasks to simulate: ");
    scanf("%d", &numTasks);

    for (int i = 0; i < numTasks; i++) {
        Task task;
        printf("\nEnter task name: ");
        scanf("%s", task.name);

        int priority;
        printf("Enter task priority (1 for Game, 2 for Music, 3 for Download): ");
        scanf("%d", &priority);

        task.priority = priority;

        // Enqueue the task based on its priority
        if (priority == DOWNLOAD_PRIORITY) {
            enqueue(downloadQueue, task);
        } else if (priority == MUSIC_PRIORITY) {
            enqueue(musicQueue, task);
        } else if (priority == GAME_PRIORITY) {
            enqueue(gameQueue, task);
        } else {
            printf("Invalid priority. Please enter a valid priority (1-3).\n");
        }
    }

    // Process the tasks based on their priority
    processTasks(downloadQueue, musicQueue, gameQueue);

    // Free memory
    free(downloadQueue);
    free(musicQueue);
    free(gameQueue);

    return 0;
}
