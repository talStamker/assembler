
#include <stdbool.h>
#include <stdio.h>
#include "utils.h"
#include "castingToBinnary.h"
#include <string.h>
#include "assembler.h"
/*This department handles action sentences,
 checks whether they are correct and to what extent, and codes them*/

/*This function encodes simple operations with 2 operands or with 1 operand.
variable:
numOfOprand-Number of operands in the instruction statement
words- The general array of the entire am file.
operand1-the first operand
oprand2- the second operand
ic-instruction conter
immediateS-Checks if sorce is an immediate address
immediateD-Checks if destination is an immediate address
labelS-Checks if sorce is a direct address
labelD-Checks if destination is a direct address
registerS-Checks if sorce is an direct register address
registerD-Checks if destination is adirect register address
accessToListS-Checks if sorce is an access to list address
accessToListD-Checks if destination is an an access to list address
*/
int encodeAction(int numOfOprand, char words[256][11], char *oprand1, char *oprand2, int IC, bool immediateS, bool immediateD, bool labelS, bool labelD, bool registerS, bool registerD, bool accessToListS, bool accessToListD)
{
    int i = IC;
    char tempS[81], tempD[81], *temp_s, *temp_d, dest[5];
    ;
    if (numOfOprand == 1) /*sorce is 0*/
    {
        strcpy(tempD, oprand1);
        strcat(words[IC], "00");
        i++;
    }
    else
    {
        strcpy(tempS, oprand1);
        strcpy(tempD, oprand2);
    }
    temp_d = tempD;
    temp_s = tempS;
    if (immediateS)
    {
        temp_s++;
        strcat(words[IC], "00");
        i++;
        numTo8Bits(temp_s, words[i]);
        strcat(words[i], "00");
        i++;
    }
    else if (labelS)
    {
        strcat(words[IC], "01");
        i++;
    }
    else if (registerS)
    {
        strcat(words[IC], "11");
        i++;
        registerTo4Bits(tempS, words[i]);
        if (registerD)
        {
            strcat(words[IC], "1100");
            registerTo4Bits(tempD, dest);
            strcat(words[i], dest);
            strcat(words[i], "00");
            i++;
            return i - IC;
        }
        strcat(words[i], "000000");
        i++;
    }
    else if (accessToListS)
    {
        strcat(words[IC], "10");

        temp_s = strtok(tempS, ".");
        temp_s = strtok(NULL, ".");
        i++;
        i++;
        numTo8Bits(temp_s, words[i]);
        strcat(words[i], "00");
        i++;
    }
    if (immediateD)
    {
        temp_d++;
        strcat(words[IC], "00");
        numTo8Bits(temp_d, words[i]);
        strcat(words[i], "00");
        i++;
    }
    else if (labelD)
    {
        strcat(words[IC], "01");
        i++;
    }
    else if (registerD)
    {
        strcat(words[IC], "11");
        strcpy(words[i], "0000");
        registerTo4Bits(tempD, dest);
        strcat(words[i], dest);
        strcat(words[i], "00");
        i++;
    }
    else if (accessToListS)
    {
        strcat(words[IC], "10");
        temp_d = strtok(tempD, ".");
        temp_d = strtok(NULL, ".");
        i++;
        numTo8Bits(temp_d, words[i]);
        strcat(words[i], "00");
        i++;
    }
    strcat(words[IC], "00");
    return i - IC;
}

/*This function checks the correctness of instruction sentences,
 and encodes them if they are correct
 words-array of words in first run.
 line- line in am file
 commandtype-action type
 num of line- num of corrent line
 ic-instruction conter */
int isCorrectAction(char words[256][11], char *line, char *command_type, int numOfLine, int IC)
{
    int opcode = getOpcode(command_type);
    bool iscorrect = false, immediate_s = false, immediate_d = false, label_s = false, label_d = false, register_s = false, register_d = false, access_to_list_s = false, access_to_list_d = false;
    char label[81] = "", action[81] = "", oprand1[81] = "", oprand2[81] = "", *temp, isWrong[81] = "";
    if (opcode == -1)
    {
        printf("At line %d there is an invalid action name(%s).\n", numOfLine, command_type);
        return 0;
    }
    temp = strtok(line, ",");
    sscanf(temp, "%s%s%s", label, action, oprand1);
    if (label[(int)strlen(label) - 1] != ':')
    {
        strcpy(oprand1, action);
        strcpy(action, label);
    }
    if (isNonOperand(opcode))
    {
        if (strlen(oprand1) == 0)
        {
            numTo4Bits(opcode, words[IC]);
            strcat(words[IC], "000000");
            return 1;
        }
        else
        {
            printf("At line %d there are too many operangs.\n", numOfLine);
            return 0;
        }
    }
    else
    {
        temp = strtok(NULL, ",");
        if (isTwoOperand(opcode))
        {
            if (strlen(oprand1) == 0 || temp == NULL)
            {

                printf("At line %d missing operangs.\n", numOfLine);
                return 0;
            }
            sscanf(temp, "%s%s", oprand2, isWrong);
            if (strlen(isWrong) != 0)
            {
                printf("At line %d there are too many oprangs.\n", numOfLine);
                return 0;
            }
            numTo4Bits(opcode, words[IC]);
            if (opcode >= 0 && opcode <= 3)
            {
                if ((label_s = isALabel(oprand1)) || (register_s = isARegister(oprand1)) || (immediate_s = isImmediate(oprand1)) || (access_to_list_s = isAccessToList(oprand1)))
                {
                    if ((label_d = isALabel(oprand2)) || (access_to_list_d = isAccessToList(oprand2)) || (register_d = isARegister(oprand2)))
                    {
                        iscorrect = true;
                    }
                    else if (opcode == 1 && (immediate_d = isImmediate(oprand2)))
                    {
                        iscorrect = true;
                    }
                    else
                    {
                        printf("At line %d in acction sentence there is invalid destination (%s).\n", numOfLine, oprand2);
                        return 0;
                    }
                }
                else
                {
                    printf("At line %d  in acction sentence there is invalid source (%s).\n", numOfLine, oprand1);
                    return 0;
                }
            }
            else
            {
                if ((label_s = isALabel(oprand1)) || (access_to_list_s = isAccessToList(oprand1)))
                {
                    if ((label_d = isALabel(oprand2)) || (access_to_list_d = isAccessToList(oprand2)) || (register_d = isARegister(oprand2)))
                    {
                        iscorrect = true;
                    }
                    else
                    {
                        printf("At line %d in acction sentence there is invalid destination (%s).\n", numOfLine, oprand2);
                        return 0;
                    }
                }
                else
                {
                    printf("At line %d  in acction sentence there is invalid source (%s).\n", numOfLine, oprand1);
                    return 0;
                }
            }
            if (iscorrect)
            {
                return encodeAction(2, words, oprand1, oprand2, IC, immediate_s, immediate_d, label_s, label_d, register_s, register_d, access_to_list_s, access_to_list_d);
            }
        }
        else if (isOneOperand(opcode))
        {
            if (temp != NULL)
            {
                printf("At line %d there are too many oprangs.\n", numOfLine);
                return 0;
            }
            if (strlen(oprand1) == 0)
            {
                printf("At line %d missing operangs.\n", numOfLine);
                return 0;
            }

            numTo4Bits(opcode, words[IC]);
            if ((label_d = isALabel(oprand1)) || (access_to_list_d = isAccessToList(oprand1)) || (register_d = isARegister(oprand1)))
            {
                iscorrect = true;
            }
            else if (opcode == 12 && (immediate_d = isImmediate(oprand1)))
            {
                iscorrect = true;
            }
            else
            {
                printf("At line %d in acction sentence there is invalid destination (%s).\n", numOfLine, oprand1);
                return 0;
            }
            if (iscorrect)
            {
                return encodeAction(1, words, oprand1, oprand2, IC, immediate_s, immediate_d, label_s, label_d, register_s, register_d, access_to_list_s, access_to_list_d);
            }
        }
        if (!iscorrect)
        {
            printf("At line %d operation does not match type in operands.\n", numOfLine);
            return 0;
        }
    }
    return 0;
}