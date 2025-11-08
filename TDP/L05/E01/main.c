#include <stdio.h>
#include <stdlib.h>

#define n 20
#define m 20

int main()
{
    FILE *fp;
    int i=0,j=0;
    int ris[n][m];
    char c='c';

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            ris[i][j] = 0;
        }
    }
i=0;
j=0;

fp = fopen("classifica.txt", "r");
if (fp == NULL)
{
    printf("ERRORE APERTURA FILE");
    exit(1);
}

while (!feof(fp) && i < n)
{
    c = ' ';
    j = 0;
    while (!feof(fp) && j < m && c != '\n')
    {
        fscanf(fp, "%d", &ris[i][j]);
        fscanf(fp, "%c", &c);
        j++;
    }
    i++;
}

int righe=ris[0][0]+1;
int colonne=ris[0][1];

int max=0;
int max_colonne[m];
int indice=0;
int somma;
int massimo=0;
j=0;

for(i=0; i<colonne; i++)
{
    indice=0;
    somma=0;
    max=0;
    for(j=1; j<righe; j++)
    {
        for (int k = 0; k < i+1; k++)
        {
            somma += ris[j][k];
        }
        if (somma > max)
        {
            max = somma;
            indice = j;
        }
        somma=0;
    }
    printf("%d\n", indice);
}
printf("La squadra vincitrice è la squadra numero %d", indice);
for(i=0;i<colonne;i++)
{
    for(j=0;j<righe;j++)
    {
        max = ris[j][i];
        if (max > massimo)
        {
            massimo = j;
        }
    }
    printf("%d", massimo);
    max=0,massimo=0;
}
}