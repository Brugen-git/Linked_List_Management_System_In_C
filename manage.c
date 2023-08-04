#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int student_id;
    char name[50];
    float grade;
    struct Student* next;
};

typedef struct Student Student;

Student* create_student(int student_id, char name[], float grade) {
    Student* new_student = (Student*)malloc(sizeof(Student));
    new_student->student_id = student_id;
    strcpy(new_student->name, name);
    new_student->grade = grade;
    new_student->next = NULL;
    return new_student;
}

void add_student(Student** head, int student_id, char name[], float grade) {
    Student* new_student = create_student(student_id, name, grade);
    if (*head == NULL) {
        *head = new_student;
    } else {
        Student* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_student;
    }
}

void display_students(Student* head) {
    Student* current = head;
    while (current != NULL) {
        printf("Student ID: %d, Name: %s, Grade: %.2f\n", current->student_id, current->name, current->grade);
        current = current->next;
    }
}

Student* search_student(Student* head, int student_id) {
    Student* current = head;
    while (current != NULL) {
        if (current->student_id == student_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void remove_student(Student** head, int student_id) {
    if (*head == NULL) {
        printf("No students to remove.\n");
        return;
    }

    if ((*head)->student_id == student_id) {
        Student* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("Student removed successfully!\n");
        return;
    }

    Student* prev = *head;
    Student* current = (*head)->next;

    while (current != NULL) {
        if (current->student_id == student_id) {
            prev->next = current->next;
            free(current);
            printf("Student removed successfully!\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Student not found.\n");
}

void update_student(Student* head, char name[]) {
    Student* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            float new_grade;
            printf("Enter new grade for %s: ", name);
            scanf(" %f", &new_grade);
            current->grade = new_grade;
            printf("Student details updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Student not found.\n");
}

int count_students(Student* head) {
    int count = 0;
    Student* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int main() {
    Student* head = NULL;
    int choice;
    
    while (1) {
        printf("\nLinked List Management System\n");
        printf("1. Add a student\n");
        printf("2. Display all students\n");
        printf("3. Search for a student\n");
        printf("4. Count the number of students\n");
        printf("5. Remove a student\n");
        printf("6. Update student details\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        Student* found_student; 
        int student_id;
        
        switch (choice) {
            case 1:
                int student_id;
                char name[50];
                float grade;
                printf("Enter student ID: ");
                scanf("%d", &student_id);
                printf("Enter student's name: ");
                scanf("%s", name);
                printf("Enter student's grade: ");
                scanf("%f", &grade);
                add_student(&head, student_id, name, grade);
                printf("Student added successfully!\n");
                break;
                
            case 2:
                printf("\nList of Students:\n");
                display_students(head);
                break;
                
            case 3:
                printf("Enter student ID to search: ");
                scanf("%d", &student_id);
                found_student = search_student(head, student_id);
                if (found_student != NULL) {
                    printf("Student found:\n");
                    printf("Student ID: %d, Name: %s, Grade: %.2f\n", found_student->student_id, found_student->name, found_student->grade);
                } else {
                    printf("Student not found.\n");
                }
                break;
                
             case 4:
                printf("Number of students: %d\n", count_students(head));
                break;
                
            case 5:
                printf("Enter student ID to remove: ");
                scanf("%d", &student_id);
                remove_student(&head, student_id);
                break;
            
            case 6:
                printf("Enter student's name to update: ");
                scanf("%s", name);
                update_student(head, name);
                break;
                
            case 7:
                printf("Exiting the program.\n");
                exit(0);
                
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }
    
    return 0;
}