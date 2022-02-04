#include "BinarySearchTree.h"

Position insertNode(Position root, int coef)
{

    if (root == NULL)
    {
        return createNode(coef);
    }

    if (root->coef > coef)
    {
        root->left = insertNode(root->left, coef);
    }
    else if (root->coef < coef)
    {
        root->right = insertNode(root->right, coef);
    }

    return root;
}
Position deleteTree(Position root)
{
    if (root != NULL)
    {
        root->left = deleteTree(root->left);
        root->right = deleteTree(root->right);
        free(root);
    }
    return NULL;
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
    el->left = NULL;
    el->right = NULL;

    return el;
}
Position findNode(Position root, int coef)
{

    if (root == NULL)
        return NULL;

    if (root->coef > coef)
        return findNode(root->left, coef);

    else if (root->coef < coef)
        return findNode(root->right, coef);

    else
        return root;
}
Position findMin(Position root)
{

    if (root != NULL)
        if (root->left != NULL)
            return findMin(root->left);

    return root;
}
Position findMax(Position root)
{

    if (root != NULL)
        if (root->right != NULL)
            return findMax(root->right);

    return root;
}
Position deleteNode(Position root, int coef)
{
    Position temp = NULL;

    if (root == NULL)
    {
        printf("\nElement sa vrijednosti %d ne postoji.\n", coef);
        return NULL;
    }

    if (root->coef > coef)
    {
        root->left = deleteNode(root->left, coef);
    }
    else if (root->coef < coef)
    {
        root->right = deleteNode(root->right, coef);
    }
    else if (root->left != NULL && root->right != NULL)
    {
        temp = findMax(root->left);
        root->coef = temp->coef;
        root->left = deleteNode(root->left, temp->coef);
    }
    else
    {
        temp = root;

        if (root->left == NULL)
            root = root->right;
        else
            root = root->left;

        free(temp);
        temp = NULL;
    }

    return root;
}
void printList(Position head, int n)
{

    printf("\n");

    for (int i = 0; i < n - 1; i++)
    {
        printf("\t");
    }

    if (head == NULL)
    {
        return;
    }

    if (n > 0)
        printf("|");

    if (n > 0)
        printf("_______");

    printNode(head);

    printList(head->left, n + 1);

    printList(head->right, n + 1);
}
void printNode(Position head)
{
    if (head == NULL)
        puts("");

    else
        printf("%d", head->coef);
}