#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define wordLen 20

typedef struct
{
    char ime[wordLen];
    char prez[wordLen];
    size_t godRod;
} Osoba;

Osoba newPerson()
{
    Osoba temp;
    puts("Unesite ime...");
    scanf_s("%s", temp.ime, wordLen);
    puts("Unesite prezime...");
    scanf_s("%s", temp.prez, wordLen);
    puts("Unesite datum rodenja...");
    scanf_s("%u", &temp.godRod);
    return temp;
}

struct List
{
    Osoba osoba;
    struct List *next;
};

struct List *newNode()
{
    struct List *temp = NULL;
    temp = (struct List *)malloc(sizeof(struct List));
    temp->osoba = newPerson();
    temp->next = NULL;
}

struct List *addStart(struct List *list)
{
    struct List *head = newNode();
    head->next = list;
    return head;
}

struct List *addEnd(struct List *list)
{
    if (list == NULL)
        return newNode();

    list->next = addEnd(list->next);

    return list;
}

int search(struct List *list, char *prez)
{
    while (list != NULL)
    {
        if (strcmp(list->osoba.prez, prez) == 0)
        {
            printObject(&(list->osoba));
            break;
        }
        list = list->next;
    }
}

struct List *deleteElement(struct List *list, char *prez)
{

    if (list == NULL)
        return NULL;

    if (strcmp(list->osoba.prez, prez) == 0)
    {
        struct List *tmp = NULL;
        tmp = list->next;
        free(list);
        return tmp;
    }

    list->next = deleteElement(list->next, prez);

    return list;
}

int printList(struct List *list)
{
    puts("");
    while (list != NULL)
    {
        printObject(&(list->osoba));
        list = list->next;
    }
    puts("");
    return 1;
}

int printObject(Osoba *osoba)
{
    printf("Ime:\t%-20sPrezime:\t%-20sGodina rodenja:\t%-10u\n", osoba->ime, osoba->prez, osoba->godRod);
}

struct List *deleteList(struct List *list)
{

    if (list != NULL)
        list->next = deleteList(list->next);

    free(list);

    return NULL;
}

int main(void)
{

    struct List *list = NULL;

    list = addStart(list);
    list = addStart(list);

    list = addEnd(list);

    puts("Ispis svih clanova liste...\n");
    printList(list);

    puts("Ispis trazenog clana...\n");
    search(list, "Matic");

    puts("Brisanje trazenog clana...\n");
    list = deleteElement(list, "Matic");

    puts("Ispis svih clanova liste...\n");
    printList(list);

    puts("Brisanje liste iz memorije...\n");
    list = deleteList(list);

    return 0;
}
