#ifndef student_h
#define student_h

#define MIN_GPA 0.0
#define MAX_GPA 5.0
#define MIN_TOEFL 0
#define MAX_TOEFL 120
#define TOEFL_FILTER 70

typedef struct {
  char firstName[50];
  char lastName[50];
  float gpa;
  char status;
} DomesticStudent;

typedef struct {
  DomesticStudent student;
  int toefl;
} InternationalStudent;


// Function prototypes
int parseLine(char *line, DomesticStudent *domStudent, InternationalStudent *intStudent);
void writeDomesticStudent(FILE *file, DomesticStudent *domStudent);
void writeIntStudent(FILE *file, InternationalStudent *intStudent);
int compareDomStudentGPA(const void *a, const void *b);
int compareIntStudentGPA(const void *a, const void *b);
#endif