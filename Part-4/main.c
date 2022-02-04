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
    size_t exp;
    Position next;
} Node;

Position create(int, size_t);
Position getLast(Position);
int clone(Position);
int insertAfter(Position, Position);
int printListSum(Position);
int printListProduct(Position);
int sum(Position, Position, Position);
int multiply(Position, Position, Position);
int unosIzDatoteke(Position, Position, char *);

int main(void)
{

    Node pHead;
    pHead.next = NULL;

    Node qHead;
    qHead.next = NULL;

    Node rHead;
    rHead.next = NULL;

    Node mHead;
    mHead.next = NULL;

    unosIzDatoteke(&pHead, &qHead, "polinom.txt");

    /*
    insertAfter(getLast(&pHead), create(3,2));
    insertAfter(getLast(&pHead), create(7, 5));
    insertAfter(getLast(&pHead), create(2, 10));

    insertAfter(getLast(&qHead), create(1, 1));
    insertAfter(getLast(&qHead), create(2, 3));
    insertAfter(getLast(&qHead), create(9, 5));
    insertAfter(getLast(&qHead), create(8, 8));
    insertAfter(getLast(&qHead), create(-2, 10));
    */

    printf("\nPOLINOM p lista...");
    printListSum(&pHead);
    printf("\nPOLINOM q lista...");
    printListSum(&qHead);

    sum(&pHead, &qHead, &rHead);
    printf("\nPOLINOM r lista zbroj...");
    printListSum(&rHead);

    multiply(&pHead, &qHead, &mHead);
    printf("\nPOLINOM m lista umnozak...");
    printListProduct(&mHead);

    system("pause");

    return EXIT_SUCCESS;
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

    int a, c;
    size_t b, d;
    int n = 0;
    char buffer[lineLength];
    char *poi = NULL;
    int cnt;

    Node temp;
    Node rclone;
    Node res;
    rclone.next = NULL;

    Node temp2;
    Node rclone2;
    Node res2;
    rclone2.next = NULL;

    while (fgets(buffer, lineLength, fp) != NULL)
    {
        poi = buffer;
        while (*poi)
        {

            temp.next = NULL;
            res.next = NULL;

            temp2.next = NULL;
            res2.next = NULL;

            n = 0;
            cnt = sscanf(poi, "%d %u %d %u %n", &a, &b, &c, &d, &n);
            if (cnt >= 1)
            {
                poi += n; // no error increase pointer for amount of read characters
                // printf("%d %d %d %d %d", a, b, c, d, n);
                if (a != 0)
                {
                    insertAfter(getLast(&temp), create(a, b));
                    // insertAfter(getLast(p), create(a, b)); //if input is already sorted, faster
                }

                sum(&temp, &rclone, &res);
                rclone.next = NULL;
                clone(&res, &rclone);

                if (c != 0)
                {
                    insertAfter(getLast(&temp2), create(c, d));
                    // insertAfter(getLast(q), create(c, d)); //if input is already sorted, faster
                }

                sum(&temp2, &rclone2, &res2);
                rclone2.next = NULL;
                clone(&res2, &rclone2);
            }
            else
            {
                poi++; // ERROR occured->skip one character and repeat
                perror(stderr);
            }
        }
    }

    clone(&res, p);
    clone(&res2, q);

    return 0;
}

int sum(Position p, Position q, Position r)
{
    if (p != NULL)
        p = p->next; // skip EMPTY head elements
    if (q != NULL)
        q = q->next;
    int sum = 0;
    while (p != NULL && q != NULL)
    {

        if (p->coef != 0 && q->coef != 0)
        {
            if (p->exp == q->exp)
            {
                if (sum = (p->coef + q->coef) != 0)
                    insertAfter(getLast(r), create((p->coef + q->coef), p->exp));
                p = p->next;
                q = q->next;
            }
            else if (p->exp > q->exp)
            {
                insertAfter(getLast(r), create((q->coef), q->exp));
                q = q->next;
            }
            else if (p->exp < q->exp)
            {
                insertAfter(getLast(r), create((p->coef), p->exp));
                p = p->next;
            }
        }
        else if (p->coef == 0)
        {
            insertAfter(getLast(r), create((q->coef), q->exp));
            p = p->next;
            q = q->next;
        }
        else if (q->coef == 0)
        {
            insertAfter(getLast(r), create((p->coef), p->exp));
            p = p->next;
            q = q->next;
        }
        else // p->coef == 0 && q->coef == 0
        {
            p = p->next;
            q = q->next;
        }
    }

    if (p != NULL)
        foreach (g, p)
        {
            if (g->coef != 0)
                insertAfter(getLast(r), create((g->coef), g->exp));
        }

    else if (q != NULL)
        foreach (g, q)
        {
            if (g->coef != 0)
                insertAfter(getLast(r), create((g->coef), g->exp));
        }

    return 0;
}

int multiply(Position p, Position q, Position r)
{

    Node temp;
    Node rclone;
    Node res;

    p = p->next; // skip EMPTY head elements
    q = q->next;

    rclone.next = NULL;

    foreach (g, p)
    {

        temp.next = NULL;
        res.next = NULL;

        foreach (l, q)
        {
            insertAfter(getLast(&temp), create((g->coef * l->coef), (g->exp + l->exp)));
        }

        // printf("\n\n----->TEMP");
        // printListSum(&temp);
        // printf("----->PREVIOUS RESULT");
        // printListSum(&rclone);
        sum(&temp, &rclone, &res);
        // printf("----->CURRENT RESULT");
        // printListSum(&res);

        rclone.next = NULL;

        clone(&res, &rclone);
    }

    clone(&res, r);

    return 0;
}

int clone(Position what, Position where)
{

    foreach (p, what->next)
        insertAfter(getLast(where), create(p->coef, p->exp));

    return 0;
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

Position create(int k, size_t e)
{

    Position el = NULL;

    el = (Position)malloc(sizeof(Node));

    if (NULL == el)
    {
        printf("Memory allocation failed!\r\n");
        return NULL;
    }

    el->coef = k;
    el->exp = e;
    el->next = NULL;

    return el;
}

int printListSum(Position head)
{

    printf("\r\n\rLIST CONTENT:\r\n");

    foreach (p, head->next)
    {
        printf(" %d*x^(%u) ", p->coef, p->exp);
        if (p->next != NULL)
            printf("+");
    }

    puts("\n");

    return 0;
}

int printListProduct(Position head)
{

    printf("\r\n\rLIST CONTENT:\r\n");

    foreach (p, head->next)
    {
        printf(" %d*x^(%u) ", p->coef, p->exp);
        if (p->next != NULL)
            printf("*");
    }

    puts("\n");

    return 0;
}

// resources: https://stackoverflow.com/questions/59809443/sscanf-in-c-reading-numbers-from-a-txt-file