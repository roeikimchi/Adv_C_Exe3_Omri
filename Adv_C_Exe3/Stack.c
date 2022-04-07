#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

void rotateStack(Stack* s, int n);
void removeItem(charNode* head);
charNode* addToHead(charNode* head, charNode* toadd);

/***************** Stack ADT Implementation *****************/

void initStack(Stack* s)
{
	s->head = NULL;
}

void destroyStack(Stack* s)
{
	charNode* ptr = s->head; 
	if (s->head == NULL)
		return;
	if (s->head->next == NULL)
	{
		free(s->head);
		s->head = NULL;
		return;
	}
	while (ptr->next != NULL)
	{
		if (ptr->next->next == NULL) {
			charNode* temp = ptr->next;
			ptr->next = NULL;
			free(temp);
			break;
			}
	}
	destroyStack(s);
}

void push(Stack* s, char data)
{
	charNode* newnode; 
	newnode = (charNode*)malloc(sizeof(charNode));
	if (newnode == NULL)
		return;
	newnode->data = data;
	s->head = addToHead(s->head, newnode);
}

char pop(Stack* s)
{

	char tav = s->head->data;
	removeItem(&(s->head));
	return tav;
	
}


int isEmptyStack(const Stack* s)
{
	if (s->head == NULL) {
		return 1;
	}
	return 0; 

}

/*************** Functions using stacks - Implementation/definition **************************/

void flipBetweenHashes(const char* sentence)
{
	int count = 0;
	for (int i = 0; i < strlen(sentence); i++)
	{
		if (sentence[i] == '#')
			count++;
	}
	if (count % 2 == 1)
		count--;
	count /= 2;
	Stack to_REV_sen;
	initStack(&to_REV_sen);
	for (int i = 0; i < ; i++){
		push(&to_REV_sen, sentence[i]);
	}
}


int isPalindrome(Stack* s)
{
	// add your code here
}

void rotateStack(Stack* s, int n)
{
	// add your code here
}

charNode* addToHead(charNode* head, charNode* toadd) {
	toadd->next = head;
	head = toadd;
	return head;
}

void removeItem(charNode **head) {
	charNode* tmp = *head;
	*head = (*head)->next;
	free(tmp);
}