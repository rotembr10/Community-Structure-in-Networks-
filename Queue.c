#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"


/* A linked list (LL) node to store a queue entry */
struct QNode {
	community* com;
	struct QNode* next;
};

/* A utility function to create a new linked list node. */
struct QNode* newNode(community* c)
{
	struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
	temp->com = c;
	temp->next = NULL;
	return temp;
}

/* A utility function to create an empty queue */
struct Queue* createQueue()
{
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->front = q->rear = NULL;
	return q;
}

/* The function to add a community pointer c to q */
void enQueue(struct Queue* q, community* c)
{
	/* Create a new LL node */
	struct QNode* temp = newNode(c);

	/* If queue is empty, then new node is front and rear both */
	if (q->rear == NULL) {
		q->front = q->rear = temp;
		return;
	}

	/* Add the new node at the end of queue and change rear */
	q->rear->next = temp;
	q->rear = temp;
}

/* Function to remove a community pointer from given queue q */
void deQueue(struct Queue* q)
{
	struct QNode* temp;

	/* If queue is empty, return NULL. */
	if (q->front == NULL)
		return;

	/* Store previous front and move front one node ahead */
	temp = q->front;
	q->front = q->front->next;

	/* If front becomes NULL, then change rear also as NULL */
	if (q->front == NULL)
		q->rear = NULL;

	free(temp);
}




