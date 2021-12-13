/*  Author : Panagiotis Giovanos
       SDI : *******
    Lesson : K08 - Data Structures and Programming Techniques
  Question : *                                                */

#include <stdio.h>
#include "ST.h"
int main(int argc,char *argv[])
{
    Graph G;
    Initialize(&G);
    int e; scanf("%d", &e);
    for (int i = 0; i < e ; ++i) {
        int S,D,W;
        scanf("%d-%d-%d", &S, &D, &W);
        InsertEdge(S,D,W,&G);
    }
    printf("Vertex X : Adjacency List\n");
    Print(&G);
    Kruskal(&G);
    DestroyGraph(&G);
    return  0;
}
