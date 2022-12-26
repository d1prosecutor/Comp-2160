#include <stdio.h>

typedef struct STUDENT
{
    int studentId;
    int level;
    float CGPA;
} Student;

typedef struct TEACHER
{
    int numYears;
    int rating;
} Teacher;

typedef struct PERSON
{
    char *name;
    int age;
    union TYPE
    {
        Student newStudent;
        Teacher newTeacher;
    } type;
} Person;

Person newStudent(char *name, int age)
{
    Student tempStudent = {
        .studentId = 7928676,
        .level = 200,
        .CGPA = 4.41,
    };

    Person newPerson = {
        .name = name,
        .age = age,
        .type = {tempStudent},
    };

    return newPerson;
}

int main()
{
    Person Naza = newStudent("Chukwunaza", 19);
    printf("%s, %d, %.2f, %d, %d", Naza.name, Naza.age, Naza.type.newStudent.CGPA, Naza.type.newStudent.level, Naza.type.newStudent.studentId);
    return 0;
}