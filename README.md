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
###linkedList.c
This class deals with a linked list of labels
#### Functions:
##### Node *newNode(char *insertName, char *insertText, char *insertType, char insertWord[256][11])
This function generate node function
##### Node *insertToStart(Node *head, char *insertName, char *insertText, char *insertType, char insertWord[256][11])
This function puts at the beginning of the list
##### Node *insertToEnd(Node *head, char *insertName, char *insertText, char *insertType, char insertWord[256][11])
This function puts at the end of the list
##### int length(Node *head)
This function returning the length of the list 
##### Node *searchByName(Node *head, char *nodeName)
This function returns the named node (nodeName)
##### bool isExist(Node *head, char *nodeName)
This function checks if a node with the name is found
##### Node *insertALLDataCode(Node *allL, Node *head)
This function puts S in the general list of labels,
it will put in all the labels that have the potential to be ".extern",
 that is, anyone who is not already extern or entry.
 That is, only labels assigned to them in the current encoding file. 
##### Node *insertAllEntrylist(Node *list1, Node *list2)
This function inserts a list at the end of another list,
 so that in each first and second pass we consider the fact that the labels on which
 the extern operation was performed are already in the label list of head
##### void destroy(Node *head)
This function free alll the node
### teachingSentence.c
This department handles action sentences,
 checks whether they are correct and to what extent, and codes them
#### Functions
##### int encodeAction(int numOfOprand, char words[256][11], char *oprand1, char *oprand2, int IC, bool immediateS, bool immediateD, bool labelS, bool labelD, bool registerS, bool registerD, bool accessToListS, bool accessToListD)
This function encodes simple operations with 2 operands or with 1 operand.
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
##### int isCorrectAction(char words[256][11], char *line, char *command_type, int numOfLine, int IC)
This function checks the correctness of instruction sentences,
 and encodes them if they are correct
 words-array of words in first run.
 line- line in am file
 commandtype-action type
 num of line- num of corrent line
 ic-instruction conter 
### utils.c
#### Functions:
##### bool isANum(char *st)
This function checks that a number is indeed correct,
and takes into account that it can start with a plus or minus
##### bool isARegister(char *name)
This function checks that the received register is valid
##### bool isALabel(char *label)
This function checks that the label is syntactically correct
##### bool isImmediate(char *name)
This function checks whether the address is immediate
##### bool isAccessToList(char *name)
This function checks that it is a label and an index 
##### bool isAComment(char *name)
This function checks that it is a comment sentence
##### bool isADataStorage(char *data_storage)
This function checks
whether the string it received is the instruction to store data
##### int getOpcode(char *name)
This function checks whether the string received is an instruction
and if so returns the opcode of the instruction
##### bool isCommaAtTheBeginning(char *directive)
This function checks if there is a comma at the beginning.
##### bool isCommaAtTheEnd(char *directive)
This function checks if there is a comma at the end.
##### bool space(char st[81])
This function checks whether the entire string is only spaces.
##### bool isNonOperand(int opcode)
This function checks whether the command with this opcode has no operands.
##### bool isOneOperand(int opcode)
This function checks whether the command with this opcode has one operands
##### bool isTwoOperand(int opcode)
This function checks whether the command with this opcode has two operands
### preAssembler.c 
This file pass the source file and look for macro lines and save them in file source.am
#### Functions:
##### void makeAmFile(char *name)
This function accepts a source file and interprets the macro in the source file
### firstRun.c
#### Functions:
##### Node *fRun(char *name, Node *head, char words[256][11], int *numOfWord, int *DC)
This function performs a complete first pass according to the skeletal algorithm that appeared in the file.
It will update everything that can be translated in the first pass,
i.e. coded instruction sentences, coded instruction sentences without label addresses,
and the full list of words will be updated in words
variable:
name- am file name
head- list of label
words- array of words
dc-Data-Counter updated in first run.c
### secondRun.c
#### Functions:
##### Node *insertAllEntLabel(Node *head)
This function insert all entry lable to head
##### bool isCorrectEntry(Node *head, char *line, Node **entryNode, int numOfLine)
This function chaeck if entry sentence is correct
variable:
head-list of label of source file
line- entry line
entryNode-pointer to *node if the entry line will be correct it will cut the node thar need to entry
num of line- cuurrent line
##### void markEntry(Node *entryNode)
This function mark all the label in head that need to extern and update entlabel for the other files
##### void writeObFile(char words[256][11], char *name, int dc, int ic)
This function receives a list of words and writes them to a file of type ob
 according to their value in base32
  words-The label list
name-am file name
  ic-instruction conter
dc-Data counter
##### void writeEntFile(Node *head, char *name)
A function that writes all labels of type Entry to ent file
head- list of label
name- am name file
##### void writeExtFie(Node *head, char *name)
A function that writes all labels of type Extern to ext file
head- list of label
name- am name file
##### bool isExistInSourceFile(Node *head, char *line, int numOfLine)
This function check if the label that in source file write ti extern it is defined in source file
##### Node *sRun(Node *head, char words[256][11], char *name, int dc)
This function performs an algorithm according to the shield algorithm of the second pass
head- list of labels
words- the entier words
name - am file
dc-Data-Counter updated in first run.c
##### void destroyEnt()
This function destroy entLabel
##### Node *searchFromAllLabel(char *name)
This function return the node that have this name
##### void destroyAllLabel()
This function destroy the labels in allLabel
### main.c
#### Functions:
void clean(char words[256][11], int numOfWords)
This function clean words
##### int main(int argc, char *argv[])
This function is the main function that pre Assembler run and first run and second run
