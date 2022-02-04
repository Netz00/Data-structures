#include <stdio.h>

#define FileName "students.txt"
#define WordLength 30
#define max_br_bodova 50

typedef struct
{
    char ime[WordLength];
    char prez[WordLength];
    size_t bodovi;
} Student;

int getNumOfStud(char *file)
{
    FILE *fp = NULL;
    int numOfStud = 0;

    fopen_s(&fp, file, "r");

    if (fp == NULL)
    {
        puts("Loading file failed.");
        return -1;
    }

    while (!feof(fp))
    {

        if (fgetc(fp) == '\n')
            numOfStud++;
    }
    fclose(fp);

    return numOfStud;
}

int readStudents(char *file, Student *stud)
{
    FILE *fp = NULL;
    size_t i = 0;

    fopen_s(&fp, file, "r");

    if (fp == NULL)
    {
        puts("Loading file failed.");
        return -1;
    }

    while (!feof(fp))
    {

        fscanf_s(fp, "%s %s %u", (stud + i)->ime, WordLength, (stud + i)->prez, WordLength, &(stud + i)->bodovi);

        i++;
    }

    fclose(fp);

    return 1;
}

float RelBrBodova(size_t brBod)
{
    return brBod / (float)max_br_bodova * 100;
}

int WriteOut(Student *stud, int numOfStud)
{
    size_t i;
    printf("%25s%25s%25s%25s\n", "Ime", "Prezime", "Broj bodova", "Relativan broj bodova");
    puts("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    for (i = 0; i < numOfStud; i++)
    {
        printf("%25s%25s%25d%25.2f\n", (stud + i)->ime, (stud + i)->prez, (stud + i)->bodovi, RelBrBodova((stud + i)->bodovi));
        puts("_____________________________________________________________________________________________________");
    }
    return 1;
}

int main(void)
{

    Student *stud = NULL;
    int numOfStud;

    // read number of students from file
    numOfStud = getNumOfStud(FileName);
    if (numOfStud == -1)
        return -1;

    // allocate memory for students
    stud = (Student *)malloc(numOfStud * sizeof(Student));

    if (stud == NULL)
    {
        puts("Allocation of memory failed.");
        return -1;
    }

    // read studetns from file
    if (readStudents(FileName, stud) == -1)
        return -1;

    // write out students
    if (WriteOut(stud, numOfStud) != 1)
        return -1;

    free(stud);

    return 0;
}