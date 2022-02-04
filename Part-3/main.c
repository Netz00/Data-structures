#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define wordLen (256)

#define foreach(p, first) \
    for (Position p = first; p != NULL; p = p->next)

#define flushStdin                                  \
    {                                               \
        char c;                                     \
        while ((c = getchar()) != '\n' && c != EOF) \
            ;                                       \
    }

typedef struct _osoba
{
    char ime[wordLen];
    char prez[wordLen];
    size_t godRod;
} Osoba;

struct _node;

typedef struct _node *Position;

typedef struct _node
{
    Osoba osoba;
    Position next;
} Node;

/*ZADATAK 2*/
Position create(Osoba);
Position getLast(Position);
Position findElement(Position, char *);

int insertAfter(Position, Position);
int deleteElement(Position, char *);

int printList(Position);
int printListElement(Position);

Osoba createOsoba();
int printOsoba(Osoba);

/*ZADATAK 3*/
int addAfter(Position, char *);
Position findElementBefore(Position, char *);
int addBefore(Position, char *);
int sortByLastName(Position); // bubblesort
int makeFile(Position, char *);
int readFile(Position, char *);

int deleteList(Position *);

int main(void)
{

    Node head;
    head.next = NULL;
    Position el = NULL;
    Osoba osoba;

    puts("\nUcitajmo vezanu listu iz datoteke...\n");
    readFile(&head, "list.txt");
    printList(&head);

    while (1)
    {

        puts("Write y to add element...");

        if (getchar() != 'y')
            break;
        flushStdin;

        osoba = createOsoba();
        el = create(osoba);
        insertAfter(&head, el);
        printList(&head);

        flushStdin;
    }

    puts("\nPoslejdnji element liste je...\n");
    printListElement(getLast(&head));

    puts("\nDodajmo na kraj liste element...\n");
    osoba = createOsoba();
    el = create(osoba);
    insertAfter(getLast(&head), el);
    printList(&head);

    puts("\nPoslejdnji element liste je...\n");
    printListElement(getLast(&head));

    puts("\nPotrazimo element u listi...\n");
    printListElement(findElement(&head, "Senta"));

    puts("\nIzbrisimo element u listi...\n");
    deleteElement(&head, "Senta");
    printList(&head);

    puts("\nPotrazimo IZBRISANI element u listi...\n");
    printListElement(findElement(&head, "Senta"));

    printList(&head);

    puts("\nDodajmo element prije prezimena Olic...\n");
    addBefore(&head, "Olic");
    printList(&head);

    puts("\nDodajmo element nakon prezimena Olic...\n");
    addAfter(&head, "Olic");
    printList(&head);

    puts("\nSortirajmo listu po prezimenima...\n");
    sortByLastName(&head);
    printList(&head);

    puts("\nIspisimo vezanu listu u datoteku...\n");
    makeFile(&head, "list.txt");
    printList(&head);

    puts("\nIzbrisimo vezanu listu...\n");
    deleteList(&head.next);
    printList(&head);

    system("pause");

    return EXIT_SUCCESS;
}

int makeFile(Position head, char *fileName)
{
    FILE *fp = NULL;
    fp = fopen(fileName, "w");

    if (fp == NULL)
    {
        puts("Error opening file!");
        return -1;
    }

    foreach (p, head->next)
        fprintf(fp, "%s %s %u\r\n", p->osoba.ime, p->osoba.prez, p->osoba.godRod);

    fclose(fp);
    puts("\n");

    return 0;
}

int readFile(Position head, char *fileName)
{
    FILE *fp = NULL;
    Osoba osoba;
    Position el = NULL;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        puts("Error opening file!");
        return -1;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%s %s %u\r\n", osoba.ime, osoba.prez, &osoba.godRod);

        el = create(osoba);
        insertAfter(getLast(head), el);
    }
    fclose(fp);
    puts("\n");

    return 0;
}

int sortByLastName(Position p)
{

    Position j = NULL, prev_j = NULL, temp = NULL, end = NULL;
    end = NULL;
    while (p->next != end)
    {
        prev_j = p;
        j = p->next;
        while (j->next != end)
        {
            if (_strcmpi(j->osoba.prez, j->next->osoba.prez) > 0)
            {
                temp = j->next;
                prev_j->next = temp;
                j->next = temp->next;
                temp->next = j;
                j = temp;
            }
            prev_j = j;
            j = j->next;
        }

        end = j;
    }
    return 0;
}

int addAfter(Position head, char *lastName)
{
    Position el = NULL, tmp = NULL;
    Osoba osoba;

    tmp = findElement(head, lastName);

    if (tmp == NULL)
        puts("Element ne postoji!");
    else
    {
        osoba = createOsoba();
        el = create(osoba);
        insertAfter(tmp, el);
    }
    return 0;
}

int addBefore(Position head, char *lastName)
{
    Position el = NULL, tmp = NULL;
    Osoba osoba;

    tmp = findElementBefore(head, lastName);

    if (tmp == NULL)
        puts("Element ne postoji!");
    else
    {
        osoba = createOsoba();
        el = create(osoba);
        insertAfter(tmp, el);
    }
    return 0;
}

int printListElement(Position el)
{
    if (el == NULL)
    {
        puts("Trazeni element ne postoji!");
        return -1;
    }
    else
        printOsoba(el->osoba);

    return 0;
}

int deleteElement(Position head, char *lastName)
{

    Position tmp = NULL;

    foreach (p, head)
        if (p->next != NULL && strcmp(p->next->osoba.prez, lastName) == 0)
        {
            tmp = p->next->next;
            free(p->next);
            p->next = tmp;
            return 0;
        }

    return 1;
}

Position findElement(Position head, char *lastName)
{

    foreach (p, head->next)
        if (strcmp(p->osoba.prez, lastName) == 0)
            return p;

    return NULL;
}

Position findElementBefore(Position head, char *lastName)
{

    foreach (p, head)
        if (p->next != NULL && strcmp(p->next->osoba.prez, lastName) == 0)
            return p;

    return NULL;
}

Position getLast(Position head)
{

    Position temp = NULL;

    foreach (p, head)
        temp = p;

    return temp;
}

int printOsoba(Osoba osoba)
{
    printf("%s %s %u\r\n", osoba.ime, osoba.prez, osoba.godRod);
    return 0;
}

Osoba createOsoba()
{

    Osoba osoba;

    printf("Please insert person:\r\n");
    printf("First name:\r\n");
    scanf(" %s", osoba.ime);
    printf("Last name:\r\n");
    scanf(" %s", osoba.prez);
    printf("Birthyear:\r\n");
    scanf(" %u", &osoba.godRod);

    return osoba;
}

int insertAfter(Position where, Position what)
{
    what->next = where->next;
    where->next = what;
    return 0;
}

Position create(Osoba osoba)
{

    Position el = NULL;
    el = (Position)malloc(sizeof(Node));
    if (NULL == el)
    {
        printf("Memory allocation failed!\r\n");
        return NULL;
    }
    el->osoba = osoba;
    el->next = NULL;
    return el;
}

int printList(Position head)
{

    printf("\r\n\rLIST CONTENT:\r\n");

    foreach (p, head->next)
        printListElement(p);

    puts("\n");

    return 0;
}

int deleteList(Position *head)
{
    if ((*head)->next != NULL)
        deleteList(&((*head)->next));

    free((*head));
    (*head) = NULL;
}