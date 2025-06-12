#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "linkedList.h"

#define BLOCK_ALLOCATION(pointer, type, size) \
	pointer = (type *)malloc(sizeof(type) * (size))

#define BLOCK_RELLOCATION(pointer, type, size, b)                               \
	type *SAVED_NAME_POINTER = (type *)realloc(pointer, sizeof(type) * (size)); \
	if (SAVED_NAME_POINTER != NULL)                                             \
	{                                                                           \
		pointer = SAVED_NAME_POINTER;                                           \
		b = true;                                                               \
	}                                                                           \
	else                                                                        \
	{                                                                           \
		printf("not enough memorry");                                           \
		b = false;                                                              \
	}
/*This class deals with a linked list of labels*/

/*generating node function*/
Node *newNode(char *insertName, char *insertText, char *insertType, char insertWord[256][11])
{
	int i = 0;
	Node *temp = NULL;
	BLOCK_ALLOCATION(temp, Node, 1);
	if (temp != NULL)
	{
		strcpy(temp->name, insertName);
		strcpy(temp->text, insertText);
		strcpy(temp->type, insertType);
		for (; strlen(insertWord[i]); i++)
		{
			strcpy((temp->word)[i], insertWord[i]);
		}
		temp->word[i][0] = '\0';
		temp->next = NULL;
	}
	else
		printf("ERROR - not enogh memory");
	return temp;
}

/*This function puts at the beginning of the list*/
Node *insertToStart(Node *head, char *insertName, char *insertText, char *insertType, char insertWord[256][11])
{
	Node *temp = newNode(insertName, insertText, insertType, insertWord);
	if (head == NULL)
	{
		head = temp;
		return head;
	}
	if (temp != NULL)
	{
		temp->next = head;
		head = temp;
	}
	else
		printf("ERROR - not enogh memory, returning original head");
	return head;
}

/*This function puts at the end of the list*/
Node *insertToEnd(Node *head, char *insertName, char *insertText, char *insertType, char insertWord[256][11])
{
	Node *temp = newNode(insertName, insertText, insertType, insertWord);
	Node *temp_head = head;
	if (head == NULL)
	{
		head = temp;
		return head;
	}
	while (temp_head->next != NULL)
	{

		temp_head = temp_head->next;
	}
	temp->next = NULL;
	temp_head->next = temp;
	return head;
}

/* returning the length of the list */
int length(Node *head)
{
	int num = 0;
	while (head != NULL)
	{
		head = head->next;
		num++;
	}
	return num;
}

/*This function returns the named node (nodeName)*/
Node *searchByName(Node *head, char *nodeName)
{
	while (head != NULL)
	{
		if (strcmp(head->name, nodeName) == 0)
		{
			return head;
		}
		head = head->next;
	}
	return NULL;
}

/*This function checks if a node with the name is found*/
bool isExist(Node *head, char *nodeName)
{
	return searchByName(head, nodeName) != NULL;
}

/*This function puts S in the general list of labels,
it will put in all the labels that have the potential to be ".extern",
 that is, anyone who is not already extern or entry.
 That is, only labels assigned to them in the current encoding file. */
Node *insertALLDataCode(Node *allL, Node *head)
{
	while (head != NULL)
	{
		if (strcmp(head->type, "Extern") != 0 && strcmp(head->type, "Entry") != 0)
		{
			allL = insertToEnd(allL, head->name, head->text, "", head->word);
		}
		head = head->next;
	}
	return allL;
}

/*This function inserts a list at the end of another list,
 so that in each first and second pass we consider the fact that the labels on which
 the extern operation was performed are already in the label list of head*/
Node *insertAllEntrylist(Node *list1, Node *list2)
{
	while (list2 != NULL)
	{
		list1 = insertToEnd(list1, list2->name, list2->text, list2->type, list2->word);

		list2 = list2->next;
	}
	return list1;
}

/*this function free alll the node*/
void destroy(Node *head)
{
	Node *curNode = head;
	Node *nextNode = NULL;
	while (curNode != NULL)
	{
		nextNode = curNode->next;
		free(curNode);
		curNode = nextNode;
	}
}