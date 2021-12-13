/*  Author : Panagiotis Giovanos
       SDI : *******
    Lesson : K08 - Data Structures and Programming Techniques
  Question : *                                                */

#include <stdio.h>
#include <stdlib.h>
#include "GraphTypes.h"

static Edge head;
typedef struct edge* link;
edge_list Kr_G;
edge_list min_spanning;
int n;

// Print the G
void Print(Graph *G) {
    int v;
    for (v = 0; v < MAXVERTEX; v++) {
        Edge *temp = G->firstedge[v];
        if(temp!=NULL) {
            while (temp) {
                printf("%d to %d Weight : %d",v, temp->endpoint,temp->weight);
                temp = temp->nextedge;
                if(temp!=NULL) printf("\n");
            }
            printf("\n");
        }
    }
}

//sortList() will sort nodes of the list in ascending order
void sortList(Graph *G,int S) {
    //Node current will point to head
    Edge *current = G->firstedge[S], *index = NULL;
    int temp,temp_w;
    while(current != NULL) {
        //Node index will point to node next to current
        index = current->nextedge;
        while(index != NULL) {
            //If current node's endpoint is greater than index's node endpoint, swap the endpoint between them
            if(current->endpoint > index->endpoint) {
                temp = current->endpoint;
                temp_w = current->weight;
                current->endpoint = index->endpoint;
                current->weight = index->weight;
                index->endpoint = temp;
                index->weight = temp_w;
            }
            index = index->nextedge;
        }
        current = current->nextedge;
    }
}
void Initialize(Graph *G) {
    G->n=0;
    for (int i = 0; i < MAXVERTEX; ++i) {
        G->firstedge[i] = malloc(sizeof(Edge));
        G->firstedge[i] = NULL;
    }
}

link new_edge(int dst,Weight w) {
    Edge *edge = (link) malloc(sizeof(Edge));

    edge->endpoint = dst;
    edge->weight = w;
    edge->nextedge = NULL;

    return edge;
}
int V[MAXVERTEX];

void count_V(Graph *G){
    int Count=0;
    int v;
    for (v = 0; v < MAXVERTEX; v++) {
        Edge *temp = G->firstedge[v];
        if(temp!=NULL) { Count++; temp = temp->nextedge;}
    }
    G->n = Count;
}

void InsertEdge(Vertex S, Vertex D, Weight W, Graph *G) {

    Edge *New_Edge = new_edge(D,W);
    New_Edge->nextedge = G->firstedge[S];
    G->firstedge[S] = New_Edge;
    sortList(G,S);

    //undirected
    New_Edge = new_edge(S,W);
    New_Edge->nextedge = G->firstedge[D];
    G->firstedge[D] = New_Edge;
    sortList(G,D);
    //Update G->n
    count_V(G);

    //For kruskal's Algorithm
    Kr_G.endpoint[Kr_G.n].S = S;
    Kr_G.endpoint[Kr_G.n].D = D;
    Kr_G.endpoint[Kr_G.n].weight = W;
    Kr_G.n++;
}

// Sort Graph based on weights
void Kr_Sort() {
    int i, j; edge temp;
    for (i = 1; i < Kr_G.n; i++) {
        for (j = 0; j < Kr_G.n - 1; j++) {
            if (Kr_G.endpoint[j].weight > Kr_G.endpoint[j + 1].weight) {
                temp = Kr_G.endpoint[j];
                Kr_G.endpoint[j] = Kr_G.endpoint[j + 1];
                Kr_G.endpoint[j + 1] = temp;
            }
        }
    }
}

int Kr_Find(int data[], int v) {
    return (data[v]);
}

// Union of the MSTs
void Kr_Union(int data[], int S, int D) {
    int i;
    for (i = 0; i < n; i++) if (data[i] == D) data[i] = S;
}

// Kruskal's Algorithm
void Kruskal (Graph *G) {
    int data[MAXVERTEX];
    int cost = 0;
    n = Kr_G.n;

    Kr_Sort(); //Sort by weight

    for (int i = 0; i < n; i++)
        data[i] = i;

    printf("\nMinimum Spanning Tree : \n");

    min_spanning.n = 0;
    int Res_S,Res_D;
    for (int i = 0; i < Kr_G.n; i++) {
        Res_S = Kr_Find(data, Kr_G.endpoint[i].S);
        Res_D = Kr_Find(data, Kr_G.endpoint[i].D);

        if (Res_S != Res_D) {
            printf("\n%d to %d Weight : %d", Kr_G.endpoint[i].S, Kr_G.endpoint[i].D, Kr_G.endpoint[i].weight);
            cost = cost + Kr_G.endpoint[i].weight;
            min_spanning.endpoint[min_spanning.n] = Kr_G.endpoint[i];
            min_spanning.n +=1 ;

            Kr_Union(data, Res_S, Res_D);

        }
    }
    printf("\n\nMinimum Spanning Tree Cost : %d\n", cost);
}

void DestroyGraph(Graph *G){
    int v;
    for (v = 0; v < MAXVERTEX; v++) {
        Edge *temp ;
        while (G->firstedge[v]) {
            temp = G->firstedge[v];
            G->firstedge[v] = G->firstedge[v]->nextedge;
            free(temp);
        }
    }
}