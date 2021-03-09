#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
	struct node *prev;
} Node;

typedef struct {
	long size;
	Node *head;
	Node *tail;
} Deque;

Node *createDequeNode(int data);

void destroyNode(Node *node);

Deque *createDeque();

void destroyDeque(Deque *deque);

int isEmptyDeque(Deque *deque);

void pushBack(Deque *deque, int data);

int popBack(Deque *deque);

int peekBack(Deque *deque);

void pushFront(Deque *deque, int data);

int popFront(Deque *deque);

int peekFront(Deque *deque);

#endif /* DEQUE_H_INCLUDED */
