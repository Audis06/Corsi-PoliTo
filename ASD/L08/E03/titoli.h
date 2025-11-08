#ifndef LISTTITOLI_H_DEFINED
#define LISTTITOLI_H_DEFINED
#define LEN 256

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "titolo.h"

typedef struct LISTtitoli_ *LISTtitoli;

int        LISTtitoliEmpty(LISTtitoli titoli);
Titolo     LISTtitoliSearch(LISTtitoli titoli, char *cod);
void       LISTtitoliInsert(LISTtitoli titoli, Titolo t);
LISTtitoli LISTtitoliInit();
void       LISTtitoliStore(LISTtitoli titoli, FILE *fp);

#endif
