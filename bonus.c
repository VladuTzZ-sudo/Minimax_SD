#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bonus.h"
#include "queue.h"

BonusNode *createBonusNode(int players)
{
    BonusNode *BonNode;
    BonNode = (BonusNode *)malloc(sizeof(BonusNode));
    BonNode->child = NULL;
    BonNode->next = NULL;
    BonNode->ok = 0; // este frunza la inceput;
    BonNode->indici = (int *)calloc(players, sizeof(int));
    return BonNode;
}

void recursivitateBonus(BonusNode *NewNode, int indice, int players)
{
    if (indice >= 1)
    {
        BonusNode *NextNode;
        NextNode = createBonusNode(players);
        NextNode->value = -2;
        NewNode->next = NextNode;
        recursivitateBonus(NextNode, indice - 1, players);
    }
}

void insertBonusNode(BonusNode *BonNode, Queue *value, Queue *frunza, int players)
{
    BonusNode *NewNode;
    int ok;
    int i;
    if (BonNode == NULL)
    {
        return;
    }
    if (isEmptyQueue(value) == 1)
    {
        return;
    }

    if (BonNode->child == NULL)
    {
        if (BonNode->ok == 0)
        {
            BonNode->ok = dequeue(frunza);
            if (BonNode->ok == 1)
            {
                BonNode->value = dequeue(value);
            }
            else
            {
                for (i = 0; i < players; i++)
                {
                    BonNode->indici[i] = dequeue(value);
                }
            }
            if (BonNode->ok == 1)
            {
                NewNode = createBonusNode(players);
                NewNode->value = -1;
                BonNode->child = NewNode;
                recursivitateBonus(NewNode, BonNode->value - 1, players);
            }
        }
        insertBonusNode(BonNode->next, value, frunza, players);
    }
    else
    {
        if (isEmptyQueue(value) == 1)
        {
            return;
        }
        ok = 0;
        insertBonusNode(BonNode->child, value, frunza, players);
        insertBonusNode(BonNode->next, value, frunza, players);
    }
    if (BonNode->next == NULL)
    {
        return;
    }
}

void printBonus(BonusNode *root, int level, FILE **tu, int players)
{
    if (root == NULL)
        return;
    int i;
    for (i = 1; i <= level; i++)
    {
        fprintf((*tu), "\t");
    }
    fprintf(*(tu), "[");
    for (i = 0; i < players - 1; i++)
    {
        fprintf((*tu), "%d,", root->indici[i]);
    }
    fprintf((*tu), "%d", root->indici[i]);
    fprintf(*(tu), "]\n");

    printBonus(root->child, level + 1, tu, players);
    printBonus(root->next, level, tu, players);
}

int FindBonMin(BonusNode *MinNode, int min, int indice, int *pozmin)
{
    if (MinNode != NULL)
    {
        if (MinNode->indici[0] < min)
        {
            *pozmin = indice;
            min = FindBonMin(MinNode->next, MinNode->indici[0], indice + 1, pozmin);
        }
        min = FindBonMin(MinNode->next, min, indice + 1, pozmin);
    }
    return min;
}

int FindBonMax(BonusNode *MaxNode, int max, int indice, int *pozmax)
{
    if (MaxNode != NULL)
    {
        if (MaxNode->indici[0] > max)
        {
            *pozmax = indice;
            max = FindBonMax(MaxNode->next, MaxNode->indici[0], indice + 1, pozmax);
        }
        max = FindBonMax(MaxNode->next, max, indice + 1, pozmax);
    }
    return max;
}

int recursivmaxim(BonusNode *MaxNode, int pozmax, int indice)
{
    if (pozmax == 0)
    {
        return MaxNode->indici[indice];
    }
    recursivmaxim(MaxNode->next, pozmax - 1, indice);
}

int recursivminim(BonusNode *MinNode, int pozmin, int indice)
{
    if (pozmin == 0)
    {
        return MinNode->indici[indice];
    }
    recursivmaxim(MinNode->next, pozmin - 1, indice);
}

void BonusLevel(BonusNode *root, int level, int ok, int players)
{
    int indice;
    int max;
    int min;
    int pozmax, pozmin;
    int dubla;
    pozmax = 0;
    pozmin = 0;
    if (root == NULL)
        return;
    if (level == 1)
    {
        if (ok % players != 0)
        {
            if (root->child != NULL)
            {
                min = root->child->indici[0];
                pozmin = 0;
                min = FindBonMin(root->child, min, 0, &pozmin);
                for (indice = 0; indice < players; indice++)
                {
                    dubla = pozmin;
                    root->indici[indice] = recursivminim(root->child, dubla, indice);
                }
            }
        }
        if (ok % players == 0)
        {
            if (root->child != NULL)
            {
                max = root->child->indici[0];
                pozmax = 0;
                max = FindBonMax(root->child, max, 0, &pozmax);
                for (indice = 0; indice < players; indice++)
                {
                    dubla = pozmax;
                    root->indici[indice] = recursivmaxim(root->child, dubla, indice);
                }
            }
        }
    }
    if (level >= 1)
    {
        BonusLevel(root->child, level - 1, ok, players);
        BonusLevel(root->next, level, ok, players);
    }
}

void AlgoBonus(BonusNode *MinNode, int h, int players)
{
    int i;
    int ok;
    if (h >= players)
    {
        ok = h % players;
        if (ok == 0)
        {
            ok = 2;
        }
    }
    else
    {
        ok = players - h + 2;
    }
    for (i = h - 1; i >= 1; i--)
    {
        BonusLevel(MinNode, i, ok, players);
        ok++;
    }
}

void freeBonus(BonusNode *root)
{
    if (root != NULL)
    {
        freeBonus(root->next);
        freeBonus(root->child);
        free(root->indici);
        free(root);
    }
}
