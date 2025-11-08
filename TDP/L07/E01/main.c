#include <stdio.h>
#include <stdlib.h>
#define N 50

void lettura_file(FILE *fp, int nc, int nr, int M[][N]);
int riconosci_regioni(int M[][N], int nr, int nc,int r, int c, int *pb, int *ph);

int main() {
    FILE *fp;
    int nc,nr;
    int M[N][N];
    int base[5] = {0};
    int altezza[5] = {0};
    int area[5] = {0};
    fp= fopen("mappa.txt","r");
    fscanf(fp,"%d %d",&nr,&nc);
    lettura_file(fp,nc,nr,M);
    fclose(fp);
    //printf("%d %d", nr, nc);
    int i,j,b,h;
    for(i=0; i<nr; i++){
        for(j=0;j<nc;j++){
            b=0;
            h=0;
            if(riconosci_regioni(M,nr,nc,i,j,&b,&h)){
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

    printf("Base Maggiore: estr. sup. SX<%d,%d> b=%d, h=%d, Area=%d\n", base[0], base[1], base[2], base[3], base[4]);
    printf("Area Maggiore: estr. sup. SX<%d,%d> b=%d, h=%d, Area=%d\n", area[0], area[1], area[2], area[3], area[4]);
    printf("Altezza Maggiore: estr. sup. SX<%d,%d> b=%d, h=%d, Area=%d", altezza[0], altezza[1], altezza[2], altezza[3], altezza[4]);
    return 0;
}

void lettura_file(FILE *fp, int nc, int nr, int M[][N]){
    for(int i=0;i<nr;i++){
        for(int j=0; j<nc; j++){
            fscanf(fp,"%d", &M[i][j]);
        }
    }
    printf("La matrice di %d righe e %d colonne vale: \n", nr,nc);
    for(int i=0;i<nr;i++){
        for(int j=0; j<nc; j++){
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int riconosci_regioni(int M[][N], int nr, int nc,int r, int c, int *pb, int *ph){
    int b = 0;
    int h = 0;
    int estremo = 1;
    if (M[r][c] != 1)
        return 0;
    else
    {
        for (int i = c; i < nc && M[r][i] != 0; i++)
        {
            if (M[r][i] == 1)
            {
                b = b + 1;
            }
        }
        for (int j = r; j < nr && M[j][c] != 0; j++)
        {
            if (M[j][c] == 1)
            {
                h = h + 1;
            }
        }
    }
    *pb = b;
    *ph = h;
    return estremo;
}
