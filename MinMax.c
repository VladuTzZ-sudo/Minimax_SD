#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MinMax.h"
#include "queue.h"
#include <limits.h>

MinMaxNode *createMinMaxNode()
{
    MinMaxNode *MinNode;
    MinNode = (MinMaxNode *)malloc(sizeof(MinMaxNode));
    MinNode->child = NULL;
    MinNode->next = NULL;
    MinNode->ok = 0; // este frunza la inceput;
    return MinNode;
}

void recursivitate(MinMaxNode *NouNode, int indice)
{
    if (indice >= 1)
    {
        MinMaxNode *NextNode;
        NextNode = createMinMaxNode();
        NextNode->value = -2;
        NouNode->next = NextNode;
        recursivitate(NextNode, indice - 1);
    }
}

// contor = nr de copii
// value = in caz ca e frunza contine indicele,daca nu va contine numarul de copii
void insertMinMaxNode(MinMaxNode *MinNode, Queue *value, Queue *frunza)
{
    MinMaxNode *NouNode;
    int ok;
    if (MinNode == NULL)
    {
        return;
    }
    if (isEmptyQueue(value) == 1)
    {
        return;
    }

    if (MinNode->child == NULL)
    {
        if (MinNode->ok == 0)
        {
            MinNode->value = dequeue(value);
            MinNode->ok = dequeue(frunza);
            if (MinNode->ok == 1)
            {
                NouNode = createMinMaxNode();
                NouNode->value = -1;
                MinNode->child = NouNode;
                recursivitate(NouNode, MinNode->value - 1);
            }
        }
        insertMinMaxNode(MinNode->next, value, frunza);
    }
    else
    {
        if (isEmptyQueue(value) == 1)
        {
            return;
        }
        ok = 0;
        insertMinMaxNode(MinNode->child, value, frunza);
        insertMinMaxNode(MinNode->next, value, frunza);
    }
    if (MinNode->next == NULL)
    {
        return;
    }
}

void printGivenLevel(MinMaxNode *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->value);
    if (level >= 1)
    {
        printGivenLevel(root->child, level - 1);
        printGivenLevel(root->next, level);
    }
}

void printMinMaxNode(MinMaxNode *MinNode, int h)
{
    int i;
    for (i = 1; i <= h; i++)
    {
        printGivenLevel(MinNode, i);
        printf("\n");
    }
}

int FindMin(MinMaxNode *MinNode, int min)
{
    if (MinNode != NULL)
    {
        if (MinNode->value < min)
        {
            min = FindMin(MinNode->next, MinNode->value);
        }
        min = FindMin(MinNode->next, min);
    }
    return min;
}

int FindMax(MinMaxNode *MaxNode, int max)
{
    if (MaxNode != NULL)
    {
        if (MaxNode->value > max)
        {
            max = FindMax(MaxNode->next, MaxNode->value);
        }
        max = FindMax(MaxNode->next, max);
    }
    return max;
}

void AlgoritmLevel(MinMaxNode *root, int level, int ok)
{
    int max;
    int min;
    if (root == NULL)
        return;
    if (level == 1)
    {
        if (ok % 2 == 0)
        {
            if (root->child != NULL)
            {
                min = root->child->value;
                min = FindMin(root->child, min);
            }
            else
            {
                min = root->value;
            }
            root->value = min;
        }
        if (ok % 2 == 1)
        {
            if (root->child != NULL)
            {
                max = root->child->value;
                max = FindMax(root->child, max);
            }
            else
            {
                max = root->value;
            }
            root->value = max;
        }
    }
    if (level >= 1)
    {
        AlgoritmLevel(root->child, level - 1, ok);
        AlgoritmLevel(root->next, level, ok);
    }
}

void Algoritm(MinMaxNode *MinNode, int h)
{
    int i;
    int ok;
    if (h % 2 == 0)
    {
        ok = 1;
    }
    else
    {
        ok = 0;
    }
    for (i = h - 1; i >= 1; i--)
    {
        AlgoritmLevel(MinNode, i, ok);
        ok++;
    }
}

void printFinal(MinMaxNode *root, int level, FILE **tu)
{
    if (root == NULL)
        return;
    int i;
    for (i = 1; i <= level; i++)
    {
        fprintf((*tu), "\t");
    }
    fprintf((*tu), "%d\n", root->value);
    printFinal(root->child, level + 1, tu);
    printFinal(root->next, level, tu);
}

void freeMulticai(MinMaxNode *root)
{
    if (root != NULL)
    {
        freeMulticai(root->next);
        freeMulticai(root->child);
        free(root);
    }
}

void AlphaBetaLevel(MinMaxNode *root, int ok, int alpha, int beta)
{
    int max;
    int min;
    if (root == NULL)
        return;

    AlphaBetaLevel(root->child, ok + 1, alpha, beta);
    if (ok % 2 == 0)
    {
        if (alpha == -4000 && beta == 4000)
        {
            if (root->child != NULL)
            {
                min = root->child->value;
                min = FindMin(root->child, min);
            }
            else
            {
                min = root->value;
            }
            root->value = min;
            beta = min;
            AlphaBetaLevel(root->next, ok, beta, 4000);
        }
        else
        {
            if (root->child != NULL)
            {
                BetaEliminare(root->child, alpha);
                min = root->child->value;
                min = FindMin(root->child, min);
                root->value = min;
            }
            int bet;
            bet = beta;
            if (root->value >= alpha)
            {
                beta = root->value;
                AlphaBetaLevel(root->next, ok, beta, bet);
            }
            else
            {
                AlphaBetaLevel(root->next, ok, alpha, bet);
            }
        }
    }
    if (ok % 2 == 1)
    {
        if (alpha == -4000 && beta == 4000)
        {
            if (root->child != NULL)
            {
                max = root->child->value;
                max = FindMax(root->child, max);
            }
            else
            {
                max = root->value;
            }
            root->value = max;
            alpha = max;
            AlphaBetaLevel(root->next, ok, -4000, alpha);
        }
        else
        {
            if (root->child != NULL)
            {
                AlphaEliminare(root->child, beta);
                max = root->child->value;
                max = FindMax(root->child, max);
                root->value = max;
            }
            int alpha2;
            alpha2 = alpha;

            if (root->value <= beta)
            {
                alpha = root->value;
                AlphaBetaLevel(root->next, ok, alpha2, alpha);
            }
            else
            {
                AlphaBetaLevel(root->next, ok, alpha2, beta);
            }
        }
    }
}

void AlphaBeta(MinMaxNode *MinNode)
{
    int alpha, beta;
    alpha = -4000;
    beta = 4000;
    AlphaBetaLevel(MinNode, 1, alpha, beta);
}

void AlphaEliminare(MinMaxNode *root, int alpha)
{
    if (root == NULL)
        return;
    if (root->value >= alpha)
    {
        if (root->next != NULL)
        {
            freeMulticai(root->next);
        }
        root->next = NULL;
    }
    AlphaEliminare(root->next, alpha);
}

void BetaEliminare(MinMaxNode *root, int beta)
{
    if (root == NULL)
        return;
    if (root->value <= beta)
    {
        if (root->next != NULL)
        {
            freeMulticai(root->next);
        }
        root->next = NULL;
    }
    BetaEliminare(root->next, beta);
}