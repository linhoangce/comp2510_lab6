//
// Created by linho on 2024-10-19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    if(argc < 4 || argc > 5) {
        printf("Error: ./<executable> <input_file> <output_file> <option> [--sort]\n");
        return 1;
    }

    FILE *readFile = fopen(argv[1], "r");
    FILE *writeFile = fopen(argv[2], "w");
    int option = atoi(argv[3]);
    int isSorted = (argc == 5 && strcmp(argv[4], "--sort") == 0);

    if(readFile == NULL || writeFile == NULL) {
        printf("Error: Could not open file!");
        return 1;
    }

    // Dynamic arrays to store students for sorting
    DomesticStudent *domesticStudents = NULL;
    InternationalStudent *internationalStudents = NULL;
    int domSCount = 0;
    int intSCount = 0;
    char line[MAX_LINE_LENGTH];

    while(fgets(line, sizeof(line), readFile)) {
        DomesticStudent      domStudent;
        InternationalStudent intStudent;
        // Parse line and handle error
        int result = parseLine(line, &domStudent, &intStudent);

        if(result == 0) {
            fprintf(writeFile, "Error: Invalid format!\n");
            fclose(readFile);
            fclose(writeFile);
            return 1;
        }

        switch(option) {
            case 1:
                if(domStudent.status == 'D' && domStudent.gpa > 3.9) {
                    domesticStudents = realloc(domesticStudents, (domSCount + 1) * sizeof(DomesticStudent));

                    if(domesticStudents == NULL) {
                        perror("Memory allocation for domesticStudents failed!\n");
                        free(domesticStudents);
                        return 1;
                    }

                    domesticStudents[domSCount++] = domStudent;

                    if(!isSorted) {
                        writeDomesticStudent(writeFile, &domStudent);
                        free(domesticStudents);
                    }
                }
                break;
            case 2:
                if(intStudent.student.status == 'I' && intStudent.student.gpa > 3.9 && intStudent.toefl > 70) {
                    internationalStudents = realloc(internationalStudents, (intSCount + 1) * sizeof(InternationalStudent));

                    if(internationalStudents == NULL) {
                        perror("Memory allocation for internationalStudents failed!");
                        free(internationalStudents);
                        return 1;
                    }

                    internationalStudents[intSCount++] = intStudent;

                    if(!isSorted) {
                        writeIntStudent(writeFile, &intStudent);
                        free(internationalStudents);
                    }
                }
                break;
            case 3:
                if(domStudent.status == 'D' && domStudent.gpa > 3.9) {
                    domesticStudents = realloc(domesticStudents, (domSCount + 1) * sizeof(DomesticStudent));

                    if(domesticStudents == NULL) {
                        perror("Memory allocation for domesticStudents failed!\n");
                        free(domesticStudents);
                        return 1;
                    }

                    domesticStudents[domSCount++] = domStudent;

                    if(!isSorted) {
                        writeDomesticStudent(writeFile, &domStudent);
                        free(domesticStudents);
                    }
                }

                if(intStudent.student.status == 'I' && intStudent.student.gpa > 3.9 && intStudent.toefl > 70) {
                    internationalStudents = realloc(internationalStudents, (intSCount + 1) * sizeof(InternationalStudent));

                    if(internationalStudents == NULL) {
                        perror("Memory allocation for internationalStudents failed!");
                        free(internationalStudents);
                        return 1;
                    }

                    internationalStudents[intSCount++] = intStudent;

                    if(!isSorted) {
                        writeIntStudent(writeFile, &intStudent);
                        free(internationalStudents);
                    }
                }
                break;
            default:
                fprintf(writeFile, "Error: Invalid format!\n");
                fclose(readFile);
                fclose(writeFile);
                return 1;
        }
    }

    if(isSorted) {
        qsort(domesticStudents, domSCount, sizeof(DomesticStudent), compareDomStudentGPA);
        qsort(internationalStudents, intSCount, sizeof(InternationalStudent), compareIntStudentGPA);

        for(int i = 0; i < domSCount; i++) {
            writeDomesticStudent(writeFile, &domesticStudents[i]);
        }

        for(int i = 0; i < intSCount; i++) {
            writeIntStudent(writeFile, &internationalStudents[i]);
        }
    }

    fclose(readFile);
    fclose(writeFile);

    return 0;
}

