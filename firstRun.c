#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include <stdbool.h>
#include "utils.h"
#include "assembler.h"

/*This function performs a complete first pass according to the skeletal algorithm that appeared in the file.
It will update everything that can be translated in the first pass,
i.e. coded instruction sentences, coded instruction sentences without label addresses,
and the full list of words will be updated in words
variable:
name- am file name
head- list of label
words- array of words
dc-Data-Counter updated in first run.c*/

Node *fRun(char *name, Node *head, char words[256][11], int *numOfWord, int *DC)
{
    FILE *input;
    int numOfLines = 0, IC = 0, L = 0;
    char firstWord[81] = "", *temp, line[81], commandType[81], IC_s[81] = "", labelForExtern[30] = "";
    bool is_exist_label = false, isWrong = false;
    Node *tempNode = NULL;
    head = insertAllEntLabel(head); /*insert all labels fro other failes*/
    input = fopen(name, "r");
    if (input == NULL)
    {
        isWrong = 1;
        printf("file failed to open.\n");
        printf("please put the file in the same directory of thoprogram.\n");
    }
    while (fgets(line, 81, input) != NULL)
    {
        is_exist_label = false;
        strcpy(firstWord, "");
        numOfLines++;
        sscanf(line, "%s", firstWord);
        if (strlen(firstWord) == 0 || isAComment(firstWord)) /*emty or comment sentence*/
        {
            continue;
        }
        else
        {
            if (line[(int)strlen(line) - 1] == '\n') /*at the end of line there is A linebreak*/
            {
                line[(int)strlen(line) - 1] = '\0';
            }
            if (firstWord[(int)(strlen(firstWord)) - 1] == ':') /*if at the begining there is label*/
            {
                firstWord[(int)strlen(firstWord) - 1] = '\0';
                if (!isALabel(firstWord)) /*Check its integrity*/
                {
                    printf("At line %d there is  illegal label(%s)\n", numOfLines, firstWord);
                    continue;
                }
                if (isExist(head, firstWord)) /*Check that it is not defined twice in the source file or that it is not an address that was entered in a previous file*/
                {
                    printf("At line %d There is already another label(%s) with that name\n", numOfLines, firstWord);
                    isWrong = 1;
                    continue;
                }
                is_exist_label = true; /*turn on flag*/
                strcpy(commandType, line);
                temp = strtok(commandType, ":");
                temp = strtok(NULL, ":");
                if (temp != NULL)
                {
                    sscanf(temp, "%s", commandType);
                }
                else /*The label stands alone*/
                {
                    printf("At line %d There is a no trial label.\n", numOfLines);
                    isWrong = 1;
                    continue;
                }
            }
            else
            {
                strcpy(commandType, firstWord);
            }
        }                                /*Now updated commandType and firstword*/
        if (isADataStorage(commandType)) /*if data/string/struct*/
        {
            if ((tempNode = isDataStorageDirective(head, line, firstWord, is_exist_label, numOfWord, numOfLines, *DC)) != NULL) /*encode it just if the sentence is correct*/
            {
                head = tempNode;
                (*DC) += (*numOfWord);
                *(numOfWord) = 0;
            }
            else
            {
                isWrong = 1;
                continue;
            }
        }
        else if (strcmp(commandType, ".extern") == 0 || strcmp(commandType, ".entry") == 0)
        {
            if (strcmp(commandType, ".extern") == 0)
            {

                if ((tempNode = insertExternLabel(head, words, line, numOfLines, labelForExtern)) == NULL)
                {
                    isWrong = 1;
                }
                else
                {
                    head = tempNode;
                }
            }
        }
        else
        {
            if (is_exist_label)
            {
                if (isExist(head, firstWord) == false)
                {
                    sprintf(IC_s, "%d", IC + 100);
                    head = insertToEnd(head, firstWord, IC_s, "Code", words);
                }
                else
                {
                    isWrong = 1;
                    printf("At line %d exist alredy label.\n", numOfLines);
                    continue;
                }
            }
            if ((L = isCorrectAction(words, line, commandType, numOfLines, IC)))
            {
                IC += L;
            }
            else
            {
                isWrong = 1;
                printf("At line %d the sentence is not a valid instruction nor a valid directive.\n", numOfLines);
            }
        }
    }
    fclose(input);
    *numOfWord = 0;
    if (isWrong)
    {
        destroy(head);
        return NULL;
    }
    else
    {
        head = updateData(head, words, numOfWord, IC);
        return head;
    }
}