#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct _node;
typedef struct _node *Position;
typedef struct _node
{
    int coef;
    Position left;
    Position right;
} Node;

Position insertNode(Position, int); // inserts new value in binary search tree
Position deleteTree(Position);      // deletes complete binary search tree
Position findNode(Position, int);   // searches value through tree and returns node address if found or NULL if not found
void printList(Position, int);
Position deleteNode(Position, int);

Position findMin(Position);
Position findMax(Position);

Position createNode(int);
void printNode(Position);
