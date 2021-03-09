#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "deque.h"

typedef Deque Queue;

Queue *createQueue();

void destroyQueue(Queue *queue);

int isEmptyQueue(Queue *queue);

void enqueue(Queue *queue, int data);

int dequeue(Queue *queue);

int front(Queue *queue);

#endif /* QUEUE_H_INCLUDED */
