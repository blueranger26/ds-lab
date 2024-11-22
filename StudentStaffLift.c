#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 10  // Maximum capacity of the lift

// Define the priority levels
#define HIGH_PRIORITY 3  // HODs, Deans, Directors
#define STAFF_PRIORITY 2  // Staff members
#define STUDENT_PRIORITY 1  // Students
#define GUEST_PRIORITY 0  // Guests (lowest priority)

// Structure to represent a user in the lift
typedef struct User {
    char type;  // 'S' for Student, 'F' for Staff, 'H' for High-priority (HOD/Dean/Director), 'G' for Guest
    int id;     // User ID
    int priority;  // Priority of the user
} User;

// Lift structure
typedef struct Lift {
    User *users[MAX_CAPACITY];
    int currentUsers;
} Lift;

// Function to create a new lift
Lift* createLift() {
    Lift *lift = (Lift*)malloc(sizeof(Lift));
    lift->currentUsers = 0;
    return lift;
}

// Function to add a user to the lift
int addUserToLift(Lift *lift, User user) {
    // Check if the lift is full
    if (lift->currentUsers >= MAX_CAPACITY) {
        printf("Lift is full. Cannot add user %d.\n", user.id);
        return 0;
    }

    // Check priority and remove users accordingly
    if (user.priority == HIGH_PRIORITY) {
        // High priority users (HOD, Dean, Director) push out staff and students
        for (int i = 0; i < lift->currentUsers; i++) {
            if (lift->users[i]->priority < HIGH_PRIORITY) {
                printf("High-priority user %d (HOD/Dean/Director) removing user %d (Type: %c)\n",
                       user.id, lift->users[i]->id, lift->users[i]->type);
                removeUserFromLift(lift, lift->users[i]->id);  // Remove lower priority users
                i--;  // Adjust index after removal
            }
        }
    } else if (user.priority == STAFF_PRIORITY) {
        // Staff push out students, but not high-priority users
        for (int i = 0; i < lift->currentUsers; i++) {
            if (lift->users[i]->priority == STUDENT_PRIORITY) {
                printf("Staff user %d removing student %d\n", user.id, lift->users[i]->id);
                removeUserFromLift(lift, lift->users[i]->id);
                i--;  // Adjust index after removal
            }
        }
    } else if (user.priority == STUDENT_PRIORITY) {
        // Students can only enter if no staff are in the lift
        for (int i = 0; i < lift->currentUsers; i++) {
            if (lift->users[i]->priority == STAFF_PRIORITY) {
                printf("Student %d cannot enter the lift, staff is already inside.\n", user.id);
                return 0;
            }
        }
    }

    // Add the user to the lift if space is available
    lift->users[lift->currentUsers] = (User*)malloc(sizeof(User));
    *lift->users[lift->currentUsers] = user;
    lift->currentUsers++;
    printf("User %d added to the lift (Type: %c, Priority: %d)\n", user.id, user.type, user.priority);
    return 1;
}

// Function to remove a user from the lift
void removeUserFromLift(Lift *lift, int userID) {
    for (int i = 0; i < lift->currentUsers; i++) {
        if (lift->users[i]->id == userID) {
            printf("User %d (Type: %c) removed from the lift.\n", userID, lift->users[i]->type);
            free(lift->users[i]);
            for (int j = i; j < lift->currentUsers - 1; j++) {
                lift->users[j] = lift->users[j + 1];
            }
            lift->currentUsers--;
            return;
        }
    }
    printf("User %d not found in the lift.\n", userID);
}

// Function to display the current lift status
void displayLift(Lift *lift) {
    printf("Current users in the lift: \n");
    for (int i = 0; i < lift->currentUsers; i++) {
        printf("User %d (Type: %c, Priority: %d)\n", lift->users[i]->id, lift->users[i]->type, lift->users[i]->priority);
    }
}

// Main simulation function
int main() {
    Lift *lift = createLift();
    
    // Sample actions for adding users to the lift
    User student1 = {'S', 1, STUDENT_PRIORITY};
    User staff1 = {'F', 2, STAFF_PRIORITY};
    User hod = {'H', 3, HIGH_PRIORITY};  // HOD/Dean/Director (high-priority)
    User student2 = {'S', 4, STUDENT_PRIORITY};
    User guest1 = {'G', 5, GUEST_PRIORITY};
    
    addUserToLift(lift, student1);  // Student 1 enters the lift
    addUserToLift(lift, staff1);    // Staff 1 enters the lift
    addUserToLift(lift, hod);       // HOD/Dean/Director enters, staff is removed
    addUserToLift(lift, student2);  // Student 2 enters (after HOD, displaces staff)
    addUserToLift(lift, guest1);    // Guest enters the lift
    displayLift(lift);
    
    // Attempting to add another student when staff are already in the lift
    User student3 = {'S', 6, STUDENT_PRIORITY};
    addUserToLift(lift, student3);  // This should be rejected
    
    // Remove a user from the lift
    removeUserFromLift(lift, 1);  // Remove Student 1
    displayLift(lift);

    return 0;
}
