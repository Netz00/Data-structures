#define _CRT_SECURE_NO_WARNINGS
#define POSTFIX_LEN 1000
#define INFIX (112 + 223 + (-1 + 3)) / (-22 * 12) * (15 + 42)
#define FILENAME "postfix.txt"
#define foreach(p, head) \
    for (Position p = head; p != NULL; p = p->next)

#include <stdio.h>
#include <stdlib.h>

struct _node;
typedef struct _node *Position;
typedef struct _node
{
    int coef;
    Position next;
} Node;

Position createNode(int);
int printList(Position);

int pop(Position);
int push(Position, Position);

int calculatePostfix(Position, char *, int *);
int calculate(int, int, char);

int main(void)
{

    Node pHead;
    pHead.next = NULL;
    int r, err;
    err = calculatePostfix(&pHead, "postfix.txt", &r);

    if (err)
        return EXIT_SUCCESS;

    printList(&pHead);
    printf("\nRESULT: %2d\n", r);

    return EXIT_SUCCESS;
}

int pop(Position head)
{
    if (head->next == NULL)
    {
        printf("\nERROR: Nothing to POP!\n");
        return 404;
    }

    Position tempP = head->next;

    int temp = tempP->coef;

    head->next = tempP->next;

    free(tempP);
    tempP = NULL;

    return temp;
}

int push(Position where, Position what)
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
        printf("\r\n\rLIST IS EMPTY.\r\n");

    puts("\n");
    return 0;
}

int calculatePostfix(Position p, char *file, int *r)
{
    FILE *fp = NULL;
    int n = 0, d, res = 0;
    char c;
    char mem[POSTFIX_LEN];
    char *buffer = mem;

    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("ERROR: Failed to open '%s'\n", file);
        return 1;
    }

    fgets(mem, POSTFIX_LEN, fp);
    fclose(fp);

    printf("INFIX: %s\n", mem);
    printf("EXPECTED RESULT: %d\n\n", INFIX);

    while (*buffer != '\0')
    {
        n = 0;
        if (sscanf(buffer, "%d %n", &d, &n) >= 1)
        {
            buffer += n;
            printf("PUSH: %d ", d);
            push(p, createNode(d));
        }
        else if (sscanf(buffer, " %c %n", &c, &n) >= 1)
        {
            buffer += n;
            printf("OPERATOR: %c ", c);

            res = calculate(pop(p), pop(p), c);
            push(p, createNode(res));
            res = 0;
        }
        else
        {
            buffer++; // ERROR occured->skip one character and repeat loop
            perror(stderr);
        }
        printList(p);
    }
    *r = pop(p);
    return 0;
}

int calculate(int res, int a, char c)
{
    switch (c)
    {
    case '+':
        return res + a;
        break;
    case '-':
        return res - a;
        break;
    case '*':
        return res * a;
        break;
    case '/':
        return res / a;
        break;
    default:
        printf("\nERROR: Not valid operand '%c' , inspect your postfix expression please.\n", c);
        return res;
        break;
    }
}