#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

typedef struct BonusNode
{
    int ok;
    int value;
    int *indici;
    struct BonusNode *child;
    struct BonusNode *next;
} BonusNode;

BonusNode *createBonusNode(int players);

void recursivitateBonus(BonusNode *NewNode, int indice, int players);

void insertBonusNode(BonusNode *BonNode, Queue *value, Queue *frunza, int players);

void printBonus(BonusNode *root, int level, FILE **tu, int players);

void BonusLevel(BonusNode *root, int level, int ok, int players);

void AlgoBonus(BonusNode *MinNode, int h, int players);

int FindBonMin(BonusNode *BonNode, int min, int indice, int *pozmin);

int FindBonMax(BonusNode *BonNode, int max, int indice, int *pozmax);

int recursivmaxim(BonusNode *MaxNode, int pozmax, int indice);

int recursivminim(BonusNode *MinNode, int pozmin, int indice);

void freeBonus(BonusNode *root);
