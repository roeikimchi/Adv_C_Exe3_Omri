#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printQueue(Queue* q);
void addToHeadQ(Queue* q, unsigned int data);
void addToMiddleQ(intNode* ptr, unsigned int data);

/***************** Queue ADT Implementation *****************/

void initQueue(Queue* q)
{
	q->head = NULL;
	q->tail = NULL;
}

void destroyQueue(Queue* q)
{
	intNode* ptr = q->head;
	if (q->head == NULL && q->tail == NULL)//case queue is empty
		return;
	if (q->head->next == NULL)//free the last item
	{
		free(q->head);
		q->head = q->tail = NULL;
		return;
	}
	while (ptr->next != NULL)//free all items except the last one
	{
		if (ptr->next->next == NULL)
		{
			intNode* temp = ptr->next;
			ptr->next = NULL;
			free(temp);
			break;
		}
		ptr = ptr->next;
	}
	destroyQueue(q);
}

void enqueue(Queue* q, unsigned int data)
{
	intNode* newNode = (intNode*)malloc(sizeof(intNode));
	if (newNode == NULL) {
		printf("memory allocation problem\n");
		return;
	}
	newNode->data = data;
	newNode->next = NULL;

	if (isEmptyQueue(q))//case queue is empty 
	{
		q->head = newNode;
		q->tail = newNode;
	}
	else//case queue isn't empty
	{
		q->tail->next = newNode;
		q->tail = newNode;
	}
}

unsigned int dequeue(Queue* q)
{
	int temp = q->head->data;
	intNode* p = q->head;
	q->head = q->head->next;

	if (q->head == NULL)//case there is only 1 item in queue
		q->tail = NULL;
	free(p);
	return temp;
}

int isEmptyQueue(const Queue* q)
{
	if (q->head == NULL && q->tail == NULL)
		return 1;
	else return 0;
}

/***************** Functions using Queues - Implementation/definition **************************/

void rotateQueue(Queue* q)
{
	if (isEmptyQueue(q) == 1)//case queue is empty
		return;
	intNode* temp;
	intNode* ptr = q->head;
	while (ptr->next->next != NULL)//puts the ptr on last item
	{
		ptr = ptr->next;
	}
	temp = q->tail;
	ptr->next = NULL;
	temp->next = q->head;
	q->head = temp;
}

void cutAndReplace(Queue* q)
{
	if (isEmptyQueue(q) == 1)//case queue is empty
		return;
	unsigned int counter = 0, sum = 0;
	Queue temp_q;
	initQueue(&temp_q);
	intNode* ptr = q->head;
	while (ptr != NULL)//count how many items are in list 
	{
		counter++;
		ptr = ptr->next;
	}
	if (counter % 2 != 0)//if there is odd num of items
	{
		ptr = q->head;
		while (ptr != NULL)//sum up all items in list
		{
			sum += ptr->data;
			ptr = ptr->next;
		}
		sum /= counter;
		enqueue(q, sum);//add new item - average
		counter++;
	}
	ptr = q->head;
	counter /= 2;
	for (int i = 0; i < counter; i++)//puts the ptr on the middle 
	{
		ptr = ptr->next;
	}
	while (ptr != NULL)//puts the items from middle to end in temp queue
	{
		enqueue(&temp_q, ptr->data);
		ptr = ptr->next;
	}
	for (int i = 0; i < counter; i++)//puts the rest of the items in temp queue
	{
		enqueue(&temp_q, dequeue(q));
	}
	destroyQueue(q);//empty the original queue
	while (temp_q.head != NULL)//copy the temp queue to the original queue
	{
		enqueue(q, dequeue(&temp_q));
	}
	destroyQueue(&temp_q);//free the temp queue
}

void sortKidsFirst(Queue* q)
{
	if (isEmptyQueue(q) == 1)//case queue is empty
		return;
	Queue temp_q;
	initQueue(&temp_q);
	enqueue(&temp_q, dequeue(q));
	unsigned int num;
	intNode* ptr = &temp_q.head;
	ptr = ptr->next;
	while (q->head != NULL)
	{
		num = dequeue(q);
		if (num > temp_q.tail->data)//case node needs to be the last at queue
		{
			enqueue(&temp_q, num);
			continue;
		}
		if (num < temp_q.head->data)//case node needs to be the first at queue
		{
			addToHeadQ(&temp_q, num);
			continue;
		}
		if (num >= temp_q.head->data && num < temp_q.tail->data)//case node needs to be at middle
		{
			ptr = temp_q.head;
			while (ptr != NULL)
			{
				if (num >= ptr->data && num <= ptr->next->data)
					break;
				ptr = ptr->next;
			}
			addToMiddleQ(ptr, num);
		}
	}
	destroyQueue(q);//empty the original queue
	while (temp_q.head != NULL)//copy the temp queue to the original queue
	{
		enqueue(q, dequeue(&temp_q));
	}
	destroyQueue(&temp_q);//free the temp queue
}

void printQueue(Queue* q)
{
	if (isEmptyQueue(q) == 1)//case queue is empty 
	{
		printf("\Queue is empty!\n");
		return;
	}
	intNode* ptr = q->head;
	printf("\n");
	while (ptr->next != NULL)
	{
		printf("%d <- ", ptr->data);
		ptr = ptr->next;
	}
	printf("%d\n", ptr->data);
}

void addToHeadQ(Queue* q, unsigned int data)//puts new node at head of queue
{
	intNode* newNode = (intNode*)malloc(sizeof(intNode));
	if (newNode == NULL) 
	{
		printf("memory allocation problem\n");
		return;
	}
	newNode->data = data;
	newNode->next = q->head;

	if (isEmptyQueue(q))//case queue is empty
	{
		q->head = newNode;
		q->tail = newNode;
	}
	else//case queue isn't empty
	{
		q->head = newNode;
	}
}

void addToMiddleQ(intNode* ptr, unsigned int data)//puts new node at list between two other nodes
{
	intNode* newNode = (intNode*)malloc(sizeof(intNode));
	if (newNode == NULL) {
		printf("memory allocation problem\n");
		return;
	}
	newNode->data = data;
	newNode->next = ptr->next;
	intNode* temp = ptr->next;
	ptr->next = newNode;
	
}