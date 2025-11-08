//
// Created by Fabio Audisio on 20/01/23.
//

#ifndef E01_GRAPH_H
#define E01_RAPH_H

#include "ST.h"
#include "stdio.h"


typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fout);
int   GRAPHgetIndex(Graph G, char *label);
int GRAPHgetNEdges(Graph G);
int GRAPHgetNVertex(Graph G);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
Graph GRAPHedgesToDAG(Graph G,Edge *E);
void GRAPHcopy(Graph G1,Graph G2);
void  GRAPHspD(Graph G, int id);
void  GRAPHspBF(Graph G, int id);
void  DAGlongestpath(Graph G);
Graph GRAPHedgestoDAG(Graph G,Edge *E);

#endif //E01_GRAPH_H