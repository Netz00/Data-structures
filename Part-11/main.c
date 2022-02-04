#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define wordLen (64)
#define hashTableLen (11)
#define charsToHash (5)

#define foreach(p, head) \
    for (Position p = head; p != NULL; p = p->next)

struct _student;
typedef struct _student
{
    char ime[wordLen];
    char prez[wordLen];
    size_t matBroj;
} Student;

struct _node;
typedef struct _node *Position;
typedef struct _node
{
    Student student;
    Position next;
} Node;

Student insertStudent();
int addToHashTable(Position, int, Student);
int getHashValue(int, char *, int);
Position newNode(Student);
int PrintHashTable(Position, int);
Position sortedInsertion(Position, Position);

int main(void)
{
    Node hashList[hashTableLen];

    for (size_t i = 0; i < hashTableLen; i++)
    {
        hashList[i].next = NULL;
    }

    // addToHashTable(&hashList, hashTableLen, insertStudent());

    Student stud;
    strcpy(stud.ime, "Marko");
    strcpy(stud.prez, "Matic");
    stud.matBroj = 2324;

    addToHashTable(&hashList, hashTableLen, stud);

    strcpy(stud.ime, "Jerko");
    strcpy(stud.prez, "Matid");
    stud.matBroj = 23342;

    addToHashTable(&hashList, hashTableLen, stud);

    strcpy(stud.ime, "Ivo");
    strcpy(stud.prez, "Matie");
    stud.matBroj = 234342;

    addToHashTable(&hashList, hashTableLen, stud);

    strcpy(stud.ime, "Drugi");
    strcpy(stud.prez, "Matic");
    stud.matBroj = 234342;

    addToHashTable(&hashList, hashTableLen, stud);

    strcpy(stud.ime, "AaPrvi");
    strcpy(stud.prez, "Matic");
    stud.matBroj = 234342;

    addToHashTable(&hashList, hashTableLen, stud);

    strcpy(stud.ime, "zzZadnji");
    strcpy(stud.prez, "Matic");
    stud.matBroj = 234342;

    addToHashTable(&hashList, hashTableLen, stud);

    strcpy(stud.ime, "Ivica");
    strcpy(stud.prez, "citaM");
    stud.matBroj = 234342;

    addToHashTable(&hashList, hashTableLen, stud);

    strcpy(stud.ime, "prikoVezePrvi");
    strcpy(stud.prez, "aMtic");
    stud.matBroj = 234342;

    addToHashTable(&hashList, hashTableLen, stud);

    PrintHashTable(&hashList, hashTableLen);

    return EXIT_SUCCESS;
}

int PrintHashTable(Position hashTable, int tableSize)
{

    for (size_t i = 0; i < tableSize; i++)
    {
        printf("KEY: %d\t", i);
        foreach (p, (hashTable + i)->next)
            printf("%s %s %u\t", p->student.ime, p->student.prez, p->student.matBroj);
        printf("\n");
    }
}

int addToHashTable(Position hashTable, int hashTableSize, Student el)
{

    int i;
    i = getHashValue(charsToHash, el.prez, hashTableSize);

    (hashTable + i)->next = sortedInsertion((hashTable + i)->next, newNode(el));

    return i;
}

Position newNode(Student el)
{
    Position temp = (Position)malloc(sizeof(Node));
    if (NULL == temp)
    {
        puts("Memory allocation failed!\n");
        return NULL;
    }

    temp->student = el;
    temp->next = NULL;

    return temp;
}

int getHashValue(int len, char *lastName, int hashTableSize)
{
    int sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (*(lastName + i) == '\0')
            break;

        sum += *(lastName + i);
    }

    return sum % (hashTableSize + 1);
}

Student insertStudent()
{
    Student temp;
    printf("Insert student first name:\n");
    scanf(" %s", temp.ime);
    printf("Insert student last name:\n");
    scanf(" %s", temp.prez);
    printf("Insert student personal number:\n");
    scanf(" %u", &temp.matBroj);
    return temp;
}

Position sortedInsertion(Position head, Position el)
{

    if (NULL == head)
        return el;

    if (_strcmpi(head->student.prez, el->student.prez) > 0)
    {

        el->next = head;
        return el;
    }

    if (_strcmpi(head->student.prez, el->student.prez) == 0)
        if (_strcmpi(head->student.ime, el->student.ime) >= 0)
        {

            el->next = head;
            return el;
        }

    head->next = sortedInsertion(head->next, el);

    return head;
}
