#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

int castigator(int **M, int n, int m)
{
    int i, j;
    int k, t, r;
    int s;
    int flag;
    flag = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (M[i][j] == 1)
            {
                if (m - 1 - j >= 3)
                {
                    s = 0;
                    for (k = j; k <= j + 3; k++)
                    {
                        if (M[i][k] == 1)
                            s++;
                    }
                    if (s == 4)
                    {
                        flag = 1;
                        break;
                    }
                }
                if (n - 1 - i >= 3 && flag == 0)
                {
                    s = 0;
                    for (k = i; k <= i + 3; k++)
                    {
                        if (M[k][j] == 1)
                            s++;
                    }
                    if (s == 4)
                    {
                        flag = 1;
                        break;
                    }
                }
                if (n - 1 - i >= 3 && flag == 0 && m - 1 - j >= 3)
                {
                    s = 0;
                    t = i;
                    r = j;
                    for (k = 1; k <= 4; k++)
                    {
                        if (M[t][r] == 1)
                            s++;
                        t++;
                        r++;
                    }
                    if (s == 4)
                    {
                        flag = 1;
                        break;
                    }
                }
                if (n - 1 - i >= 3 && flag == 0 && j >= 3)
                {
                    s = 0;
                    t = i;
                    r = j;
                    for (k = 1; k <= 4; k++)
                    {
                        if (M[t][r] == 1)
                            s++;
                        t++;
                        r--;
                    }
                    if (s == 4)
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            if (M[i][j] == 2)
            {
                if (m - 1 - j >= 3)
                {
                    s = 0;
                    for (k = j; k <= j + 3; k++)
                    {
                        if (M[i][k] == 2)
                        {
                            s++;
                        }
                    }
                    if (s == 4)
                    {
                        flag = 2;
                        break;
                    }
                }
                if (n - 1 - i >= 3 && flag == 0)
                {
                    s = 0;
                    for (k = i; k <= i + 3; k++)
                    {
                        if (M[k][j] == 2)
                            s++;
                    }
                    if (s == 4)
                    {
                        flag = 2;
                        break;
                    }
                }
                if (n - 1 - i >= 3 && flag == 0 && m - 1 - j >= 3)
                {
                    s = 0;
                    t = i;
                    r = j;
                    for (k = 1; k <= 4; k++)
                    {
                        if (M[t][r] == 2)
                            s++;
                        t++;
                        r++;
                    }
                    if (s == 4)
                    {
                        flag = 2;
                        break;
                    }
                }
                if (n - 1 - i >= 3 && flag == 0 && j >= 3)
                {
                    s = 0;
                    t = i;
                    r = j;
                    for (k = 1; k <= 4; k++)
                    {
                        if (M[t][r] == 2)
                            s++;
                        t++;
                        r--;
                    }
                    if (s == 4)
                    {
                        flag = 2;
                        break;
                    }
                }
            }
        }
        if (flag == 1 || flag == 2)
            break;
    }
    return flag;
}

ConectNode *createNode()
{
    ConectNode *Node;
    Node = (ConectNode *)malloc(sizeof(ConectNode));
    Node->child = NULL;
    Node->M = NULL;
    Node->next = NULL;
    return Node;
}
int **generate2Matrix(int **J, int n, int m, int curent)
{
    int i, j;
    int **M;
    M = (int **)calloc(n, sizeof(int *));
    for (i = 0; i < n; i++)
    {
        M[i] = (int *)calloc(m, sizeof(int));
    }
    int z;
    int x;
    for (j = 0; j < m; j++)
    {
        for (i = n - 1; i >= 0; i--)
        {
            if (J[i][j] == 0)
            {
                J[i][j] = curent;
                //v = castigator(J,n,m);
                for (z = 0; z < n; z++)
                {
                    for (x = 0; x < m; x++)
                    {
                        M[z][x] = J[z][x];
                    }
                }
                J[i][j] = 0;
                break;
            }
        }
    }
    return M;
}
int ***generateMatrix(int **J, int n, int m, int curent)
{
    int i, j;
    int contor;
    contor = 0;
    for (j = 0; j < m; j++)
    {
        for (i = 0; i < n; i++)
        {
            if (J[i][j] == 0)
            {
                contor++;
                //printf("%d ", J[i][j]);
                break;
            }
        }
    }
    //printf("%d ", contor);
    int ***M;
    int q;
    M = (int ***)calloc(contor, sizeof(int **));
    for (q = 0; q < contor; q++)
    {
        M[q] = (int **)calloc(n, sizeof(int *));
        for (i = 0; i < n; i++)
        {
            M[q][i] = (int *)calloc(m, sizeof(int));
        }
    }

    int p;
    p = 0;
    int z;
    int x;
    for (j = 0; j < m; j++)
    {
        for (i = n - 1; i >= 0; i--)
        {
            if (J[i][j] == 0)
            {
                J[i][j] = curent;
                //v = castigator(J,n,m);
                for (z = 0; z < n; z++)
                {
                    for (x = 0; x < m; x++)
                    {
                        M[p][z][x] = J[z][x];
                    }
                }
                p++;
                J[i][j] = 0;
                break;
            }
        }
    }
    return M;
}

void insertNode(ConectNode *Node, int n, int m, int t, int curent, FILE *argv)
{

    int k;
    k = 0;
    int i, j;
    fprintf(argv, "\n");
    int contor;
    contor = 0;
    for (j = 0; j < m; j++)
    {
        for (i = 0; i < n; i++)
        {
            if (Node->M[i][j] == 0)
            {
                contor++;
                break;
            }
        }
    }
    // printf("%d", contor);
    int v;
    v = castigator(Node->M, n, m);
    if (v == 1 || v == 2)
        return;
    //printf("%d", contor);
    int okk;
    okk = 0;
    int ***T;
    if (contor >= 2)
    {
        okk = 3;
    }
    else
    {
        okk = 2;
    }
    int **L;
    if (contor >= 1)
    {
        t++;
        if (t >= 2)
        {
            if (curent == 1)
                curent = 2;
            else
            {
                curent = 1;
            }
        }
        ConectNode *NouNode;
        NouNode = createNode(n, m);

        if (okk == 3)
        {
            T = generateMatrix(Node->M, n, m, curent);
            NouNode->M = T[0];
        }
        if (okk == 2)
        {
            L = generate2Matrix(Node->M, n, m, curent);
            NouNode->M = L;
        }
        Node->child = NouNode;
        Node = Node->child;
        printNode(Node, n, m, t, argv);
        insertNode(Node, n, m, t, curent, argv);
        ConectNode *NextNode;
        for (k = 1; k < contor; k++)
        {
            NextNode = createNode(n, m);
            NextNode->M = T[k];
            Node->next = NextNode;
            Node = Node->next;
            printNode(Node, n, m, t, argv);
            insertNode(Node, n, m, t, curent, argv);
        }
    }
    if (contor >= 2)
    {
        free(T);
    }
}

void printNode(ConectNode *Node, int n, int m, int tab, FILE *f)
{
    //printf("%s", argv);
    //printf("A intrat");
    int i, j;
    int k;
    for (i = 0; i < n; i++)
    {
        for (k = 1; k <= tab; k++)
        {
            fprintf(f, "\t");
            //        printf("\t");
        }

        for (j = 0; j < m - 1; j++)
        {
            if (Node->M[i][j] == 1)
            {
                fprintf(f, "R ");
                //  printf("R ");
            }
            if (Node->M[i][j] == 2)
            {
                fprintf(f, "B ");
                //  printf("B ");
            }
            if (Node->M[i][j] == 0)
            {
                fprintf(f, "- ");
                //  printf("- ");
            }
        }
        if (Node->M[i][j] == 1)
        {
            fprintf(f, "R");
            //  printf("R");
        }
        if (Node->M[i][j] == 2)
        {
            fprintf(f, "B");
            //  printf("B");
        }
        if (Node->M[i][j] == 0)
        {
            fprintf(f, "-");
            //   printf("-");
        }
        fprintf(f, "\n"); 
        //  printf("\n");
    }
}

void freeTree(ConectNode *Node, int n, int m)
{
    if (Node->child != NULL)
        freeTree(Node->child, n, m);
    if (Node->next != NULL)
        freeTree(Node->next, n, m);
    int i;
    for (i = n - 1; i >= 0; i--)
    {
        free(Node->M[i]);
    }
    free(Node->M);
    free(Node);
}
