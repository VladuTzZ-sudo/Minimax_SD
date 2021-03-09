#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//ok == 0 , deci nu este frunza.
typedef struct ConectNode
{
    int **M;
    struct ConectNode *child;
    struct ConectNode *next;
} ConectNode;

int castigator(int **M, int n, int m);

ConectNode *createNode();

int **generate2Matrix(int **J, int n, int m, int curent);

int ***generateMatrix(int **J, int n, int m, int curent);

void insertNode(ConectNode *Node, int n, int m, int t, int curent, FILE *f);

void printNode(ConectNode *Node, int n, int m, int tab, FILE *f);

void freeTree(ConectNode *Node, int n, int m);