#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define lineLength 128
#define foreach(p, head) \
    for (Position p = head; p != NULL; p = p->next)

struct _node;

typedef struct _node *Position;

typedef struct _node
{
    int coef;
    Position next;
} Node;

Position create(int);
Position getLast(Position);

int insertAfter(Position, Position);
int printList(Position);
int sortedInsertion(Position, Position);

int list_union(Position, Position, Position);
int list_intersection(Position, Position, Position);

int unosIzDatoteke(Position, Position, char *);

int main(void)
{

    Node pHead;
    pHead.next = NULL;

    Node qHead;
    qHead.next = NULL;

    Node rHead;
    rHead.next = NULL;

    Node nHead;
    nHead.next = NULL;

    // sortirani unos iz datoteke
    unosIzDatoteke(&pHead, &qHead, "polinom.txt");

    /*
    insertAfter(getLast(&pHead), create(3));
    insertAfter(getLast(&pHead), create(7));
    */

    printf("\np lista...");
    printList(&pHead);
    printf("\nq lista...");
    printList(&qHead);

    printf("\nunija p i r liste...");
    list_union(&pHead, &qHead, &rHead);
    printList(&rHead);

    printf("\npresjek p i r liste...");
    list_intersection(&pHead, &qHead, &nHead);
    printList(&nHead);

    system("pause");

    return EXIT_SUCCESS;
}

int list_union(Position p, Position q, Position r)
{

    if (p != NULL)
        p = p->next;
    if (q != NULL)
        q = q->next;

    while (p != NULL && q != NULL)
    {

        if (p->coef == q->coef)
        {
            insertAfter(getLast(r), create(p->coef));
            p = p->next;
            q = q->next;
        }
        else if (p->coef > q->coef)
        {
            insertAfter(getLast(r), create(q->coef));
            q = q->next;
        }
        else if (p->coef < q->coef)
        {
            insertAfter(getLast(r), create(p->coef));
            p = p->next;
        }
    }

    if (p != NULL)
        foreach (g, p)
            insertAfter(getLast(r), create(g->coef));

    else if (q != NULL)
        foreach (g, q)
            insertAfter(getLast(r), create(g->coef));

    return 1;
}
int list_intersection(Position p, Position q, Position r)
{

    if (p != NULL)
        p = p->next;
    if (q != NULL)
        q = q->next;

    while (p != NULL && q != NULL)
    {

        if (p->coef == q->coef)
        {
            insertAfter(getLast(r), create(p->coef));
            p = p->next;
            q = q->next;
        }
        else if (p->coef > q->coef)
        {

            q = q->next;
        }
        else if (p->coef < q->coef)
        {

            p = p->next;
        }
    }

    return 1;
}

int unosIzDatoteke(Position p, Position q, char *file)
{

    FILE *fp = NULL;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        puts("Neuspjesno otvaranje datoteke!");
        return -1;
    }

    int a, b;
    int n = 0;
    char buffer[lineLength];
    char *poi = NULL;
    int cnt;

    while (fgets(buffer, lineLength, fp) != NULL)
    {
        poi = buffer;
        while (*poi)
        {

            n = 0;
            cnt = sscanf(poi, "%d %d %n", &a, &b, &n);
            if (cnt >= 1)
            {
                poi += n; // no error increase pointer for amount of read characters
                // printf("%d %d %d\n", a, b, n);

                sortedInsertion(p, create(a));
                sortedInsertion(q, create(b));
            }
            else
            {
                poi++; // ERROR occured->skip one character and repeat
                perror(stderr);
            }
        }
    }

    return 0;
}

int sortedInsertion(Position where, Position what)
{

    foreach (p, where)
        if (p->next != NULL && p->next->coef > what->coef)
        {
            insertAfter(p, what);
            break;
        }
        else if (p->next == NULL)
        {
            insertAfter(p, what);
            break;
        }
}

Position getLast(Position head)
{

    Position temp = NULL;

    foreach (p, head)
        temp = p;

    return temp;
}

int insertAfter(Position where, Position what)
{
    what->next = where->next;
    where->next = what;
    return 0;
}

Position create(int k)
{

    Position el = NULL;

    el = (Position)malloc(sizeof(Node));

    if (NULL == el)
    {
        printf("Memory allocation failed!\r\n");
        return NULL;
    }

    el->coef = k;
    el->next = NULL;

    return el;
}

int printList(Position head)
{

    printf("\r\n\rLIST CONTENT:\r\n");

    if (head != NULL)
        foreach (p, head->next)
        {
            printf(" %d ", p->coef);
            if (p->next != NULL)
                printf(",");
        }

    puts("\n");

    return 0;
}