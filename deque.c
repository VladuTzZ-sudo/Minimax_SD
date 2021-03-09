#include "deque.h"

Node *createDequeNode(int data)
{
	Node *node = malloc(sizeof(Node));

	if (node == NULL)
		return NULL;
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void destroyNode(Node *node)
{
	free(node);
}

Deque *createDeque()
{
	Deque *deque = malloc(sizeof(Deque));

	if (deque == NULL)
		return NULL;
	deque->size = 0;
	deque->head = NULL;
	deque->tail = NULL;
	return deque;
}

void destroyDeque(Deque *deque)
{
	while (!isEmptyDeque(deque)) {
		popFront(deque);
	}
	free(deque);
}

int isEmptyDeque(Deque *deque)
{
	if (deque->head == NULL || deque->tail == NULL)
		return 1;
	return 0;
}

void pushBack(Deque *deque, int data)
{
	Node *node = createDequeNode(data);

	if (node == NULL)
		return;
	if (isEmptyDeque(deque)) {
		deque->head = node;
		deque->tail = node;
	} else {
		deque->tail->next = node;
		node->prev = deque->tail;
		deque->tail = node;
	}
	deque->size++;
}

int popBack(Deque *deque)
{
	Node *node;
	int data;

	if (isEmptyDeque(deque))
		return -1;
	node = deque->tail;
	data = node->data;
	deque->tail = deque->tail->prev;
	if (!isEmptyDeque(deque))
		deque->tail->next = NULL;
	destroyNode(node);
	deque->size--;
	return data;
}

int peekBack(Deque *deque)
{
	if (isEmptyDeque(deque))
		return -1;
	return deque->tail->data;
}

void pushFront(Deque *deque, int data)
{
	Node *node = createDequeNode(data);

	if (node == NULL)
		return;
	if (isEmptyDeque(deque)) {
		deque->head = node;
		deque->tail = node;
	} else {
		deque->head->prev = node;
		node->next = deque->head;
		deque->head = node;
	}
	deque->size++;
}

int popFront(Deque *deque)
{
	Node *node;
	int data;

	if (isEmptyDeque(deque))
		return -1;
	node = deque->head;
	data = node->data;
	deque->head = deque->head->next;
	if (!isEmptyDeque(deque))
		deque->head->prev = NULL;
	destroyNode(node);
	deque->size--;
	return data;
}

int peekFront(Deque *deque)
{
	if (isEmptyDeque(deque))
		return -1;
	return deque->head->data;
}
