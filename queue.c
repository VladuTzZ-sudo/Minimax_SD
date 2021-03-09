#include "queue.h"

Queue *createQueue()
{
	return createDeque();
}

void destroyQueue(Queue *queue)
{
	destroyDeque(queue);
}

int isEmptyQueue(Queue *queue)
{
	return isEmptyDeque(queue);
}

void enqueue(Queue *queue, int data)
{
	pushBack(queue, data);
}

int dequeue(Queue *queue)
{
	return popFront(queue);
}

int front(Queue *queue)
{
	return front(queue);
}
