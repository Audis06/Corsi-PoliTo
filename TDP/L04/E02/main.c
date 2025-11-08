#include <stdio.h>
#define maxN 30

void ruota(int v[maxN], int N, int P, int dir);

int main() {
    int v[maxN];
    int N,P=1,dir;
    printf("Inserire dimensione del vettore: ");
    scanf("%d", &N);
    if(N>maxN){
        printf("Errore. Numero di elementi del vettore troppo elevato\n");
        return 0;
    }
    printf("Inserire i valori del vettore: ");
    for(int i=0; i<N;i++){
        scanf("%d",&v[i]);
    }

    while(P!=0){
        printf("Inserire il numero di posizioni che vuoi ruotare (0 -> per terminare): ");
        scanf("%d",&P);
        if(P!=0) {
            printf("Inserire il verso di rotazione che si vuole effettuare (dir=-1 -> verso dx o dir=1 -> verso sx): ");
            scanf("%d", &dir);
            if(dir==1 || dir==-1) {
                ruota(v, N, P, dir);
                printf("Il vettore ruotato vale: ");
                for (int i = 0; i < N; i++) {
                    if (i == N - 1) {
                        printf("%d\n", v[i]);
                    } else {
                        printf("%d ", v[i]);
                    }
                }
            }
            else{
                printf("Errore inserimento nella direzione della rotazione.\n");
            }
        }
    }
    return 0;
}

void ruota(int v[maxN], int N, int P, int dir){
    int tmp=0;
    if(dir==-1){
        for(int i=0;i<P;i++){
            tmp=v[N-1];
            for(int j=  N-1;j>0;j--){
                v[j]=v[j-1];
            }
            v[0]=tmp;
        }
    }
    else if(dir==1){
        for(int i=0;i<P;i++){
            tmp=v[0];
            for(int j=0;j<N;j++){
                v[j]=v[j+1];
            }
            v[N-1]=tmp;
        }
    }
}