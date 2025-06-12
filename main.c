#include <stdio.h>
#include "linkedList.h"
#include <string.h>
#include "assembler.h"
#include <stdlib.h>

void clean(char words[256][11], int numOfWords)
{
    int i = 0;
    for (i = 0; i < numOfWords; i++)
    {
        strcpy(words[i], "");
    }
}
int main(int argc, char *argv[])
{
    Node *head = NULL;
    char words[256][11] = {""}, as[] = ".as", am[] = ".am", name_file[30];
    int a = 0, *numOfWords = &a, dc = 0, *DC = &dc, i = 1;
    for (; i < argc; i++, *DC = 0, *numOfWords = 0)
    {
        head = NULL;
        strcpy(name_file, argv[i]);
        strcat(name_file, as);
        makeAmFile(name_file);
        strcpy(name_file, argv[i]);
        strcat(name_file, am);
        head = fRun(name_file, head, words, numOfWords, DC);
        if ((*numOfWords))
        {
            head = sRun(head, words, name_file, dc);
            clean(words, *numOfWords);
        }
    }
    destroyEnt();
    destroyAllLabel();
    return 0;
}