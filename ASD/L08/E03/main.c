#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "datetime.h"
#include "titoli.h"
#include "quotazioni.h"

#define DBG 0

void leggiFile( char *fn, LISTtitoli LISTtitoli);
void menu();

int main(int argc, char **argv) {
    LISTtitoli titoli = LISTtitoliInit();
    Titolo t;
    Quotazione q;
    float f1, f2;
    char strTmp[100], strTmp1[100];
    int selezione, fine=1;

    do {
        menu();
        scanf("%d", &selezione);
        switch(selezione){
            case 0: {
                fine=0;
            } break;

            case 1: {
                printf("Inserire nome file: ");
                scanf("%s", strTmp);
                leggiFile(strTmp, titoli);
            } break;

            case 2: {
                LISTtitoliStore(titoli, stdout);
            } break;

            case 3: {
                printf("Inserire codice titolo: ");
                scanf("%s", strTmp);
                t = LISTtitoliSearch(titoli, strTmp);
                if (t != NULL)
                    TITOLOstore(stdout, t);
            } break;

            case 4: {
                printf("Inserire codice titolo: ");
                scanf("%s", strTmp);
                t = LISTtitoliSearch(titoli, strTmp);
                if (t != NULL) {
                    printf("Inserire data: ");
                    scanf("%s", strTmp);
                    q = TITOLOgetQuotazione(t, DATAload(strTmp));
                    QUOTAZIONEstore(stdout, q);
                }
            } break;

            case 5: {
                printf("Inserire codice titolo: ");
                scanf("%s", strTmp);
                t = LISTtitoliSearch(titoli, strTmp);
                if (t != NULL)
                    printf("MIN = %.2f || MAX = %.2f\n", TITOLOminAssoluto(t), TITOLOmaxAssoluto(t));
            } break;

            case 6: {
                printf("Inserire codice titolo: ");
                scanf("%s", strTmp);
                t = LISTtitoliSearch(titoli, strTmp);
                if (t != NULL) {
                    printf("Inserire data 1: ");
                    scanf("%s", strTmp);
                    printf("Inserire data 2: ");
                    scanf("%s", strTmp1);
                    TITOLOminmaxRange(t, DATAload(strTmp), DATAload(strTmp1), &f1, &f2);
                    printf("MIN = %.2f || MAX = %.2f\n", f1, f2);
                }
            } break;

            case 7: {
                printf("Inserire codice titolo: ");
                scanf("%s", strTmp);
                t = LISTtitoliSearch(titoli, strTmp);
                if (t != NULL)
                    TITOLOtreeBalance(t);
            } break;

            default:{
                printf("Scelta non valida\n");
            } break;
        }
    } while(fine!=0);

    return 0;
}


void leggiFile(char *fn, LISTtitoli LISTtitoli) {
    char cod[LEN], data[DATELEN], ora[TIMELEN];
    int quote = 0, i, qta,num=0;
    float valore;
    Titolo t;
    FILE *fp = fopen(fn, "r");
    if (fp == NULL)
        return;
    fscanf(fp,"%d",&num);
    for(int j=0; j<num; j++)
    {
        while (fscanf(fp, "%s %d\n", cod, &quote) == 2) {
            t = LISTtitoliSearch(LISTtitoli, cod);
            if (t == NULL) {
                t = TITOLOnew(cod);
                LISTtitoliInsert(LISTtitoli, t);
            }

            for (i = 0; i < quote; i++) {
                fscanf(fp, "%s %s %f %d\n", data, ora, &valore, &qta);
                TITOLOinsertTransazione(t, DATAload(data), ORAload(ora), valore, qta);
            }
        }
    }

    fclose(fp);
    return;
}


void menu()
{
    printf("\n");
    printf("0- Uscita\n");
    printf("1- Leggi file\n");
    printf("2- Stampa titoli\n");
    printf("3- Stampa titolo\n");
    printf("4- Stampa quotazione\n");
    printf("5- Stampa quotazione MIN/MAX assoluti\n");
    printf("6- Stampa quotazione MIN/MAX intervallo\n");
    printf("7- Bilanciamento\n");
}

