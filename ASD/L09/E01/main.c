//
// Created by Fabio Audisio on 20/01/23.
//
#include "graph.h"
#include "stdlib.h"
#include "stdio.h"

int main(){
    char file[20];
    printf("Inserire nome file: ");
    scanf("%s",&file);
    FILE *fin;
    fin=fopen(file,"r");
    FILE*fout=fopen("out.txt","w");
    Graph G=GRAPHload(fin);
    Graph Dag;
    int EdgeNum=GRAPHgetNEdges(G);
    Edge *E=malloc(EdgeNum*sizeof(Edge));
    GRAPHedges(G,E);
    Dag=GRAPHedgesToDAG(G,E);
    DAGlongestpath(Dag);
    GRAPHstore(Dag,fout);
    fclose(fout);
    return 0;
}