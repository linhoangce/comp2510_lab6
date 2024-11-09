//
// Created by linho on 2024-10-19.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "student.h"
#define MAX_WORD_LENGTH 256
#define MAX_WORDS 100

int parseLine(char *line, DomesticStudent *domStudent, InternationalStudent *intStudent) {

    char **words;
    char word[MAX_WORD_LENGTH];
    int wordsIndex = 0;
    int wordIndex = 0;
    int lineLength = strlen(line);

    // Allocate memory for words
    words = malloc(MAX_WORDS * sizeof(char*));

    if(words == NULL) {
        printf("Memory allocation for words failed!\n");
        return 0;
    }

    for(int i = 0; i <= lineLength; i++) {
        if(line[i] != ' ' && line[i] != '\n' && line[i] != '\0') {
            word[wordIndex++] = line[i];
        }
        else if(wordIndex > 0) {
            word[wordIndex] = '\0';

            // Allocate memory for each word in words
            words[wordsIndex] = malloc((MAX_WORD_LENGTH + 1) * sizeof(char));

            if(words[wordsIndex] == NULL) {
                printf("Memory allocation for words[wordsIndex] failed!\n");
                free(words);
                return 0;
            }

            strcpy(words[wordsIndex], word);
            wordsIndex++;
            wordIndex = 0;
        }
    }

    // Check if there are at least 4 words (for status 'D') or 5 words (for status 'I')
    if (wordsIndex < 4 || (words[3][0] == 'I' && wordsIndex < 5)) {
        for (int i = 0; i < wordsIndex; i++) {
            free(words[i]);
        }

        free(words);
        return 0;
    }

    if(words[3][0] == 'D') {
        strcpy(domStudent->firstName, words[0]);
        strcpy(domStudent->lastName, words[1]);
        domStudent->gpa = atof(words[2]);
        domStudent->status = words[3][0];

        // clear status for international student
        intStudent->student.status = '\0';
    }
    else if(words[3][0] == 'I') {
        strcpy(intStudent->student.firstName, words[0]);
        strcpy(intStudent->student.lastName, words[1]);
        intStudent->student.gpa = atof(words[2]);
        intStudent->student.status = words[3][0];
        intStudent->toefl = atoi(words[4]);

        //populate only intStudent, clear status for domStudent
        domStudent->status = '\0';
    }
    else {
        free(words);
        return 0;
    }

    // Free memory allocation
    for(int i = 0; i < wordsIndex; i++) {
        free(words[i]);
    }

    free(words);

    return 1;
}

void writeDomesticStudent(FILE *file, DomesticStudent *domStudent) {
    fprintf(file, "%s %s %.3f %c\n", domStudent->firstName,
                                    domStudent->lastName,
                                    domStudent->gpa,
                                    domStudent->status);
}

void writeIntStudent(FILE *file, InternationalStudent *intStudent) {
    fprintf(file, "%s %s %.3f %c %d\n", intStudent->student.firstName,
                                            intStudent->student.lastName,
                                            intStudent->student.gpa,
                                            intStudent->student.status,
                                            intStudent->toefl);
}

int compareDomStudentGPA(const void *a, const void *b) {
    const DomesticStudent *studentA = (const DomesticStudent *) a;
    const DomesticStudent *studentB = (const DomesticStudent *) b;

    if(studentA->gpa > studentB->gpa) {
        return -1;
    }

    if(studentA->gpa < studentB->gpa) {
        return 1;
    }

    return 0;
}

int compareIntStudentGPA(const void *a, const void *b) {
    const InternationalStudent *studentA = (InternationalStudent *) a;
    const InternationalStudent *studentB = (InternationalStudent *) b;

    if(studentA->student.gpa > studentB->student.gpa) {
        return -1;
    }

    if(studentA->student.gpa < studentB->student.gpa) {
        return 1;
    }

    return 0;
}
