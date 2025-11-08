//
// Created by Fabio Audisio on 20/01/23.
//

#ifndef E01_ST_H
#define E01_ST_H



typedef struct symboltable *ST;

ST    STinit(int maxN);
void  STfree(ST st);
int   STsize(ST st);
ST STcopy(ST st);
void  STinsert(ST st, char *str, int i);
int   STsearch(ST st, char *str);
char *STsearchByIndex(ST st, int i);

#endif //E01_ST_H