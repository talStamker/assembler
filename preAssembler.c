#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "linkedList.h"
#include "assembler.h"
/*This function accepts a source file and interprets the macro in the source file*/
void makeAmFile(char *name)
{
	char words[256][11] = {""};
	char outputName[40];
	char tempFileName[] = "temp_file";
	char am[] = ".am";
	FILE *input, *output, *temp_file;
	char line[81], correntMacroName[81];
	char temp_str[81] = "";
	bool inMacro = false;
	char macro[] = "macro";
	char endmacro[] = "endmacro";
	Node *macroList = NULL;
	Node *tempNode = NULL;
	strcpy(outputName, name);
	strtok(outputName, ".");
	strcat(outputName, am); /* outputName is "name".am */

	/* Declare the input file and output file pointers */
	input = fopen(name, "r");
	if (input == NULL)
	{
		printf("file failed to open.\n");
		printf("please put the file in the same directory of this program.\n");
	}
	output = fopen(outputName, "w+");
	temp_file = fopen(tempFileName, "w+");
	while (fgets(line, 81, input) != NULL)
	{
		if (!inMacro)
		{
			sscanf(line, "%s", temp_str);
			sscanf(line, "%*s %s", correntMacroName);
			if (strcmp(temp_str, macro) == 0 && !isExist(macroList, temp_str))
			{

				inMacro = true;
				continue;
			}
		}
		if (inMacro)
		{
			sscanf(line, "%s", temp_str);
			if (strcmp(temp_str, endmacro) == 0)
			{
				inMacro = false;
				continue;
			}
			else
			{
				macroList = insertToEnd(macroList, correntMacroName, line, "macro", words);
			}
		}
		else
			fputs(line, temp_file);
	}
	rewind(temp_file);
	while (fgets(line, 81, temp_file) != NULL)
	{
		sscanf(line, "%s", temp_str);
		if (isExist(macroList, temp_str))
		{
			tempNode = searchByName(macroList, temp_str);
			while (strcmp(tempNode->name, temp_str) == 0)
			{

				fputs(tempNode->text, output);
				if (tempNode->next == NULL)
					break;
				tempNode = tempNode->next;
			}
		}
		else
			fputs(line, output);
	}
	destroy(macroList);
	fclose(input);
	fclose(output);
	fclose(temp_file);
	remove(tempFileName);
}