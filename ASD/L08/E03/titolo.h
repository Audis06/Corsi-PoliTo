#ifndef TITOLO_H_DEFINED
#define TITOLO_H_DEFINED

#define LEN 256

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "quotazioni.h"

typedef char* TitoloKey;
typedef struct TITOLO_ *Titolo;

void       TITOLOstore(FILE *out, Titolo t);
int        TITOLOcmp(TitoloKey t1, TitoloKey t2);
TitoloKey  TITOLOgetKey(Titolo t);
Titolo     TITOLOnew(char *cod);
void       TITOLOinsertTransazione(Titolo t, Data d, Ora o, float valore, int qta);
float      TITOLOminAssoluto(Titolo t);
float      TITOLOmaxAssoluto(Titolo t);
void       TITOLOminmaxRange(Titolo t, Data d1, Data d2, float *f1, float *f2);
Quotazione TITOLOgetQuotazione(Titolo t, Data d);
void       TITOLOtreeBalance(Titolo t);

#endif
