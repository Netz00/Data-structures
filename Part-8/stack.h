#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define randMIN 10
#define randMAX 100
#define foreachStack(p, head) \
    for (Stackpos p = head; p != NULL; p = p->next)

struct _stack;
typedef struct _stack *Stackpos;
typedef struct _stack
{
    Position sDir;
    Stackpos next;
} Stack;

Stackpos createNode(Position);
int printStack(Stackpos);

Position pop(Stackpos);
int push(Stackpos, Stackpos);