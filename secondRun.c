#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include "utils.h"
#include "castingToBinnary.h"
#include "assembler.h"
#include <stdlib.h>
Node *entLabel = NULL;
Node *allLabel = NULL;

/*this function insert all entry lable to head*/
Node *insertAllEntLabel(Node *head)
{
    return insertAllEntrylist(head, entLabel);
}

/*this function chaeck if entry sentence is correct
variable:
head-list of label of source file
line- entry line
entryNode-pointer to *node if the entry line will be correct it will cut the node thar need to entry
num of line- cuurrent line*/
bool isCorrectEntry(Node *head, char *line, Node **entryNode, int numOfLine)
{
    char label[30] = "", directive[30] = "", labelForEntry[30] = "", reserve[81] = "";
    sscanf(line, "%s%s%s%s", label, directive, labelForEntry, reserve);
    if (strlen(reserve) != 0) /*check tha nothing was wriiten after the label in accordance*/
    {
        printf("At line %d enty statement has too many operands.\n", numOfLine);
        return false;
    }
    if (label[(int)(strlen(label)) - 1] != ':') /*ignore label at the begining but update the elements */
    {
        strcpy(labelForEntry, directive);
        strcpy(directive, label);
    }
    if (strlen(labelForEntry) == 0) /*checks that there is a label*/
    {
        printf("At line %d missing label for entry.\n", numOfLine);
        return false;
    }
    if ((*entryNode = searchByName(head, labelForEntry)) == NULL) /*checks that the label exist in head */
    {
        printf("At line %d there is a label insertion statement but this label has not been defined.\n", numOfLine);
        return false;
    }
    return true;
}

/*mark all the label in head that need to extern and update entlabel for the other files*/
void markEntry(Node *entryNode)
{
    strcpy(entryNode->type, "Entry");
    entLabel = insertToStart(entLabel, entryNode->name, entryNode->text, "Entry in other", entryNode->word);
}

/*This function receives a list of words and writes them to a file of type ob
 according to their value in base32
  words-The label list
name-am file name
  ic-instruction conter
dc-Data counter
*/
void writeObFile(char words[256][11], char *name, int dc, int ic)
{
    FILE *output;
    char name_file[30], address_32[4], word_32[11], line[14], firsline[10], numOfDC[4], numOfIC[4];
    int i;
    castingNumto32Bit(dc, numOfDC);
    castingNumto32Bit(ic, numOfIC);
    strcpy(firsline, " ");
    if ((ic / 32) == 0)
    {
        numOfIC[0] = numOfIC[1];
        numOfIC[1] = '\0';
    }
    if ((dc / 32) == 0)
    {
        numOfDC[0] = numOfDC[1];
        numOfDC[1] = '\0';
    }
    strcat(firsline, numOfIC);
    strcat(firsline, " ");
    strcat(firsline, numOfDC);
    strcat(firsline, "\n");
    strcpy(name_file, name);
    strtok(name_file, ".");
    strcat(name_file, ".ob");
    output = fopen(name_file, "w+");
    fputs(firsline, output);
    for (i = 0; i < dc + ic; i++)
    {
        strcpy(address_32, "");
        strcpy(word_32, "");
        castingNumto32Bit(i + 100, address_32);
        strcpy(line, address_32);
        strcat(line, "     ");
        castingWordTo32Bits(words[i], word_32);
        strcat(line, word_32);
        strcat(line, "\n");
        fputs(line, output);
    }
    fclose(output);
}

/*A function that writes all labels of type Entry to ent file
head- list of label
name- am name file*/
void writeEntFile(Node *head, char *name)
{
    Node *temp = head;
    FILE *output;
    int counterEnt = 0, num;
    char line[45], address[5], name_file[30];
    while (temp != NULL)
    {
        if (strcmp(temp->type, "Entry") == 0)
        {
            strcpy(address, "");

            if (counterEnt == 0)
            {
                strcpy(name_file, name);
                strtok(name_file, ".");
                strcat(name_file, ".ent");
                output = fopen(name_file, "w+");
            }
            counterEnt = 1;
            strcpy(line, temp->name);
            strcat(line, "    ");
            num = atoi(temp->text);
            castingNumto32Bit(num, address);
            strcat(line, address);
            strcat(line, "\n");
            fputs(line, output);
        }
        temp = temp->next;
    }
    if (counterEnt)
    {
        fclose(output);
    }
}

/*A function that writes all labels of type Extern to ext file
head- list of label
name- am name file*/
void writeExtFie(Node *head, char *name)
{
    Node *temp = head;
    Node *extNode = NULL;
    FILE *output;
    int counterExt = 0, num;
    char line[45], address[5], name_file[30];
    while (temp != NULL)
    {
        if (strcmp(temp->type, "Extern") == 0)
        {
            strcpy(address, "");

            if (counterExt == 0)
            {
                strcpy(name_file, name);
                strtok(name_file, ".");
                strcat(name_file, ".ext");
                output = fopen(name_file, "w+");
                counterExt = 1;
            }
            extNode = searchByName(allLabel, temp->name);
            while (extNode != NULL)
            {

                strcpy(line, temp->name);
                strcat(line, "    ");
                num = atoi(extNode->text);
                castingNumto32Bit(num, address);
                strcat(line, address);
                strcat(line, "\n");
                fputs(line, output);
                extNode = extNode->next;
                extNode = searchByName(extNode, temp->name);
            }
        }
        temp = temp->next;
    }
    if (counterExt)
    {
        fclose(output);
    }
}

/*this function check if the label that in source file write ti extern it is defined in source file*/
bool isExistInSourceFile(Node *head, char *line, int numOfLine)
{
    char label[81] = "", directive[81] = "", labelForExtern[30];
    Node *temp = NULL;
    sscanf(line, "%s%s%s", label, directive, labelForExtern);
    if (label[(int)strlen(label) - 1] != ':')
    {
        strcpy(labelForExtern, directive);
        strcpy(directive, label);
    }
    temp = searchByName(head, labelForExtern);
    while (temp != NULL)
    {
        if (strcmp("Extern", temp->type) != 0)
        {
            return true;
        }
        temp = temp->next;
        temp = searchByName(temp, labelForExtern);
    }
    return false;
}

/*This function performs an algorithm according to the shield algorithm of the second pass
head- list of labels
words- the entier words
name - am file
dc-Data-Counter updated in first run.c*/
Node *sRun(Node *head, char words[256][11], char *name, int dc)
{
    FILE *input;
    int numOfLines = 0, IC = 0, L = 0;
    char firstWord[30] = "", *temp, line[81], commandType[81];
    bool isWrong = false;
    Node *entryNode = NULL, **pointerEntraNode = &entryNode;
    input = fopen(name, "r");
    if (input == NULL)
    {
        isWrong = 1;
        printf("file failed to open.\n");
        printf("please put the file in the same directory of this program.\n");
    }
    while (fgets(line, 81, input) != NULL)
    {
        strcpy(firstWord, "");
        numOfLines++;
        sscanf(line, "%s", firstWord);
        if (strlen(firstWord) == 0 || isAComment(firstWord)) /*empty or comment sentence*/
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
                strcpy(commandType, line);
                temp = strtok(commandType, ":");
                temp = strtok(NULL, ":");
                sscanf(temp, "%s", commandType);
            }
            else
            {
                strcpy(commandType, firstWord);
            }
        } /*Now updated commandType and firstword*/
        if (!isADataStorage(commandType) && strcmp(commandType, ".extern") != 0)
        {

            if (strcmp(commandType, ".entry") == 0)
            {
                if (isCorrectEntry(head, line, pointerEntraNode, numOfLines)) /*checks that entry line is correct*/
                {
                    markEntry(entryNode); /*just if yes update head*/
                    entryNode = NULL;
                }
                else
                {
                    isWrong = 1;
                }
            }
            else if ((L = encodeLabel(head, words, line, numOfLines, IC))) /*encode label at the right place*/
            {
                IC += L;
            }
            else
            {
                isWrong = 1;
                printf("At line %d an invalid sentence.\n", numOfLines);
            }
        }
        else if (strcmp(commandType, ".extern") == 0)
        {
            if (isExistInSourceFile(head, line, numOfLines)) /*check if was defined in source file*/
            {
                isWrong = 1;
            }
        }
    }
    fclose(input);
    if (!isWrong)
    {
        writeObFile(words, name, dc, IC);
        writeEntFile(head, name);
        writeExtFie(head, name);
        allLabel = insertALLDataCode(allLabel, head);
    }
    destroy(head);
    return NULL;
}

void destroyEnt()
{
    destroy(entLabel);
}

Node *searchFromAllLabel(char *name)
{
    return searchByName(allLabel, name);
}

void destroyAllLabel()
{
    destroy(allLabel);
}
