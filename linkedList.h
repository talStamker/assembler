#ifndef linked_lost_h
#define linked_lost_h
#include <stdbool.h>
/*This header has useful functions throughout the project.
The classes that use this library:
linkedList.c
preAssembler.c
directiveSentence.c
firstRun.c
encodeLabels.c
secondRun.c
main.c*/
struct Node
{
	char name[81];		/*name label*/
	char text[81];		/*address label*/
	char type[81];		/*type of label(Extern\Data..)*/
	char word[256][11]; /*Coding of the sentence of the prescriptive*/
	struct Node *next;
};
typedef struct Node Node;
Node *newNode(char *insertName, char *insertText, char *insertType, char insertWord[256][11]);
Node *insertToStart(Node *head, char *insertName, char *insertText, char *insertType, char insertWord[256][11]);
Node *insertToEnd(Node *head, char *insertName, char *insertText, char *insertType, char insertWord[256][11]);
int length(Node *head);
Node *searchByName(Node *head, char *nodeName);
void destroy(Node *head);
bool isExist(Node *head, char *nodeName);
Node *insertAllEntrylist(Node *list1, Node *list2);
Node *insertALLDataCode(Node *list1, Node *list2);
#endif