
#include "tree.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

Position pop(Stackpos head)
{
    if (head->next == NULL)
        return NULL;

    Stackpos tempP = head->next;
    Position temp = tempP->sDir;

    head->next = tempP->next;

    free(tempP);
    tempP = NULL;

    return temp;
}

int push(Stackpos where, Stackpos what)
{
    what->next = where->next;
    where->next = what;
    return 0;
}

Stackpos createNode(Position k)
{

    Stackpos el = NULL;

    el = (Stackpos)malloc(sizeof(Stack));

    if (NULL == el)
    {
        printf("Memory allocation failed!\r\n");
        return NULL;
    }

    el->sDir = k;
    el->next = NULL;

    return el;
}

int printStack(Stackpos head)
{

    if (head == NULL)
        return 0;

    printStack(head->next);

    printf("%s", head->sDir->dir);

    if (head->next != NULL)
        printf("\\");

    return 0;
}