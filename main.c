#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "MinMax.h"
#include "queue.h"
#include "bonus.h"

int main(int argc, char *argv[])
{
    int c1;
    int c2;
    int c3;
    int b;

    c1 = 0;
    c2 = 0;
    c3 = 0;
    b = 0;

    if (strcmp(argv[1], "-c1") == 0)
    {
        c1 = 1;
    }
    if (strcmp(argv[1], "-c2") == 0)
    {
        c2 = 1;
    }
    if (strcmp(argv[1], "-c3") == 0)
    {
        c3 = 1;
    }
    if (strcmp(argv[1], "-b") == 0)
    {
        b = 1;
    }

    if (c1 == 1)
    {
        FILE *p;
        p = fopen(argv[2], "r");
        int n, m;
        char curent;
        char space;
        char bile;
        fscanf(p, "%d %d %c", &n, &m, &curent);
        int **M;
        int i, j;
        M = (int **)calloc(n, sizeof(int *));
        for (i = 0; i < n; i++)
        {
            M[i] = (int *)calloc(m, sizeof(int));
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                fscanf(p, "%c", &space);
                fscanf(p, "%c", &bile);
                if (bile == 'R')
                    M[i][j] = 1;
                if (bile == 'B')
                    M[i][j] = 2;
                //printf("%d ", M[i][j]);
            }
            //printf("\n");
        }
        fclose(p);
        FILE *f;
        f = fopen(argv[3], "w");
        ConectNode *ConNode;
        ConNode = createNode();
        ConNode->M = M;
        int v;
        v = castigator(ConNode->M, n, m);
        if (v != 0)
        {
            for (i = n; i >= 0; i--)
            {
                free(M[i]);
            }
            free(M);
            return 0;
        }
        printNode(ConNode, n, m, 0, f);
        int ra, rb;
        ra = 0;
        rb = 1;
        if (curent == 'R')
        {
            insertNode(ConNode, n, m, ra, rb, f);
        }
        else
        {
            rb = 2;
            insertNode(ConNode, n, m, ra, rb, f);
        }

        //for ( i = n ; i >= 0 ; i-- ){
        //    free(M[i]);
        //}
        //free(M);
        freeTree(ConNode, n, m);
    }

    if (c2 == 1 || c3 == 1)
    {

        MinMaxNode *root;
        root = createMinMaxNode();
        FILE *z;
        FILE *v;
        z = fopen(argv[2], "r");
        v = fopen(argv[3], "w");

        int a;
        int i;
        int l;
        char buf[1000];
        int nod;
        char nr[1000];
        int h;
        fgets(nr, 1000, z);
        l = strlen(nr);
        strcpy(nr + l - 1, nr + l);
        char number[1000];

        //inaltimea
        h = atoi(nr);
        if (h <= 2)
            return 0;
        root->ok = 0;
        //root va putea avea copii

        Queue *coada, *frunza;
        char c;
        for (i = 1; i <= h; i++)
        {
            c = '2';
            coada = createQueue();
            frunza = createQueue();
            while (c != '\n')
            {
                if (z != NULL)
                {
                    fscanf(z, "%s", nr);
                    c = fgetc(z);
                }
                nod = -1;
                if (nr[0] == '(')
                {
                    strcpy(buf, nr);
                    l = strlen(buf);
                    strcpy(buf + l - 1, buf + l);
                    strcpy(number, buf + 1);
                    a = atoi(number);
                    nod = 1;
                }
                if (nr[0] == '[')
                {
                    strcpy(buf, nr);
                    l = strlen(buf);
                    strcpy(buf + l - 1, buf + l);
                    strcpy(number, buf + 1);
                    a = atoi(number);
                }
                enqueue(coada, a);
                enqueue(frunza, nod);
            }
            insertMinMaxNode(root, coada, frunza);
            destroyQueue(coada);
            destroyQueue(frunza);
        }
        fclose(z);
        if (c2 == 1)
        {
            Algoritm(root, h);
            printFinal(root, 0, &v);
        }
        if (c3 == 1)
        {
            AlphaBeta(root);
            printFinal(root, 0, &v);
        }
        freeMulticai(root);
        fclose(v);
    }
    if (b == 1)
    {
        BonusNode *root;
        FILE *z;
        FILE *v;
        z = fopen(argv[2], "r");
        v = fopen(argv[3], "w");

        int a;
        int i;
        int l;
        char buf[1000];
        int nod;
        char nr[1000];
        int h, players;
        char u;
        char *p;
        int unu;
        fscanf(z, "%s", nr);
        u = fgetc(z);
        h = atoi(nr);
        fscanf(z, "%s", nr);
        u = fgetc(z);
        players = atoi(nr);
        root = createBonusNode(players);
        char number[1000];

        root->ok = 0;

        Queue *coada, *frunza;
        char c;
        for (i = 1; i <= h; i++)
        {
            c = '2';
            coada = createQueue();
            frunza = createQueue();
            while (c != '\n')
            {
                if (z != NULL)
                {
                    fscanf(z, "%s", nr);
                    c = fgetc(z);
                }
                nod = -1;
                if (nr[0] == '(')
                {
                    strcpy(buf, nr);
                    l = strlen(buf);
                    strcpy(buf + l - 1, buf + l);
                    strcpy(number, buf + 1);
                    a = atoi(number);
                    nod = 1;
                }
                if (nr[0] == '[')
                {
                    strcpy(buf, nr);
                    l = strlen(buf);
                    strcpy(buf + l - 1, buf + l);
                    strcpy(number, buf + 1);
                    p = strtok(number, ",");
                    unu = atoi(p);
                    enqueue(coada, unu);
                    for (l = 2; l <= players; l++)
                    {
                        p = strtok(NULL, ",");
                        unu = atoi(p);
                        enqueue(coada, unu);
                    }
                }
                if (nod == 1)
                {
                    enqueue(coada, a);
                }
                enqueue(frunza, nod);
            }
            insertBonusNode(root, coada, frunza, players);
            destroyQueue(coada);
            destroyQueue(frunza);
        }
        fclose(z);
        AlgoBonus(root, h, players);
        printBonus(root, 0, &v, players);
        freeBonus(root);
        fclose(v);
    }
    return 0;
}
