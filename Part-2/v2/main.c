#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define wordLen (256)

#define foreach(p, head) \
    for (Position p = head->next; p != NULL; p = p->next)

#define flushStdin                              \
    char c;                                     \
    while ((c = getchar()) != '\n' && c != EOF) \
        ;

struct _osoba;
struct _node;

typedef struct _node *Position;

typedef struct _osoba
{
    char ime[wordLen];
    char prez[wordLen];
    size_t godRod;
} Osoba;

typedef struct _node
{
    Osoba osoba;
    Position next;
} Node;

Position create(Osoba);
Position getLast(Position);
Position findElement(Position);
void insertAfter(Position, Position);
int deleteElement(Position, Position);
void printList(Position);
void printObjConnector(Position);

Osoba createOsoba();
void printOsoba(Osoba);

int main(void)
{

    Node head;
    head.next = NULL;
    Position el = NULL;
    Osoba osoba;

    while (1)
    {

        osoba = createOsoba();

        el = create(osoba);

        insertAfter(&head, el);

        printList(&head);

        puts("Write y to continue...");

        flushStdin;

        if (getchar() != 'y')
            break;
    }

    puts("\nPoslejdnji element liste je...\n");
    printObjConnector(getLast(&head));

    puts("\nDodajmo na kraj liste element...\n");
    osoba = createOsoba();
    el = create(osoba);
    insertAfter(getLast(&head), el);
    printList(&head);

    puts("\nPoslejdnji element liste je...\n");
    printObjConnector(getLast(&head));

    puts("\nPotrazimo element u listi...\n");
    printObjConnector(findElement(&head, "Senta"));

    puts("\nIzbrisimo element u listi...\n");

    if (deleteElement(&head, findElement(&head, "Senta")))
        puts("Element NIJE PRONADJEN!");
    else
        puts("Element JE IZBRISAN!");

    puts("\nPotrazimo IZBRISANI element u listi...\n");
    printObjConnector(findElement(&head, "Senta"));

    printList(&head);

    return EXIT_SUCCESS;
}

void printObjConnector(Position el)
{
    if (el == NULL)
        puts("Trazeni element ne postoji!");
    else
        printOsoba(el->osoba);
}

int deleteElement(Position head, Position el)
{
    if (el == NULL)
        return 1;

    Position tmp = NULL;
    foreach (p, head)
        if (p->next == el)
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

    foreach (p, head)
        if (strcmp(p->osoba.prez, lastName) == 0)
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

void printOsoba(Osoba osoba)
{
    printf("%s %s %u\r\n", osoba.ime, osoba.prez, osoba.godRod);
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

void insertAfter(Position where, Position what)
{
    what->next = where->next;
    where->next = what;
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

void printList(Position head)
{

    printf("\r\n\rLIST CONTENT:\r\n");

    foreach (p, head)
        printObjConnector(p);

    puts("\n");
}
