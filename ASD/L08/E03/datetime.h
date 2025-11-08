#ifndef DATETIME_H_DEFINED
#define DATETIME_H_DEFINED
#define DATELEN 13 /* aaaa/mm/gg */
#define TIMELEN 6  /* hh:mm */

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct data_ {
    int aaaa, mm, gg;
} Data;

typedef struct ora_ {
    int hh, mm;
} Ora;

Data DATAload(char *s);
Ora  ORAload(char *s);
int  DATAcmp(Data d1, Data d2);
void DATAstore(Data d, FILE *fp);
void ORAstore(Ora o, FILE *fp);

#endif