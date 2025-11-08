#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define filein "input.txt"
#define fileout "testo.txt"

void elaborazione(FILE *fin, FILE *fout);


int main() {
    FILE *fin;
    FILE *fout;

    fin=fopen(filein, "r");
    if(fin==NULL){
        printf("Errore durante l'apertura del file o non ancora effettuata operazione di codifica");
        return 1;
    }
    fout=fopen(fileout,"w");

    elaborazione(fin, fout);

    fclose(fin);
    fclose(fout);
    return 0;
}

void elaborazione(FILE *fin, FILE *fout){
    char c0,c1,c2;
    int count=0, cmax=25, cor=0, up=0;

    c1=getc(fin);
    while(c1 != EOF){
        if(count<cmax) {
            if (isdigit(c1)) {
                c0 = c1;
                c1 = '*';
                fprintf(fout, "%c", c1);
                count++;
                cor++;
                c1=getc(fin);
            }
            else if(ispunct(c1)){
                c2=getc(fin);
                if(!isspace(c2)){
                    if(!ispunct(c2)) {
                        fprintf(fout, "%c ", c1);
                        count++;
                    }
                    else{
                        fprintf(fout,"%c",c1);
                    }
                }else{
                    fprintf(fout,"%c",c1);
                }
                if(c1=='.' || c1=='!' || c1=='?')
                    up=1;
                count++;
                cor++;
                c0=c1;
                c1=c2;
            }
            else if(isalpha(c1)){
                if(up==1) {
                    c1=toupper(c1);
                }
                up=0;
                fprintf(fout,"%c",c1);
                cor++;
                count++;
                c0=c1;
                c1=getc(fin);
            }
            else if(isspace(c1)){
                if(c1 =='\n'){
                    int c=count;
                    while (c < cmax) {
                        fprintf(fout, "%c", ' ');
                        c++;
                    }
                    c1=getc(fin);
                    cor++;
                    fprintf(fout, "| c: %d\n", cor);
                    c=0;
                    cor=0;
                    count=0;
                }else {
                    fprintf(fout, "%c", c1);
                    cor++;
                    count++;
                    c0 = c1;
                    c1 = getc(fin);
                }
            }
        }
        else{
            fprintf(fout, "| c: %d\n", cor);
            count=0;
            cor=0;
        }
    }
    int c=count;
    while (c < cmax) {
        fprintf(fout, "%c", ' ');
        c++;
    }

    fprintf(fout, "| c: %d\n", cor);
}
