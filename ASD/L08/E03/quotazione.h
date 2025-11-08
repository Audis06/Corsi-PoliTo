#ifndef QUOTAZIONE_H_DEFINED
#define QUOTAZIONE_H_DEFINED

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "datetime.h"

typedef struct QUOTAZIONE_ {
    Data data;
    float num;
    int den;
} Quotazione;


void       QUOTAZIONEstore(FILE *fp, Quotazione q);
float      QUOTAZIONEgetValore(Quotazione q);
Data       QUOTAZIONEgetData(Quotazione q);
//Quotazione QUOTAZIONEnew(Data d);
int        QUOTAZIONEcheckNull(Quotazione q);
Quotazione QUOTAZIONEsetNull();

#endif
