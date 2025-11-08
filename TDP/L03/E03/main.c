#include <stdio.h>
#include <math.h>
#define inFile "numeri.txt"

void check(FILE *fin);

int main() {
    FILE *fin;

    if((fin = fopen(inFile, "r")) == NULL){
        printf("Errore durante l'apertura del file\n");
        return 1;
    }

    check(fin);

    fclose(fin);
    return 0;
}

void check(FILE *fin){
    int numCorrente, num1, num2, numMax, numMin, scartati = 0;

    fscanf(fin, "%d", &num1);
    fscanf(fin, "%d", &num2);
    numMax = fmax(num1, num2);
    numMin = fmin(num1, num2);

    while(fscanf(fin, "%d", &numCorrente) != EOF){

        if((numCorrente == num1 + num2) || (numCorrente == num1 - num2) || (numCorrente == num1 * num2) || (num2 != 0 && numCorrente == num1 / num2)){
            numMax = fmax(numMax, numCorrente);
            numMin = fmin(numMin, numCorrente);
            num1 = num2;
            num2 = numCorrente;
        }

        else {scartati++;}
    }

    printf("Numero massimo: %d\n", numMax);
    printf("Numero minimo: %d\n", numMin);

    if (scartati == 0){
        printf("Tutti i dati rispettano la regola\n");
    }
    else{
        printf("Numeri scartati: %d\n", scartati);
    }
}