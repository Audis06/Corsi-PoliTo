#ifndef BSTQUOTAZIONI_H_DEFINED
#define BSTQUOTAZIONI_H_DEFINED

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define S 2.0

#include "datetime.h"
#include "quotazione.h"

typedef struct BSTquotazioni_ *BSTquotazioni;

int           BSTquotazioniEmpty(BSTquotazioni bst);
Quotazione    BSTquotazioniSearch(BSTquotazioni bst, Data d);
void          BSTquotazioniInsert(BSTquotazioni bst, Data d, float val, int qta);
void          BSTquotazioniMinmaxRange(BSTquotazioni bst, Data d1, Data d2, float *f1, float *f2);
BSTquotazioni BSTquotazioniInit();
void          BSTquotazioniStore(BSTquotazioni bst, FILE *fp);
void          BSTquotazioniBalance(BSTquotazioni bst);
void          BSTgetMinMax(BSTquotazioni bst, float *min, float *max);

#endif
