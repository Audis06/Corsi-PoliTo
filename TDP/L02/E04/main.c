#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LEN 25

int codifica(FILE *fin, FILE *fout);
int decodifica(FILE *fin, FILE *fout);


int main() {
    char in[LEN], out[LEN];
    FILE *fin, *fout;
    int c, res;

    printf("Inserire operazione da eseguire: Codifica-0 e Decodifica-1: ");
    scanf("%d",&c);

    printf("Inserire nome file di input: ");
    scanf("%s", &in);

    fin=fopen(in,"r");
    if(fin==NULL){
        printf("Errore durante l'apertura del file o non ancora effettuata operazione di codifica");
        return 1;
    }
    printf("Inserire nome file di output: ");
    scanf("%s", &out);
    fout=fopen(out,"w");

    switch(c){
        case 0:
            res=codifica(fin,fout);
            printf("Numero di caratteri scritti nel file di output: %d", res);
            break;
        case 1:
            res=decodifica(fin,fout);
            printf("Numero di caratteri scritti nel file di output: %d", res);
            break;
        default:
            printf("Operazione non valida");
            return 2;
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

int codifica(FILE *fin, FILE *fout){
    char c0, c1;
    int k=0, count=0, h, ch;

    c1=getc(fin);
    while(c1 != EOF){
        if(isdigit(c1)){
            ch = (c1 - '0') + k;
            while (ch >= 10) {
                ch -= 10;
            }
            fprintf(fout, "%d", ch);
            k++;
            count++;
            c0 = ch;
        }
        else if (isalpha(c1) && isalpha(c0)) {
            h = toupper(c0) - 'A';
            ch = c1 + h;
            if(ch > 'Z' && isupper(c1)){
                while(ch >'Z'){
                    ch -= 26;
                }
            }
            else if(ch > 'z' && islower(c1)){
                while(ch > 'z'){
                    ch -= 26;
                }
            }
            fprintf(fout, "%c", ch);
            count++;
            c0 = ch;
        }
        else{
            fprintf(fout, "%c", c1);
            c0 = c1;
        }
        c1=getc(fin);
    }
    return count;
}

int decodifica(FILE *fin, FILE *fout){
    char c0, c1;
    int k=0, count=0, h, ch;

    c1=getc(fin);
    while(c1 != EOF){
        if(isdigit(c1)){
            ch = (c1 - '0') - k;
            while (ch < 0) {
                ch += 10;
            }
            fprintf(fout, "%d", ch);
            k++;
            count++;
            c0 = ch;
        }
        else if (isalpha(c1) && isalpha(c0)) {
            h = toupper(c0) - 'A';
            ch = c1 - h;
            if(ch < 'A' && isupper(c1)){
                while(ch < 'A'){
                    ch += 26;
                }
            }
            else if(ch < 'a' && islower(c0)){
                while(ch < 'a'){
                    ch += 26;
                }
            }
            fprintf(fout, "%c", ch);
            count++;
            c0 = c1;
        }
        else{
            fprintf(fout, "%c", c1);
            c0 = c1;
        }
        c1=getc(fin);
    }
    return count;
}
