//
// Created by linho on 2024-10-18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define the Student structure
typedef struct {
    char name[50]; // Ensure name is an array of characters to store strings
    int age;
    float grade;
} Student;


// Function to add a new student
Student* addStudent(Student *students, int *count) {
    students = realloc(students, (*count + 1) * sizeof(Student));

    if (students == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    printf("Enter name: ");
    scanf("%s", students[*count].name); // use the name array to store strings
    printf("Enter age: ");
    scanf("%d", &students[*count].age);
    printf("Enter grade: ");
    scanf("%f", &students[*count].grade);
    (*count)++;

    return students;
}


// Function to display all students
void displayStudents(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Age: %d, Grade: %.2f\n", students[i].name, students[i].age, students[i].grade);
    }
}

// Function to search for a student by name
void searchStudent(Student *students, int count) {
    char name[50]; // name must be an array to store the search string
    printf("Enter name to search: ");
    scanf("%s", name); // scan into the name array

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) { // use strcmp to compare strings
            printf("Found student: Name: %s, Age: %d, Grade: %.2f\n",
                students[i].name, students[i].age, students[i].grade);

            return;
        }
    }
    printf("Student not found\n");
}


int main() {
    Student *students = NULL;
    int count = 0;
    int choice;
    while (1) {
    printf("\n1. Add Student\n2. Display Students\n3. Search Student\n4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

        switch (choice) {
            case 1:
                students = addStudent(students, &count);
                    if (students == NULL) {
                        printf("Error adding student. Exiting...\n");
                        return 1;
                    }
                    break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                free(students); // Freeing allocated memory
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

}