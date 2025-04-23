# Assembler
## Download the requirements file for the task can be downloaded here:
https://github.com/talStamker/assembler/releases/download/v1.0/default.pdf
In this file in maman 14 (pages 27 to 56) you will find the requirements for the task.
## How to run?
Enter terminal in the correct location and write this:
make all
./assembler [name of the as file that you want check the as file is the Assembler command lines for example you can see source.as]
## Explanation of the files:
### castingToBinnary.c
This file converts some variable types to their binary form or in base 32,
 to make coding easier. His library castingToBinnary.h
#### Functions:
##### void numTo4Bits(int num, char *ans)
This function converts a number to its binary form in 4 bits.
variables:
int num-The number we want to convert.
char *ans-The number in its binary form inside a string
##### void numTo8Bits(char *num, char *ans)
/*This function converts a number to its binary form in 8 bits.
This function works in the 2's complement method(Handles negative numbers).
variables:
char num-The number we want to convert inside string like "1".
char *ans-The number in its binary form inside a string.*/
##### void numTo10Bits(char *num, char *ans)
This function converts a number to its binary form in 10 bits.
This function works in the 2's complement method(Handles negative numbers).
variables:
char num-The number we want to convert inside string like "1".
char *ans-The number in its binary form inside a string.
##### void registerTo4Bits(char *r, char *ans)
*This function converts a register to its binary form in 4 bits.
variables:
char num-The number we want to convert inside string like "1".
char *ans-The number in its binary form inside a string.*/
##### void castingNumto32Bit(int num, char *ans)
This function converts a number to its number in base 32.
The function does a conversion in the array value:
char base32Digits[100]={'!','@','#','$','%','^',
'&','*','<','>','a','b','c','d','e','f','g','h','i','j',
'k','l','m','n','o','p','q','r','s','t','u','v'};
variables:
cha num-The number we want to convert inside a string like "1".
char *ans-The number in bace 32 inside a string.
### assembler.h
this header Shows the main functions of the project which,
when put together, completes the entire assembler process.
The classes that use this header:
preAssembler.c
directiveSentence.c
teachingSentence.c
firstRun.c
encodeLabels.c
secondRun.c
main.c
#### Functions:
##### pre assembler
void makeAmFile(char *name);
##### first run
Node *insertAllEntLabel(Node *head);
Node *isDataStorageDirective(Node *head, char *line, char *firstWord, bool isExistLabel, int *numOfWord, int numOfline, int DC);
Node *insertExternLabel(Node *head, char words[256][11], char *line, int numOfLines, char *labelForExtern);
Node *updateData(Node *head, char words[256][11], int *size, int IC);
int isCorrectAction(char words[256][11], char *line, char *command_type, int numOfLine, int IC);
Node *fRun(char *name, Node *head, char words[256][11], int *numOfWord, int *DC);
#### second run
int encodeLabel(Node *head, char words[256][11], char *line, int numofline, int IC);
Node *searchFromAllLabel(char *name);
void destroyAllLabel();
void destroyEnt();
Node *sRun(Node *head, char words[256][11], char *name, int dc);
### utils.h
This library has useful functions throughout the project.
The classes that use this library:
utils.c
directiveSentence.c
teachingSentence.c
firstRun.c
encodeLabels.c
secondRun.c
#### Functions:
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
### linkedList.h
This header has useful functions throughout the project.
The classes that use this library:
linkedList.c
preAssembler.c
directiveSentence.c
firstRun.c
encodeLabels.c
secondRun.c
main.c
struct Node
{
	char name[81];		/*name label*/
	char text[81];		/*address label*/
	char type[81];		/*type of label(Extern\Data..)*/
	char word[256][11]; /*Coding of the sentence of the prescriptive*/
	struct Node *next;
};
typedef struct Node Node;
#### Functions:
Node *newNode(char *insertName, char *insertText, char *insertType, char insertWord[256][11]);
Node *insertToStart(Node *head, char *insertName, char *insertText, char *insertType, char insertWord[256][11]);
Node *insertToEnd(Node *head, char *insertName, char *insertText, char *insertType, char insertWord[256][11]);
int length(Node *head);
Node *searchByName(Node *head, char *nodeName);
void destroy(Node *head);
bool isExist(Node *head, char *nodeName);
Node *insertAllEntrylist(Node *list1, Node *list2);
Node *insertALLDataCode(Node *list1, Node *list2);
### directiveSentence.c
This department deals with directive sentences in assembly language.
All the handling of the encoding directive and counting places in the memory is done here
#### Functions:
##### Node *isCorrectData(Node *head, char words[256][11], char line[81], char firstWord[81], int *numOfWord, int numOfLine, int DC)
This function checks whether the sentence of type DATA is correct.
 If so, code it into an array of words.
Inserts into the linked list that preserves its encoding.
variabel:
 head-The linked list into which all symbols go
Words-The list of words to be assigned to the directive sentence.
line- line in the am file
firstWord- The first word in the line
num of word- The number of words required for this prompt.
num of line- Line number in the am file
Data-Counter updated in first run.c
##### Node *updateData(Node *head, char words[256][11], int *size, int IC)
This function updates all style symbols given the IC,
 and updates their encoding in the words array
 variable:
 head-linked list
 words-all the words in first run
 size- the size of words that ful in first run
 ic-instruction conter 
##### Node *isCorrectString(Node *head, char words[256][11], char *st, char firstWord[81], int *numOfWord, int numOfLine, int DC)
This function checks whether the sentence of type STRING/STRUCT is correct.
 If so, code it into an array of words.
Inserts into the linked list that preserves its encoding.
variabel:
head-The linked list into which all symbols go.
Words-The list of words to be assigned to the directive sentence.
st- The string that needs to be coded.
firstWord- The first word in the line in am file
num of word- The number of words required for this prompt.
num of line- Line number in the am file.
DC-Data Counter updated in first run.c
##### Node *isCorrectStruct(Node *head, char words[256][11], char *line, char *firstWord, int *numOfWord, int numOfLine, int DC)
This function checks whether the sentence of type STRUCT is correct.
 If so, code it into an array of words.
Inserts into the linked list that preserves its encoding.
variabel:
head-The linked list into which all symbols go.
Words-The list of words to be assigned to the directive sentence.
line- line in the am file.
firstWord- The first word in the line in am file
num of word- The number of words required for this prompt.
num of line- Line number in the am file.
DC-Data Counter updated in first run.c
##### Node *insertExternLabel(Node *head, char words[256][11], char *line, int numOfLines, char *labelForExtern)
This function inserts all external type symbols into the symbol table.
variabel:
head-The linked list into which all symbols go.
Words-The list of words to be assigned to the directive sentence.
line- line in the am file.
num of line- Line number in the am file.
labelForExtern- the label that we need to insert
##### Node *isDataStorageDirective(Node *head, char *line, char *firstWord, bool isExistLabel, int *numOfWord, int numOfline, int DC)
This function handles all instruction sentences of any type,
encodes them and checks how many words are required to encode them
variabel:
head-The linked list into which all symbols go.
line- line in the am file.
firstWord- The first word in the line in am file
isExistLabel-Notifies if there is a label at the beginning of the line.
num of word- The number of words required for this prompt.
num of line- Line number in the am file.
Data-Counter updated in first run.c*
### encodeLables.c
#### Functions:
##### int counterAndUpdateWord(Node *head, char words[256][11], char *oprand, int i, int numofline)
This function checks that the label has indeed been defined,
 and updates its address in the appropriate place
 head-list of label
 words-The label list
 oprand-label
 i- the corrent conter
 num of line-the corrent line in am file
##### int encodeLabel(Node *head, char words[256][11], char *line, int numofline, int IC)
This function encodes labels in the appropriate place.
head-list of label
 words-The label list
 line- the corrent line
  ic-instruction conter
 num of line-the corrent line in am file
 
### preAssembler.c 
This file pass the source file and look for macro lines and save them in file source.am
#### Functions:
##### void makeAmFile(char *name)
This function accepts a source file and interprets the macro in the source file
