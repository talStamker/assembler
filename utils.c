#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "utils.h"

#define PRINT(x) \
	printf("%s\n", x ? "true" : "false");

/*This function checks that a number is indeed correct,
and takes into account that it can start with a plus or minus*/
bool isANum(char *st)
{
	int i = 0;
	if (strlen(st) == 0)
	{
		return false;
	}
	if (st[0] == '+' || st[0] == '-') /*can appear at the beginning of a number*/
		i++;
	for (; i < strlen(st); i++)
	{
		if (!isdigit(st[i])) /*If there is a non-number character after the plus it will return false*/
		{
			return false;
		}
	}
	return true;
}

/*This function checks that the received register is valid*/
bool isARegister(char *name)
{
	if (strlen(name) != 2) /*r1..r8 have 2 char*/
	{
		return false;
	}
	if (name[0] != 'r')
	{
		return false;
	}
	if (name[1] < '0' || name[1] > '9') /*can be from1 to 8*/
	{
		return false;
	}
	return true;
}

/*This function checks that the label is syntactically correct*/
bool isALabel(char *label)
{
	int j;
	if (isalpha(label[0]) == false || isARegister(label)) /*A register meets the requirements of a label, so we will first check that it is not a register*/
	{
		return false;
	}
	for (j = 0; j < strlen(label); j++)
	{
		if (isalnum(label[j]) == false) /*All other characters must be a number or alpha*/
		{
			return false;
		}
		if (j > 30) /*size no more than 30*/
		{
			return false;
		}
	}
	return true;
}

/*This function checks whether the address is immediate*/
bool isImmediate(char *name)
{
	if (name[0] != '#') /*Always start with:# */
	{
		return false;
	}
	name++;
	return isANum(name); /*after # must be munber*/
}

/*This function checks that it is a label and an index */
bool isAccessToList(char *name)
{
	char nameC[81], *temp;
	strcpy(nameC, name);
	temp = strtok(nameC, ".");
	if (isALabel(temp) == false) /*befor '.' must be label*/
	{
		return false;
	}
	temp = strtok(NULL, ".");
	if (temp == NULL || (*temp) == '-') /*index nust be positive and have to be '.'*/
	{
		return false;
	}
	return isANum(temp); /*index*/
}

/*This function checks that it is a comment sentence*/
bool isAComment(char *name)
{
	if (name[0] == ';') /*the first char must be ';'*/
		return true;

	return false;
}

/*This function checks
whether the string it received is the instruction to store data*/
bool isADataStorage(char *data_storage)
{
	if (strcmp(data_storage, ".string") == 0 || strcmp(data_storage, ".data") == 0 || strcmp(data_storage, ".struct") == 0) /*The clue is what kind of data to store*/
	{
		return true;
	}
	return false;
}

/*This function checks whether the string received is an instruction
and if so returns the opcode of the instruction*/
int getOpcode(char *name)
{
	char opcode[][4] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", "get", "prn", "jsr", "rts", "hlt"}; /*all action name*/
	int i = 0;
	for (; i < 16; i++)
	{
		if (strcmp(opcode[i], name) == 0)
		{
			return i;
		}
	}
	return -1;
}

/*This function checks if there is a comma at the beginning.*/
bool isCommaAtTheBeginning(char *directive)
{
	int i = 0;
	while (i < strlen(directive) && isspace(directive[i])) /*Continues as long as it is profitable*/
	{
		i++;
	}
	return directive[i] == ',';
}

/*This function checks if there is a comma at the end.*/
bool isCommaAtTheEnd(char *directive)
{
	int i = (int)strlen(directive) - 1;
	while (i >= 0 && isspace(directive[i])) /* go down as long as it is profitable*/
	{
		i--;
	}
	return directive[i] == ',';
}

/*This function checks whether the entire string is only spaces.*/
bool space(char st[81])
{
	int i = 0;
	for (; i < strlen(st); i++)
	{
		if (isspace(st[i]) == 0) /*this char is not space*/
		{
			return false;
		}
	}
	return true;
}

/*This function checks whether the command with this opcode has no operands.*/
bool isNonOperand(int opcode)
{
	return opcode == 15 || opcode == 14; /*hlt,rts*/
}

/*This function checks whether the command with this opcode has one operands*/
bool isOneOperand(int opcode)
{
	if (opcode == 4 || opcode == 5 || (opcode >= 7 && opcode <= 13)) /*not,clr,inc,dec,jmp,bne,get,prn,jsr*/
	{
		return true;
	}
	return false;
}

/*This function checks whether the command with this opcode has two operands*/
bool isTwoOperand(int opcode)
{
	if (opcode == 6 || (opcode >= 0 && opcode <= 3)) /*mov,cmp,add,sub,lea*/
	{
		return true;
	}
	return false;
}