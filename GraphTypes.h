#define MAXVERTEX 20

typedef enum {FALSE, TRUE} Boolean;

typedef int Vertex;
typedef int Weight;

typedef struct edge {
   Vertex endpoint;
   Weight weight;
   struct edge *nextedge;
} Edge;

typedef struct graph {
   int n;     /* number of vertices in the graph */
   Edge *firstedge[MAXVERTEX];
} Graph;

typedef struct edge_kruskal {
    int S, D, weight;
} edge;

typedef struct edge_list {
    edge endpoint[MAXVERTEX];
    int n;
} edge_list;


