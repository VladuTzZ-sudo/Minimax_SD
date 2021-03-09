#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

typedef struct MinMaxNode
{
    int ok;
    int value;
    struct MinMaxNode *child;
    struct MinMaxNode *next;
} MinMaxNode;

MinMaxNode *createMinMaxNode();

void insertMinMaxNode(MinMaxNode *MinNode, Queue *coada, Queue *frunza);

void recursivitate(MinMaxNode *NouNode, int indice);

void printGivenLevel(MinMaxNode *root, int level);

void printMinMaxNode(MinMaxNode *MinNode, int h);

int FindMin(MinMaxNode *MinNode, int min);

int FindMax(MinMaxNode *MaxNode, int max);

void AlgoritmLevel(MinMaxNode *root, int level, int ok);

void Algoritm(MinMaxNode *MinNode, int h);

void printFinal(MinMaxNode *root, int h, FILE **tu);

void freeMulticai(MinMaxNode *root);

void AlphaBetaLevel(MinMaxNode *root, int ok, int alpha, int beta);

void AlphaBeta(MinMaxNode *MinNode);

void AlphaEliminare(MinMaxNode *root, int alpha);

void BetaEliminare(MinMaxNode *root, int beta);

void parcurgere(MinMaxNode *root);