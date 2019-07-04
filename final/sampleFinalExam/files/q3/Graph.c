// Graph.c ... implementation of Graph ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

// type for small +ve int values
typedef unsigned char bool;

// graph representation (adjacency matrix)
typedef struct _graph_rep {
   int    nV;    // #vertices
   int    nE;    // #edges
   bool **edges; // matrix of booleans
} GraphRep;


int wellConnectVertex(Graph g, Vertex v);
void bubbleSortnconns(Connects *a, int size);
void bubbleSortnVertex(Connects *a, int size);
int less(Connects a, Connects b);
int eq(Connects a, Connects b);
void swap(Connects *a, int i, int j);
// validV ... check validity of Vertex

int validV(Graph g, Vertex v)
{
   return (g != NULL && v >= 0 && v < g->nV);
}

// mkEdge ... create an Edge value
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
   assert(validV(g,v) && validV(g,w));
   Edge e; e.v = v; e.w = w;
   return e;
}

// newGraph ... create an empty graph
Graph newGraph(int nV)
{
   assert(nV > 0);
   int i, j;
   bool **e = malloc(nV * sizeof(bool *));
   assert(e != NULL);
   for (i = 0; i < nV; i++) {
      e[i] = malloc(nV * sizeof(bool));
      assert(e[i] != NULL);
      for (j = 0; j < nV; j++)
         e[i][j] = 0;
   }
   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = nV;  g->nE = 0;  g->edges = e;
   return g;
}

// readGraph ... read graph contents from file
static void readError()
{
   fprintf(stderr,"Bad graph data file\n");
   exit(1);
}
Graph readGraph(FILE *in)
{
   Graph g;
   char line[100];
   // get #vertices and create graph
   int nV = 0;
   if (fgets(line,100,in) == NULL) readError();
   if (sscanf(line,"%d",&nV) != 1) readError();
   if (nV < 2) readError();
   g = newGraph(nV);
   // read edge data and add edges
   Vertex v, w;
   while (fgets(line,100,in) != NULL) {
      sscanf(line,"%d-%d",&v,&w);
      insertE(g, mkEdge(g,v,w));
   }
   return g;
}

// showGraph ... display a graph
void showGraph(Graph g)
{
   assert(g != NULL);
   printf("# vertices = %d, # edges = %d\n\n",g->nV,g->nE);
   int v, w;
   for (v = 0; v < g->nV; v++) {
      printf("%d is connected to",v);
      for (w = 0; w < g->nV; w++) {
         if (g->edges[v][w]) printf(" %d",w);
      }
      printf("\n");
   }
}

// insertE ... add a new edge
void  insertE(Graph g, Edge e)
{
   assert(g != NULL);
   assert(validV(g,e.v) && validV(g,e.w));
   if (g->edges[e.v][e.w]) return;
   g->edges[e.v][e.w] = 1;
   g->edges[e.w][e.v] = 1;
   g->nE++;
}

// removeE ... delete an edge
void  removeE(Graph g, Edge e)
{
   assert(g != NULL);
   assert(validV(g,e.v) && validV(g,e.w));
   if (!g->edges[e.v][e.w]) return;
   g->edges[e.v][e.w] = 0;
   g->edges[e.w][e.v] = 0;
   g->nE--;
}

// wellConnected ... list of vertices
// - ordered on #connections, most connected first
Connects *wellConnected(Graph g, int *nconns)
{
   assert(g != NULL && nconns != NULL);
   // TODO: replace the two lines below
   // create a array of connecrs
   Connects *new = malloc(g->nV * sizeof(Connects));
   assert (new != NULL);
   int i = 0;
   Vertex v;
   for (v = 0; v < g->nV; v++) {
       if (wellConnectVertex(g, v) >= 2) {
           new[i].vertx = v;
           new[i].nconn = wellConnectVertex(g, v);
           i++;
       }
   }
   // for now, all the well connect vertex should be store in the *new
   // now we need to sort the array by the nconn in descending order
   bubbleSortnconns(new, i - 1);
   // if the connection of the vertex is the same
   // sorting by vertex number
   bubbleSortnVertex(new, i - 1);
   *nconns = i;
   return new;
}

int wellConnectVertex(Graph g, Vertex v) {
    assert(validV(g, v));
    int count = 0;
    int w;
    for (w = 0; w < g->nV; w++) {
        if (g->edges[v][w] && g->edges[w][v]) {
            count++;
        }
    }
    if (count >= 2) return count;
    return 0;
}

void bubbleSortnconns(Connects *a, int size) {
    int i, j, nswaps;
    for (i = 0; i < size; i++) {
        nswaps = 0;
        for (j = size; j > i; j--) {
            if (!less(a[j], a[j-1])) {
                swap(a, j, j-1);
                nswaps++;
            }
        }
        if (nswaps == 0) break;
    }
}

void bubbleSortnVertex(Connects *a, int size) {
    int i, j, nswaps;
    for (i = 0; i < size; i++) {
        nswaps = 0;
        for (j = size; j > i; j--) {
            if (eq(a[j], a[j - 1]) && a[j].vertx < a[j - 1].vertx) {
                swap(a, j, j-1);
                nswaps++;
            }
        }
        if (nswaps == 0) break;
    }
}


int less(Connects a, Connects b) {
    if (a.nconn < b.nconn) return 1;
    return 0;
}

int eq(Connects a, Connects b) {
    if (a.nconn == b.nconn) return 1;
    return 0;
}

void swap(Connects *a, int i, int j) {
    Connects tmp = a[i];
    a[i].vertx = a[j].vertx;
    a[i].nconn = a[j].nconn;
    a[j].vertx = tmp.vertx;
    a[j].nconn = tmp.nconn;
}
