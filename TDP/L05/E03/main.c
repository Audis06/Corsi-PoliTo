#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define matrice 30

int riga(int mat[matrice][matrice], int indice, int nr, int nc, int dir, int posizioni);
int colonna(int mat[matrice][matrice], int indice, int nr, int nc, int verso, int posizioni);

int  main()
{
    FILE *fp;
    int i=0, j=0, nr=0, nc=0;
    int mat[matrice][matrice];
    char selettore[10];
    char direzione[10];
    int indice=0, posizioni=0;
    int dir=0, verso=0, fine=0;

    fp = fopen("mat.txt", "r");
    fscanf(fp, "%d %d", &nr, &nc);

    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    fclose(fp);

    printf("Inserire <selettore> <indice> <direzione> <posizioni>: ");
    scanf("%s %d %s %d", &selettore, &indice, &direzione, &posizioni);
    if (!strcmp(selettore, "riga"))
    {
        if (!strcmp(direzione, "destra"))
        {
            dir=1;
        }
        else
        {
            dir=-1;
        }
        riga(mat,indice,nr,nc,dir,posizioni);
    }
    else
    {
        if (!strcmp(direzione, "giu"))
        {
            verso=-1;
        }
        else
        {
            verso=1;
        }
        colonna(mat,indice,nr,nc,verso,posizioni);
    }
    for (int i = 0; i < nr; i++)
    {
        for (int j = 0; j < nc; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int riga(int mat[matrice][matrice], int indice, int nr, int nc, int dir, int posizioni)
{
    int tmp=0;
    indice=indice-1;
    if (dir == -1)//spostamento verso sinistra
    {
        for (int k = 0; k < posizioni; k++)
        {
            tmp = mat[indice][0];
            for (int i = 0; i < nc-1; i++)
            {
                mat[indice][i] = mat[indice][i + 1];
            }
            mat[indice][nc - 1] = tmp;
        }
    }
    if (dir == 1)//spostamento verso destra
    {
        for (int k = 0; k < posizioni; k++)
        {
            tmp = mat[indice][nc - 1];
            for (int i = nc -1; i > 0; i--)
            {
                mat[indice][i] = mat[indice][i - 1];
            }
            mat[indice][0] = tmp;
        }
    }
    return mat;
}


int colonna(int mat[matrice][matrice], int indice, int nr, int nc, int verso, int posizioni)
{
    int tmp = 0;
    if (verso == 1)
    {
        for (int k = 0; k < posizioni; k++)
        {
            tmp = mat[0][indice-1];
            for (int i = 0; i < nr-1; i++)
            {
                mat[i][indice-1] = mat[i+1][indice-1];
            }
            mat[nr-1][indice-1] = tmp;
        }
    }
    if (verso == -1)
    {
        for (int k = 0; k < posizioni; k++)
        {
            tmp = mat[nr-1][indice-1];
            for (int i = nr - 1; i > 0; i--)
            {
                mat[i][indice-1] = mat[i-1][indice - 1];
            }
            mat[0][indice -1] = tmp;
        }
    }
    return mat;
}