#ifndef utils_h
#define utils_h
#include <stdbool.h>

/*This library has useful functions throughout the project.
The classes that use this library:
utils.c
directiveSentence.c
teachingSentence.c
firstRun.c
encodeLabels.c
secondRun.c*/
bool isANum(char *st);
bool isARegister(char *name);
bool isALabel(char *label);
bool isImmediate(char *name);
bool isAccessToList(char *name);
bool isAComment(char *name);
bool isADataStorage(char *data_storage);
int getOpcode(char *name);
bool isCommaAtTheBeginning(char *directive);
bool isCommaAtTheEnd(char *directive);
bool space(char st[81]);
bool isNonOperand(int opcode);
bool isOneOperand(int opcode);
bool isTwoOperand(int opcode);
#endif