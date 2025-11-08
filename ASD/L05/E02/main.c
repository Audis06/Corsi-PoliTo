#include<stdio.h>
#include<stdlib.h>

typedef struct{
    char col[2];
    int val[2];
}colori;

typedef struct{
    int tile;
    int rot;
}mosse;

colori *leggiColori(int *Ncolori);
mosse **leggiMosse(int *mark, int Ncolori, int *R, int *C);
void completa(mosse **vmosse, colori *vcolori, int R, int C, int Ncolori, int *mark);
void completaR(int pos, mosse **vmosse, colori *vcolori, int R, int C, int Ncolori, int *mark, int *bestScore, mosse **bestmosse);
int score(mosse **vmosse, colori *vcolori, int R, int C, int Ncolori);

int main(){
    int Ncolori=0, *mark=calloc(Ncolori,(sizeof(int))), R=0, C=0;
    colori *vcolori;
    mosse **vmosse;
    vcolori=leggiColori(&Ncolori);
    mark=calloc(Ncolori,sizeof(int));
    vmosse=leggiMosse(mark, Ncolori, &R, &C);
    completa(vmosse, vcolori, R, C, Ncolori, mark);
    return 0;
}

colori *leggiColori(int *Ncolori){
    FILE *fp;
    colori *vcolori;

    if((fp=fopen("tiles.txt","r"))==NULL)
        printf("errore\n");

    fscanf(fp,"%d\n",Ncolori);
    vcolori=malloc(*Ncolori*sizeof(colori));
    printf("Il numero di combinazioni colori sono %d\n",*Ncolori);
    for(int i=0;i<*Ncolori;i++)
    {
        fscanf(fp,"%c %d %c %d\n",&vcolori[i].col[0], &vcolori[i].val[0],&vcolori[i].col[1], &vcolori[i].val[1]);
        printf("%c %d %c %d\n",vcolori[i].col[0], vcolori[i].val[0],vcolori[i].col[1], vcolori[i].val[1]);
    }
    fclose(fp);
    return vcolori;
}

mosse **leggiMosse(int *mark, int Ncolori, int *R, int *C){
    int i, j;
    mosse **vmosse;
    FILE *fp;

    if((fp=fopen("board.txt","r"))==NULL)
    {
        printf("Errore\n");
        return 0;
    }

    fscanf(fp,"%d %d\n",R,C);

    vmosse=calloc(*R,sizeof(mosse*));
    for(i=0;i<*R;i++)
    {
        vmosse[i]=calloc(*C,sizeof(mosse*));
        for(j=0;j<*C;j++)
        {
            fscanf(fp, "%d/%d", &vmosse[i][j].tile,&vmosse[i][j].rot);
            /* Se c'e' la tessera */
            if (vmosse[i][j].tile >= 0 && vmosse[i][j].tile < Ncolori) {
                /* Controllo se e' gia' usata */
                if (mark[vmosse[i][j].tile])
                    return NULL; /* Tessera usata due o più volte */
                else
                    mark[vmosse[i][j].tile] = 1; /* Marcala come usata */
            }
        }
    }
    printf("\nLe mosse da fare sono:\n");
    for(int i=0;i<*R;i++)
    {
        for(int j=0;j<*C;j++)
        {
            printf("%d/%d ", vmosse[i][j].tile,vmosse[i][j].rot);
        }
        printf("\n");
    }
    fclose(fp);
    return vmosse;
}

void completa(mosse **vmosse, colori *vcolori, int R, int C, int Ncolori, int *mark) {
    int bestScore = -1, i, j;
    mosse **bestmosse;

    bestmosse = calloc(R, sizeof(mosse*));
    for (i=0; i<R; i++)
        bestmosse[i] = calloc(C, sizeof(mosse));

    completaR(0, vmosse, vcolori, R, C, Ncolori, mark, &bestScore, bestmosse);

    printf ("\nSoluzione ottima: %d\n", bestScore);
    for (i=0; i<R; i++) {
        for(j=0;j<C;j++)
            printf("%d/%d ", bestmosse[i][j].tile, bestmosse[i][j].rot);
        printf("\n");
    }
    printf("\n");
}

void completaR(int pos, mosse **vmosse, colori *vcolori, int R, int C, int Ncolori, int *mark, int *bestScore, mosse **bestmosse) {
    int i, j, r, c, currScore;

    if (pos >= (R*C)) { /* Terminazione e check */
        currScore = score(vmosse, vcolori, R, C, Ncolori);
        if (currScore > *bestScore) {
            *bestScore = currScore;
            for (i=0; i<R; i++)
                for(j=0;j<C;j++)
                    bestmosse[i][j] = vmosse[i][j];
        }
        return;
    }

    r = pos / C;
    c = pos % C;

    if (vmosse[r][c].tile == -1) /* Cella vuota nella vmosse di gioco, prova tutte le tessere disponibili */
        for (i=0; i<Ncolori; i++) {
            if (mark[i]) /* Se già usate, procedi */
                continue;
            mark[i] = 1; /* marca la tessera come usata */
            vmosse[r][c].tile = i; /* piazza la tessera sulla vmosse di gioco */
            vmosse[r][c].rot = 0; /* Tessera nella direzione 'originale' */
            completaR(pos+1, vmosse, vcolori, R, C, Ncolori, mark, bestScore, bestmosse); /* ricorri sulla prossima */
            vmosse[r][c].rot = 1; /* Tessera nella direzione 'ruotata' */
            completaR(pos+1, vmosse, vcolori, R, C, Ncolori, mark, bestScore, bestmosse); /* ricorri sulla prossima */
            /* Backtrack */
            vmosse[r][c].tile = -1;
            mark[i] = 0;
        }
    else /* Cella piena, ricorri sulla successiva */
        completaR(pos+1, vmosse, vcolori, R, C, Ncolori, mark, bestScore, bestmosse);
}

int score(mosse **vmosse, colori *vcolori, int R, int C, int Ncolori) {
    int sum = 0, part = 0, i, j;
    char first = '\0';

    for (i=0; i<R; i++) { /* Per tutte le righe (check in orizzontale)  */
        part = 0;
        first = '\0';
        for (j=0; j<C; j++) { /* Per tutte le colonne  */
            if (vmosse[i][j].tile < 0 || vmosse[i][j].tile >= Ncolori) /* Consistenza */
                return -1;
            if (j == 0) {
                /* Memorizza il colore della prima cella incontrata come riferimento */
                first = vcolori[vmosse[i][j].tile].col[(0+vmosse[i][j].rot)%2];
                part = vcolori[vmosse[i][j].tile].val[(0+vmosse[i][j].rot)%2];
            } else {
                if (vcolori[vmosse[i][j].tile].col[(0+vmosse[i][j].rot)%2] == first)
                    /* Se la sequenza di colori non è interrotta, incrementa il parziale */
                    part += vcolori[vmosse[i][j].tile].val[(0+vmosse[i][j].rot)%2];
                else
                    break;
            }
        }
        if (j == C){
            /* Se la sequenza copre l'intera riga, aggiorna il punteggio */
            sum += part;
        }
    }

    for (i=0;i<C;i++) { 	/* Per tutte le colonne (check in verticale) */
        part = 0;
        first = '\0';
        for (j=0; j<R; j++) { /* Per tutte le righe  */
            if (vmosse[j][i].tile < 0 || vmosse[j][i].tile >= Ncolori)/* Consistenza */
                return -1;
            if (j == 0) {
                /* Memorizza il colore della prima cella incontrata come riferimento */
                first = vcolori[vmosse[j][i].tile].col[(1+vmosse[j][i].rot)%2];
                part = vcolori[vmosse[j][i].tile].val[(1+vmosse[j][i].rot)%2];
            } else {
                if (vcolori[vmosse[j][i].tile].col[(1+vmosse[j][i].rot)%2] == first)
                    /* Se la sequenza di colori non è interrotta, incrementa il parziale */
                    part += vcolori[vmosse[j][i].tile].val[(1+vmosse[j][i].rot)%2];
                else
                    break;
            }
        }
        if (j == R)
            sum += part;
    }
    return sum;
}

