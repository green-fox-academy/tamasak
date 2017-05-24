#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {MATH, HISTORY, ENGLISH, SCIENCE} subject_t;

typedef struct {
    subject_t subject;
    int value;
} grade_t;

typedef struct {
    char name[128];
    int age;
    grade_t* grades;
    int grade_count;
} student_t;

// TODO:
// Create a function the constructs a Student (returns a pointer to a new student)
// It should take it's name and it's age as parameter
// It should allocate 5 grades
// It should set the grade_count to 0
student_t *create_student(char *name, int age)
{
    grade_t *grades = (grade_t*) calloc(5, sizeof(grade_t));
    student_t *student = (student_t*) malloc(sizeof(student_t));
    strcpy(student->name, name);
    student->age = age;
    student->grades = grades;
    student->grade_count = 0;

    return student;
}

// TODO:
// Create a function that takes 3 parameters:
// A pointer to a Student
// A Subject
// An int (1-5)
// It should set the last grade's values with the given arguments
void set_grade(student_t *student, subject_t subject, int a)
{
    student->grades[student->grade_count].subject = subject;
    student->grades[student->grade_count].value = a;
    student->grade_count++;
}

// TODO:
// Create a function that takes a Student as a pointer and returns the subject
// that the student has worst grade in
subject_t worst_grade(student_t *student)
{
    int tmp = 100;
    int tmp2 = 50;
    //for (int j = 0; j <)
    for (int i = 0; i < student->grade_count; i++) {
        if (student->grades[i].value < tmp) {
            tmp = student->grades[i].value;
            tmp2 = student->grades[i].subject;
        }
    }
    return tmp2;
}

// TODO:
// Create a function that deconstructs a Student
// It should take a pointer that points to the student
// It should free each Grade and the Student itself
void deconstruct_student(student_t *student)
{
    free(student->grades);
    free(student);
}

int main()
{
    student_t *pisti = create_student("Pisti", 8);
    set_grade(pisti, HISTORY, 3);
    set_grade(pisti, ENGLISH, 1);
    set_grade(pisti, SCIENCE, 3);

printf("%s's worst grade subject is: %d\n", pisti->name, worst_grade(pisti));

    return 0;
}
