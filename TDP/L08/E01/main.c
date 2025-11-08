#include <stdio.h>
#include <stdlib.h>
#define MAXR 50

//prototipi funzioni
void leggiMatrice(int mat[][MAXR], int *nr, int *nc);
void stampaMatrice(int mat[][MAXR], int nr, int nc);
int riconosciRegione(int mat[][MAXR], int nr, int nc, int r, int c, int *pb, int *ph);

int main()
{
    //dichiarazione variabili
    FILE *fp;
    int base[5] = {0};
    int altezza[5] = {0};
    int area[5] = {0};
    int M[MAXR][MAXR];
    int nr, nc;
    int A, i, j, b=0, h=0;
    int max_r = 0, max_c = 0;
    int max_area = 0;

    //apro il file e carico la mappa sulla matrice
    leggiMatrice(M, &nr, &nc);
    //stampo la matrice
    stampaMatrice(M, nr, nc);

    printf("Il numero delle righe e delle colonne usate effettivamente sono: %d e %d\n", nr, nc);

    //scansiono la matrice per righe
    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            b = 0;
            h = 0;
            if (riconosciRegione(M, nr, nc, i, j, &b, &h))
            {
                printf("Rettangolo di estremo <%d,%d>, base %d e altezza %d\n", i, j, b, h); //printf per stampare tutti gli estremi sinistri presenti
                //assegno ai vettori base, altezza e area i valori dei rettagoli con i valori massimi
                if (b > base[2])
                {
                    base[0] = i;
                    base[1] = j;
                    base[2] = b;
                    base[3] = h;
                    base[4] = b * h;
                }
                if (h > altezza[3])
                {
                    altezza[0] = i;
                    altezza[1] = j;
                    altezza[2] = b;
                    altezza[3] = h;
                    altezza[4] = b * h;
                }
                if (b * h > area[4])
                {
                    area[0] = i;
                    area[1] = j;
                    area[2] = b;
                    area[3] = h;
                    area[4] = b * h;
                }
            }
        }
    }

    //stampo dei rettangoli con valori maggiori
    printf("Base Maggiore: estr. sup. SX<%d,%d> b=%d, h=%d, Area=%d\n", base[0], base[1], base[2], base[3], base[4]);
    printf("Area Maggiore: estr. sup. SX<%d,%d> b=%d, h=%d, Area=%d\n", area[0], area[1], area[2], area[3], area[4]);
    printf("Altezza Maggiore: estr. sup. SX<%d,%d> b=%d, h=%d, Area=%d", altezza[0], altezza[1], altezza[2], altezza[3], altezza[4]);
    return 0;
}

//carico la mappa del file sulla matrice
void leggiMatrice(int mat[][MAXR], int *nrp, int *ncp)
{
    int i, j;
    FILE *in = fopen("mappa.txt", "r");
    if (in == NULL)
    {
        printf("ERRORE APERTURA mat.txt");
        exit(1);
    }
    fscanf(in, "%d %d", nrp, ncp);
    for (i = 0; i < *nrp; i++)
        for (j = 0; j < *ncp; j++)
            fscanf(in, "%d", &mat[i][j]);
    fclose(in);
    return;
}

//stampo la matrice
void stampaMatrice(int mat[][MAXR], int nr, int nc)
{
    int i, j;
    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    return;
}

//funzione dove riconosco le regioni
int riconosciRegione(int mat[][MAXR], int nr, int nc, int r, int c, int *pb, int *ph)
{
    int b = 0;
    int h = 0;
    int estremo=1;
    if (mat[r][c] != 1)
        return 0;

    if (mat[r][c] == 1 && estremo == 1)
    { //se mi trovo in un un possibile estremo sinistro di un rettangolo
        if ((mat[r][c - 1] == 1 && c > 0) || (mat[r - 1][c] == 1 && r > 0))
        { //controllo colonne e righe adiacenti
            estremo = 0;
        }
        if (c == nc - 1 && r > 0 && mat[r - 1][c] == 1)
        {
            estremo = 0;
        }
        if (r == nr - 1 && c > 0 && mat[r][c - 1] == 1)
        {
            estremo = 0;
        }
    }
    if (mat[r][c] == 1 && estremo==1)
    {
        for (int i = c; i < nc && mat[r][i] != 0; i++)
        {
            if (mat[r][i] == 1)
            {
                b = b + 1;
            }
        }
        for (int j = r; j < nr && mat[j][c] != 0; j++)
        {
            if (mat[j][c] == 1)
            {
                h = h + 1;
            }
        }
    }
    *pb = b;
    *ph = h;
    return estremo;
}
