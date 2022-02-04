#include "BinarySearchTree.h"

int main(void)
{
    Position root = NULL;
    Position temp = NULL;

    root = insertNode(root, 4);

    root = insertNode(root, 2);
    root = insertNode(root, 15);

    root = insertNode(root, 1);
    root = insertNode(root, 3);
    root = insertNode(root, 10);
    root = insertNode(root, 20);

    root = insertNode(root, 6);
    root = insertNode(root, 11);

    root = insertNode(root, 7);

    root = insertNode(root, 8);

    root = insertNode(root, 9);

    printList(root, 0);

    temp = findNode(root, 10);
    if (temp == NULL)
        printf("\nElement %d nije pronadjen.\n", 10);
    else
        printf("\nElement je pronadjen \nvrijednost: %d adresa:\t0x%08p\n", temp->coef, temp);

    root = deleteNode(root, 10);

    printList(root, 0);

    temp = findNode(root, 10);
    if (temp == NULL)
        printf("\nElement %d nije pronadjen.\n", 10);
    else
        printf("\nElement je pronadjen \nvrijednost: %d adresa:\t0x%08p\n", temp->coef, temp);

    root = deleteTree(root);

    printList(root, 0);

    system("pause");
    return EXIT_SUCCESS;
}
