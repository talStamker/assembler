#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include "assembler.h"
#include "utils.h"
#include "castingToBinnary.h"

/*This function checks that the label has indeed been defined,
 and updates its address in the appropriate place
 head-list of label
 words-The label list
 oprand-label
 i- the corrent conter
 num of line-the corrent line in am file*/
int counterAndUpdateWord(Node *head, char words[256][11], char *oprand, int i, int numofline)
{
    Node *label_node = searchByName(head, oprand);
    if (label_node == NULL)
    {
        printf("At line %d there is an undefined label(%s).\n", numofline, oprand);
        return 0;
    }
    numTo8Bits(label_node->text, words[i]);
    if (strcmp(label_node->type, "Extern") == 0 || strcmp(label_node->type, "Entry in other") == 0) /*No need to allocate space in memory*/
    {
        strcat(words[i], "01");
    }
    else
    { /*need to*/
        strcat(words[i], "10");
    }
    i++;
    return i;
}

/*This function encodes labels in the appropriate place.
head-list of label
 words-The label list
 line- the corrent line
  ic-instruction conter
 num of line-the corrent line in am file*/
int encodeLabel(Node *head, char words[256][11], char *line, int numofline, int IC)
{
    char label[30] = "", directive[30] = "", oprand1[81] = "", oprand2[81] = "", *temp;
    int opcode, i = IC + 1;
    temp = strtok(line, ",");
    sscanf(temp, "%s%s%s", label, directive, oprand1);
    if (label[(int)(strlen(label)) - 1] != ':')
    {
        strcpy(oprand1, directive);
        strcpy(directive, label);
    }
    opcode = getOpcode(directive);
    if (isNonOperand(opcode)) /* all one operand action sentence have one word*/
    {
        return i - IC;
    }
    else if (isOneOperand(opcode))
    {
        if (isARegister(oprand1) || isImmediate(oprand1)) /* register one word to the number of registe,immediate one word to the number*/
        {
            i++;
        }
        else if (isALabel(oprand1))
        {
            i = counterAndUpdateWord(head, words, oprand1, i, numofline); /*checks where the label needs to encond, encode it and return the next index*/
        }
        else
        {
            strtok(oprand1, ".");
            i = counterAndUpdateWord(head, words, oprand1, i, numofline); /*checks where the label needs to encond, encode it and return the next index*/
            if (i)
            {
                i++;
            }
        }
        if (!i)
        {
            return 0;
        }
    }
    else if (isTwoOperand(opcode))
    {
        temp = strtok(NULL, ",");
        sscanf(temp, "%s", oprand2);
        if (isARegister(oprand1) && isARegister(oprand2)) /*for two register one word*/
        {
            return 2;
        }
        if (isARegister(oprand1) || isImmediate(oprand1)) /* register- one word to the number of registe,immediate- one word to the number*/
        {
            i++;
        }
        else if (isALabel(oprand1))
        {
            i = counterAndUpdateWord(head, words, oprand1, i, numofline); /*checks where the label needs to encond, encode it and return the next index*/
        }
        else
        {
            strtok(oprand1, ".");
            i = counterAndUpdateWord(head, words, oprand1, i, numofline); /*checks where the label needs to encond, encode it and return the next index*/
            if (i)
            {
                i++;
            }
        }
        if (!i)
        {
            return 0;
        }
        if (isARegister(oprand2) || isImmediate(oprand2)) /* register- one word to the number of registe,immediate- one word to the number*/
        {
            i++;
        }
        else if (isALabel(oprand2))
        {
            i = counterAndUpdateWord(head, words, oprand2, i, numofline); /*checks where the label needs to encond, encode it and return the next index*/
        }
        else
        {
            strtok(oprand2, ".");
            i = counterAndUpdateWord(head, words, oprand2, i, numofline); /*checks where the label needs to encond, encode it and return the next index*/
            if (i)
            {
                i++;
            }
        }
        if (!i)
        {
            return 0;
        }
    }
    return i - IC;
}