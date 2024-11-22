#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for a student node
typedef struct Student {
    int id;                     // Student ID
    char name[50];              // Student Name
    float marks;                // Student Marks
    struct Student* next;       // Pointer to the next node
    struct Student* prev;       // Pointer to the previous node
} Student;

// Function to create a new student node
Student* createStudent(int id, char name[], float marks) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->marks = marks;
    newStudent->next = NULL;
    newStudent->prev = NULL;
    return newStudent;
}

// Function to display all students
void displayStudents(Student* head) {
    if (head == NULL) {
        printf("No students in the database.\n");
        return;
    }
    Student* temp = head;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Marks: %.2f\n", temp->id, temp->name, temp->marks);
        temp = temp->next;
    }
}

// Function to display students in reverse order
void displayReverse(Student* tail) {
    if (tail == NULL) {
        printf("No students in the database.\n");
        return;
    }
    Student* temp = tail;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Marks: %.2f\n", temp->id, temp->name, temp->marks);
        temp = temp->prev;
    }
}

// Function to insert a new student at the start
Student* insertAtStart(Student* head, int id, char name[], float marks) {
    Student* newStudent = createStudent(id, name, marks);
    if (head != NULL) {
        head->prev = newStudent;
        newStudent->next = head;
    }
    return newStudent;
}

// Function to insert a new student at the end
Student* insertAtEnd(Student* head, Student** tail, int id, char name[], float marks) {
    Student* newStudent = createStudent(id, name, marks);
    if (*tail == NULL) { // If the list is empty
        *tail = newStudent;
        return newStudent;
    }
    (*tail)->next = newStudent;
    newStudent->prev = *tail;
    *tail = newStudent;
    return head;
}

// Function to insert a new student after a specific student ID
Student* insertInBetween(Student* head, int afterId, int id, char name[], float marks) {
    Student* temp = head;
    while (temp != NULL && temp->id != afterId) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Student ID %d not found.\n", afterId);
        return head;
    }
    Student* newStudent = createStudent(id, name, marks);
    newStudent->next = temp->next;
    newStudent->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newStudent;
    }
    temp->next = newStudent;
    return head;
}

// Function to delete a student record by ID
Student* deleteStudent(Student* head, Student** tail, int id) {
    if (head == NULL) {
        printf("No students to delete.\n");
        return head;
    }
    Student* temp = head;

    // Find the student by ID
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Student ID %d not found.\n", id);
        return head;
    }

    // Update pointers to remove the node
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next; // Update head if the first node is deleted
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        *tail = temp->prev; // Update tail if the last node is deleted
    }

    free(temp);
    printf("Student with ID %d deleted.\n", id);
    return head;
}

// Main function
int main() {
    Student* head = NULL;
    Student* tail = NULL; // To keep track of the last node
    int choice, id, afterId;
    float marks;
    char name[50];

    do {
        printf("\n--- Student Database Menu ---\n");
        printf("1. Display all students\n");
        printf("2. Display students in reverse order\n");
        printf("3. Insert at start\n");
        printf("4. Insert at end\n");
        printf("5. Insert in between\n");
        printf("6. Delete student record\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayStudents(head);
                break;
            case 2:
                printf("Students in reverse order:\n");
                displayReverse(tail);
                break;
            case 3:
                printf("Enter ID, Name, Marks: ");
                scanf("%d %s %f", &id, name, &marks);
                head = insertAtStart(head, id, name, marks);
                if (tail == NULL) tail = head; // Update tail if the list was empty
                break;
            case 4:
                printf("Enter ID, Name, Marks: ");
                scanf("%d %s %f", &id, name, &marks);
                head = insertAtEnd(head, &tail, id, name, marks);
                break;
            case 5:
                printf("Enter ID to insert after, and new student's ID, Name, Marks: ");
                scanf("%d %d %s %f", &afterId, &id, name, &marks);
                head = insertInBetween(head, afterId, id, name, marks);
                break;
            case 6:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                head = deleteStudent(head, &tail, id);
                break;
            case 7:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
