#include <stdio.h>
#define N_MAX 30

void sottoSequenza(int V[], int N);

int main() {
    int V[N_MAX];
    int dim;
    printf("Inserire dimensione del vettore: ");
    scanf("%d", &dim);
    if(dim>N_MAX){
        printf("Errore. Numero di elementi del vettore troppo elevato\n");
        return 0;
    }
    printf("Inserire i valori del vettore: ");
    for(int i=0; i<dim;i++){
        scanf("%d",&V[i]);
    }

    /*for(int i=0; i<dim;i++){
        printf("%d\n",V[i]);
    }*/
    sottoSequenza(V,dim);

    return 0;
}

void sottoSequenza(int V[], int N){
    int max=0,dim=0,cnt=0;
    for(int i=0;i<N;i++){
        if(V[i]!=0)
            dim++;
        else {
            if (dim >= max) {
                max = dim;
                cnt++;
            }
            dim=0;
        }
    }

    printf("-Dimensione massima dei sottovettori: %d\n",max);
    dim=0;
    printf("-%d sottovettore/i di dimensione massima sono :\n", cnt);

    for(int i=0;i<N;i++){
        if(V[i]!=0)
            dim++;
        else {
            if (dim == max) {
                printf("[");
                for (int j = i - dim; j < i; j++) {
                    if(j==i-1)
                        printf("%d",V[j]);
                    else {
                        printf("%d ", V[j]);
                    }
                }
                printf("]\n");
            }
            dim = 0;
        }
    }
}
