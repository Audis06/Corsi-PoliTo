#include <stdio.h>

int comprimi(FILE *fin, FILE *fout);
int decomprimi(FILE *fin, FILE *fout);

int main() {
    FILE *fin;
    FILE *fout;
    int choice, res;

    printf("Inserisci l'operazione da eseguire. Codifica-0 e Decodifica-1: ");
    scanf("%d", &choice);

    switch(choice){
        case 0:
            fin = fopen("sorgente.txt", "r");
            if(fin==NULL) {
                printf("Errore durante l'apertura del file");
                return 1;
            }
            fout = fopen("ricodificato.txt", "w");
            res=comprimi(fin, fout);
            printf("Numero di caratteri scritti nel file di output: %d\n", res);
            break;
        case 1:
            fin = fopen("ricodificato.txt", "r");
            if(fin==NULL) {
                printf("Errore durante l'apertura del file");
                return 1;
            }
            fout = fopen("decompresso.txt", "w");
            res=decomprimi(fin, fout);
            printf("Numero di caratteri scritti nel file di output: %d\n", res);
            break;

        default:
            printf("Operazione non valida");
            return 2;
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

int comprimi(FILE *fin, FILE *fout){
    int count = 0, caratteriScritti = 0;
    char c1, c2;

    c1 = getc(fin);
    c2 = getc(fin);

    while (c2 != EOF) {
        while (c1 == c2 && count < 9) {
            count += 1;
            c1 = c2;
            c2 = getc(fin);
        }

        if (count > 1) {
            fprintf(fout, "%c$%d", c1, count);
            caratteriScritti += 3;
        }

        else if(count == 1){
            fprintf(fout, "%c%c", c1, c1);
            caratteriScritti += 2;
        }

        else {
            fprintf(fout, "%c", c1);
            caratteriScritti += 1;
        }

        c1 = c2;
        c2 = getc(fin);
        count = 0;
    }

    return caratteriScritti;
}
int decomprimi(FILE *fin, FILE *fout){
    int caratteriScritti = 0;
    char c2, c1 = '\0', ripetizioni;

    c2 = getc(fin);

    while (c2 != EOF) {

        if (c2 == '$') {
            ripetizioni = getc(fin) - '0';
            for (int i = 0; i < ripetizioni; i++) {
                fprintf(fout, "%c", c1);
                caratteriScritti += 1;
            }
        }
        else{
            fprintf(fout, "%c", c2);
            caratteriScritti += 1;
        }

        c1 = c2;
        c2 = getc(fin);
    }
    return caratteriScritti;
}
