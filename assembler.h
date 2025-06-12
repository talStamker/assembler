#ifndef assembler_h
#define assembler_h
#include "linkedList.h"
/*this header Shows the main functions of the project which,
when put together, completes the entire assembler process.
The classes that use this header:
preAssembler.c
directiveSentence.c
teachingSentence.c
firstRun.c
encodeLabels.c
secondRun.c
main.c*/

/*pre assembler*/
void makeAmFile(char *name);

/*first run*/
Node *insertAllEntLabel(Node *head);
Node *isDataStorageDirective(Node *head, char *line, char *firstWord, bool isExistLabel, int *numOfWord, int numOfline, int DC);
Node *insertExternLabel(Node *head, char words[256][11], char *line, int numOfLines, char *labelForExtern);
Node *updateData(Node *head, char words[256][11], int *size, int IC);
int isCorrectAction(char words[256][11], char *line, char *command_type, int numOfLine, int IC);
Node *fRun(char *name, Node *head, char words[256][11], int *numOfWord, int *DC);

/*second run*/
int encodeLabel(Node *head, char words[256][11], char *line, int numofline, int IC);
Node *searchFromAllLabel(char *name);
void destroyAllLabel();
void destroyEnt();
Node *sRun(Node *head, char words[256][11], char *name, int dc);
#endif