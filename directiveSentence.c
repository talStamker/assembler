#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include <stdbool.h>
#include "utils.h"
#include <stdbool.h>
#include "castingToBinnary.h"
#include "assembler.h"
#include <stdlib.h>
/*This department deals with directive sentences in assembly language.
All the handling of the encoding directive and counting places in the memory is done here*/

/*This function checks whether the sentence of type DATA is correct.
 If so, code it into an array of words.
Inserts into the linked list that preserves its encoding.
variabel:
 head-The linked list into which all symbols go
Words-The list of words to be assigned to the directive sentence.
line- line in the am file
firstWord- The first word in the line
num of word- The number of words required for this prompt.
num of line- Line number in the am file
Data-Counter updated in first run.c*/
Node *isCorrectData(Node *head, char words[256][11], char line[81], char firstWord[81], int *numOfWord, int numOfLine, int DC)
{
    char *temp, *commasTest, directive[81] = "", label[81] = "", num[81] = "";
    char dc_s[5];
    int i = 0;
    sscanf(line, "%s%s%s", label, directive, num);
    if (isCommaAtTheEnd(line)) /*Checks that there is no comma at the end.*/
    {
        printf("At line %d directive (.data)sentence with a comma at the end.\n", numOfLine);
        *numOfWord = 0;
        return NULL;
    }
    if (isCommaAtTheBeginning(num)) /*Checks that there is no comma at the beginning.*/
    {
        printf("At line %d directive (.data) sentence with a comma before the first number.\n", numOfLine);
        *numOfWord = 0;
        return NULL;
    }
    commasTest = strstr(line, ",,");
    if (commasTest != NULL) /*Checks that there are no two commas between numbers*/
    {
        printf("At line %d directive (.data) there are two commas between two numbers.\n", numOfLine);
        *numOfWord = 0;
        return NULL;
    }
    temp = strtok(line, ",");
    sscanf(temp, "%s%s%s", label, directive, num);
    if (!isANum(num)) /*Checks that the first character in the list is a number*/
    {
        printf("At line %d directive(.data) there is a wrong number(%s).\n", numOfLine, num);
        *numOfWord = 0;
        return NULL;
    }
    else
    {
        (*numOfWord)++;             /*counting it*/
        numTo10Bits(num, words[i]); /*Encoding the number*/
        i++;
    }
    while ((temp = strtok(NULL, ",")) != NULL) /*Continue to the next number*/
    {
        strcpy(num, temp);
        if (space(num)) /*If there is a space it means there are two commas between two digits*/
        {
            printf("At line %d directive(.data) there are two commas between two numbers.\n", numOfLine);
            return NULL;
        }
        sscanf(temp, "%s", num);
        if (!isANum(num)) /*Checks that there is a number between the commas*/
        {
            printf("At line %d (.directive) there is a wrong number(%s).\n", numOfLine, num);
            return NULL;
        }
        else
        {
            (*numOfWord)++;             /*counting it*/
            numTo10Bits(num, words[i]); /*Encoding the number*/
            i++;
        }
    }
    sprintf(dc_s, "%d", DC);                                  /* current dc not all of this directive sentence.*/
    head = insertToEnd(head, firstWord, dc_s, "Data", words); /*Entry into the list after coding*/
    return head;
}

/*This function updates all style symbols given the IC,
 and updates their encoding in the words array
 variable:
 head-linked list
 words-all the words in first run
 size- the size of words that ful in first run
 ic-instruction conter */
Node *updateData(Node *head, char words[256][11], int *size, int IC)
{
    Node *temp = head;
    int dc, i = 0;
    *size = IC; /*Not all of this directive sentence*/
    while (temp != NULL)
    {
        i = 0;
        if (strcmp(temp->type, "Data") == 0)
        {
            dc = atoi(temp->text) + 100; /*The addresses start from*/
            dc += IC;                    /*We numbered the legal position of the instruction after that we add the
             place rule of the instruction sentences and the address 100*/
            sprintf(temp->text, "%d", dc);
            while (strlen((temp->word)[i]) != 0)
            {
                strcpy(words[(*size)], (temp->word)[i]); /*Copies the full encoding of the label to the general encoding*/
                (*size)++;
                i++;
            }
        }
        temp = temp->next;
    }
    return head;
}

/*This function checks whether the sentence of type STRING/STRUCT is correct.
 If so, code it into an array of words.
Inserts into the linked list that preserves its encoding.
variabel:
head-The linked list into which all symbols go.
Words-The list of words to be assigned to the directive sentence.
st- The string that needs to be coded.
firstWord- The first word in the line in am file
num of word- The number of words required for this prompt.
num of line- Line number in the am file.
DC-Data Counter updated in first run.c*/
Node *isCorrectString(Node *head, char words[256][11], char *st, char firstWord[81], int *numOfWord, int numOfLine, int DC)
{
    char Apostrophes[5] = "", reserve[81] = "", *pSt = NULL, ascllValueSt[5], dc_s[81];
    int i = 0, ascllValue;
    Apostrophes[0] = (char)34;
    Apostrophes[2] = '\0';
    while ((st = strstr(st, Apostrophes)) != NULL) /*Proceed to the following quotation marks*/
    {
        st += 1;    /*st without the first brackets*/
        if (i == 0) /*st stands after the first parentheses*/
        {
            pSt = st;
            for (; (*pSt) && (*pSt) != 34; (*numOfWord)++, pSt++)
            {
                ascllValue = *pSt; /*asscill*/
                sprintf(ascllValueSt, "%d", ascllValue);
                numTo10Bits(ascllValueSt, words[(*numOfWord)]);
            }
            strcpy(words[(*numOfWord)], "0000000000"); /*'\0'*/
            (*numOfWord)++;
        }
        if (i == 1)
        {
            sscanf(st, "%s", reserve);
            if (strlen(reserve))
            {
                printf("At line %d something was written after the string(%s).\n", numOfLine, reserve);
                return NULL;
            }
        }
        i++;
    }
    if (i == 2) /*ther is two quotation marks */
    {
        sprintf(dc_s, "%d", DC);
        head = insertToEnd(head, firstWord, dc_s, "Data", words);
        return head;
    }
    else /*missing: ""*/
    {
        printf("At line %d the directive sentence is missing a string.\n", numOfLine);
        return NULL;
    }
}

/*This function checks whether the sentence of type STRUCT is correct.
 If so, code it into an array of words.
Inserts into the linked list that preserves its encoding.
variabel:
head-The linked list into which all symbols go.
Words-The list of words to be assigned to the directive sentence.
line- line in the am file.
firstWord- The first word in the line in am file
num of word- The number of words required for this prompt.
num of line- Line number in the am file.
DC-Data Counter updated in first run.c*/
Node *isCorrectStruct(Node *head, char words[256][11], char *line, char *firstWord, int *numOfWord, int numOfLine, int DC)
{
    char label[81] = " ", directive[81] = " ", num[81] = " ", *temp = NULL, *n = NULL;
    temp = strtok(line, ",");
    if (temp == NULL) /*must be comma*/
    {
        printf("At line %d missing a comma.\n ", numOfLine);
        head = NULL;
        return head;
    }
    sscanf(temp, "%s%s%s", label, directive, num);
    if (!isANum(num)) /*checks if befor comma there is a number*/
    {
        printf("At line %d the directive sentence is missing a number.\n", numOfLine);
        head = NULL;
        return head;
    }
    else
    {
        n = num;
        if (num[0] == '+')
        {
            n++;
        }
        numTo10Bits(n, words[0]); /*encoding the number*/
    }
    temp = strtok(NULL, ",");
    if (temp == NULL) /*nust have string after comma*/
    {
        printf("At line %d the directive sentence is missing a string.\n", numOfLine);
        head = NULL;
        return head;
    }
    (*numOfWord)++;
    head = isCorrectString(head, words, temp, firstWord, numOfWord, numOfLine, DC); /*encoding the string*/
    return head;
}

/*This function inserts all external type symbols into the symbol table.
variabel:
head-The linked list into which all symbols go.
Words-The list of words to be assigned to the directive sentence.
line- line in the am file.
num of line- Line number in the am file.
labelForExtern- the label that we need to insert*/
Node *insertExternLabel(Node *head, char words[256][11], char *line, int numOfLines, char *labelForExtern)
{
    char label[81] = "", directive[81] = "", reserve[81] = "";
    sscanf(line, "%s%s%s%s", label, directive, labelForExtern, reserve);
    if (label[(int)strlen(label) - 1] != ':')
    {
        strcpy(labelForExtern, directive);
        strcpy(directive, label);
    }
    if (strlen(reserve))
    {
        printf("At line %d something was written after the label you wanted to insert.\n", numOfLines);
        return NULL;
    }
    if (!isALabel(labelForExtern)) /*illegal label foe extern*/
    {
        printf("At line %d there is invalid label.\n", numOfLines);
        return NULL;
    }
    if ((searchFromAllLabel(labelForExtern)) == NULL) /*Look for whether the label has been betrayed in previous files*/
    {
        printf("At line %d there is extern to undefine label.\n", numOfLines);
        return NULL;
    }
    head = insertToEnd(head, labelForExtern, "0", "Extern", words);
    return head;
}

/*This function handles all instruction sentences of any type,
encodes them and checks how many words are required to encode them
variabel:
head-The linked list into which all symbols go.
line- line in the am file.
firstWord- The first word in the line in am file
isExistLabel-Notifies if there is a label at the beginning of the line.
num of word- The number of words required for this prompt.
num of line- Line number in the am file.
Data-Counter updated in first run.c*/
Node *isDataStorageDirective(Node *head, char *line, char *firstWord, bool isExistLabel, int *numOfWord, int numOfline, int DC)
{
    char label[81] = "", directive[81] = "", temp[81] = "", *st = NULL, words[256][11] = {""}, reserve[81] = "";
    if (!isExistLabel) /*nust be label at the begining*/
    {
        printf("At line %d there is no label that stores the data.\n", numOfline);
        return NULL;
    }
    sscanf(line, "%s%s%s%s", label, directive, temp, reserve);
    if (strlen(temp) == 0) /*in data string and strucrt must be full*/
    {
        printf("At line %d is missing details for directive sentence.\n", numOfline);
        return NULL;
    }
    st = temp;
    if (strcmp(directive, ".data") == 0)
    {
        head = isCorrectData(head, words, line, firstWord, numOfWord, numOfline, DC); /*encode data sentence if it is correct*/
        return head;
    }
    else if (strcmp(directive, ".string") == 0)
    {
        if (strlen(reserve) != 0)
        {
            printf("At line %d somthing writen after the string(%s).\n", numOfline, reserve);
            return NULL;
        }

        head = isCorrectString(head, words, st, firstWord, numOfWord, numOfline, DC); /*encode string sentence if it is correct*/
        return head;
    }
    else if (strcmp(directive, ".struct") == 0)
    {
        head = isCorrectStruct(head, words, line, firstWord, numOfWord, numOfline, DC); /*encode struct sentence if it is correct*/
        return head;
    }
    else
    {
        return NULL;
    }
}