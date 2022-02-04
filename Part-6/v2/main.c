/*FIFO - insert after head - erase after last element*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define randMIN 10
#define randMAX 100
#define foreach(p, head) \
    for (Position p = head; p != NULL; p = p->next)

struct _node;
typedef struct _node *Position;
typedef struct _node
{
    int coef;
    Position next;
} Node;

Position createNode(int);
int printList(Position);

int get(Position);
int insertNode(Position, Position);

int getRandom(int, int);

int main(void)
{

    Node pHead;
    pHead.next = NULL;

    srand(time(0));

    printList(&pHead);

    for (int i = 0; i < 10; i++)
    {
        insertNode(&pHead, createNode(getRandom(randMIN, randMAX)));
        printList(&pHead);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("\nGET LAST-> %d", get(&pHead));
        printList(&pHead);
    }

    puts("");
    system("pause");

    return EXIT_SUCCESS;
}

int get(Position head)
{

    if (head->next == NULL)
        return 404;

    Position tempP = NULL;

    for (tempP = head; tempP->next->next != NULL; tempP = tempP->next)
        ;

    int temp = tempP->next->coef;
    free(tempP->next);
    tempP->next = NULL;

    return temp;
}

int getRandom(int lower, int upper)
{
    return (rand() %
            (upper - lower + 1)) +
           lower;
}

int insertNode(Position where, Position what)
{
    what->next = where->next;
    where->next = what;
    return 0;
}

Position createNode(int k)
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

    if (head->next != NULL)
    {
        printf("\r\n\rLIST CONTENT:\r\n");

        foreach (p, head->next)
        {
            printf(" %d ", p->coef);
            if (p->next != NULL)
                printf(",");
        }
    }

    else
    {
        printf("\r\n\rLIST IS EMPTY.\r\n");
    }

    puts("\n");

    return 0;
}