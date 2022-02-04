#include "main.h"
#include "tree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    Position current = NULL;
    Position temp = NULL;
    current = newDir("C:\\");
    Stack pHead;
    pHead.next = NULL;
    pHead.sDir = NULL;

    char inputBuff[COMMAND_LEN] = {'\0'};

    printf("Welcome to DOS simualtor!\nAllowed commands: \n\t\tmd [dir]\n\t\tcd [dir]\n\t\tcd ..\n\t\tdir \n\t\texit\n\n");

    do
    {

        printStack(pHead.next);
        printf("%s>", current->dir);
        scanf(" %s", inputBuff);

        if (strcmp(inputBuff, "md") == 0)
        {

            scanf(" %s", inputBuff);

            insertDir(current, newDir(inputBuff));
        }
        else if (strcmp(inputBuff, "cd") == 0)
        {
            scanf(" %s", inputBuff);

            if (strcmp(inputBuff, "..") == 0)
            {

                temp = pop(&pHead);

                if (temp != NULL)
                    current = temp;
            }
            else
            {

                temp = findDir(current, inputBuff);

                if (temp == NULL)
                {
                    printf("The system cannot find the path specified.\n");
                }
                else
                {
                    push(&pHead, createNode(current));

                    current = temp;
                }
            }
        }
        else if (strcmp(inputBuff, "dir") == 0)
        {

            printDir(current);
        }
        else if (strcmp(inputBuff, "cls") == 0)
        {

            system("cls");
        }
        else if (strcmp(inputBuff, "exit") != 0)
        {

            printf("'%s' is not recognized as an internal or external command,\noperable program or batch file.\n", inputBuff);
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }

    } while (strcmp(inputBuff, "exit") != 0);

    while ((temp = pop(&pHead)) != NULL)
        current = temp;

    current = delete (current);

    system("pause");

    return EXIT_SUCCESS;
}