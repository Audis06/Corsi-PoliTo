#include <stdio.h>
#include<stdlib.h>

typedef struct{
    int s,f;
}att;
//definizione funzioni
att *leggi(int *n);
void MergeSort(att *v, int n);
void MergeSortR(att *v, att *B, int l, int r);
void Merge(att *v, att *B, int l, int q, int r);
void attSelDP(int n, att *v);
void print_solR(att *vet, int i, int *ind);
void print_sol(att *vet, int n, int *w, int *ind);

int main(){
    att *v;
    int n;

    v=leggi(&n);
    //lettura da file
    printf("Inserimento iniziale:\n");
    for(int i=0; i<n;i++) {
        printf("%d %d", v[i].s, v[i].f);
        printf("\n");
    }
    //funzione di ordinamento
    MergeSort(v,n);
    //Attività ordinate
    printf("Attivita ordinate per tempo di fine:\n");
    for(int i=0; i<n;i++) {
        printf("%d %d", v[i].s, v[i].f);
        printf("\n");
    }
    //stampa e ricerca delle soluzioni migliori
    printf("Soluzione con programmazione dinamica:\n");
    attSelDP(n,v);
    return 0;
}

att *leggi(int *n){
    FILE *fp;
    char nomeFile[50];
    att *lett;

    printf("Inserisci il nome del file da aprire:\n");
    scanf("%s",nomeFile);
    if((fp=fopen(nomeFile,"r"))==NULL)
    {
        printf("\n Errore nell'apertura del file\n");
        return 0;
    }
    fscanf(fp,"%d",n);

    lett=calloc((*n+1),sizeof(att));

    for(int i=0; i<*n;i++)
        fscanf(fp,"%d %d",&lett[i].s, &lett[i].f);
    fclose(fp);
    return lett;
}

void MergeSort(att *v, int n){
    int l=1, r=n-1;
    att *B = (att *)malloc((n+1)*sizeof(att));
    if (B == NULL) {
        printf("Errore\n");
        exit(1);
    }
    MergeSortR(v, B, l, r);
}

void MergeSortR(att *v, att *B, int l, int r) {
    int q;
    if (r <= l)
        return;
    q = (l + r)/2;
    MergeSortR(v, B, l, q);
    MergeSortR(v, B, q+1, r);
    Merge(v, B, l, q, r);
}

void Merge(att *v, att *B, int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q+1;
    for(k = l; k <= r; k++)
        if (i > q)
            B[k] = v[j++];
        else if (j > r)
            B[k] = v[i++];
        else if (v[i].f <= v[j].f)
            B[k] =v[i++];
        else
            B[k] = v[j++];
    for ( k = l; k <= r; k++ )
        v[k] = B[k];
    return;
}

void attSelDP(int n, att *v) {
    int i, j;
    int *ind, *w, w_tmp;

    ind = (int *)malloc(n*sizeof(int));
    w = (int *)malloc(n*sizeof(int));
    if(ind==NULL || w==NULL){
        printf("Errore.\n");
        exit(-1);
    }
    ind[0]=-1; w[0]=v[0].f-v[0].s;
    for(i=1; i<n; i++){
        ind[i]=-1; w[i]=v[i].f-v[i].s;
        w_tmp=w[i];
        for(j=0; j<i; j++){//controllo di ogni prefisso per ogni attività selezionata dal ciclo esterno
            if((v[j].s<=v[i].f && v[j].f<=v[i].s) && w[i]<w_tmp+w[j]){//controlla della compatibilità di due attività
                ind[i]=j;
                w[i]=w_tmp+w[j];
            }
        }
    }
    print_sol(v, n, w, ind);      //stampa della soluzione
    free(ind);
    free(w);
}

void print_solR(att *vet, int i, int *ind){         //stampa ricosrsiva della soluzione
    if(i==-1){
        return;
    }
    print_solR(vet, ind[i], ind);
    printf("(%d,%d) ", vet[i].s, vet[i].f);
}

void print_sol(att *vet, int n, int *w, int *ind){
    int i, max_w=0, max_i=-1;
    for(i=0; i<n; i++){             //selezione dell'attività che termina la soluzione
        if(w[i]>=max_w){
            max_i=i;
            max_w=w[i];
        }
    }
    printf("Sequenza di attivita con somma delle durate massima:\n");
    print_solR(vet, max_i, ind);        //stampa della soluzione
}
