#include "community.h"

#ifndef QUEUE_H_
#define QUEUE_H_


/* The queue, front stores the front node of LL and rear stores the
   last node of LL */
struct Queue {
	struct QNode *front, *rear;
};


/* A utility function to create an empty queue */
struct Queue* createQueue();

/* The function to add a community pointer c to q */
void enQueue(struct Queue* q, community* c);

/* Function to remove a community pointer from given queue q */
void deQueue(struct Queue* q);


#endif /* QUEUE_H_ */
