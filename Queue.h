#include "community.h"

#ifndef QUEUE_H_
#define QUEUE_H_


/* The queue, front stores the front node of LL and rear stores the
   last node of LL */
typedef struct Queue {
    struct QNode *front, *rear;
}Queue;

typedef struct QNode {
    community* com;
    struct QNode* next;
} QNode;


/* A utility function to create an empty queue */
Queue* createQueue();

/* The function to add a community pointer c to q */
void enQueue(Queue* q, community* c);

/* Function to remove a community pointer from given queue q */
void deQueue(Queue* q);


#endif /* QUEUE_H_ */
