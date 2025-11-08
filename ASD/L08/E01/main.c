#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 101
#define MAX_EL 5
#define MAX_DIAG 3

typedef enum mode_t
{
    m_frontale_indietro, m_acrobatico, m_acrobatico_avanti, m_punteggio,
}Mod;

typedef struct elemento
{
    char nome[MAX_LEN];
    int tipologia;
    int ingresso;
    int uscita;
    int precedenza;
    int finale;
    float valore;
    int difficolta;
    float punteggio_specifico;
    float supporto;
}elemento;

typedef struct elenco
{
    int N;
    elemento *elenco;
}Elenco;

typedef struct programma
{
    float parziali[MAX_DIAG];
    float tot;
    int matrice[MAX_DIAG][MAX_EL];
    int diff_raggiunta[MAX_DIAG];
    int *indici;
    int DD;
    int DP;
    int res;
    int bonus;
}Programma;

void Acquisisci_elementi (Elenco *elementi);
void SetUp(Elenco elementi, Programma *programma);
void Greedy (Elenco elementi, Programma *programma);
int elementoEq (elemento *elenco, int A, int B);
void Merge (Elenco elementi, int *A, int *B, int l, int q, int r);
void MergeSortR (Elenco elementi, int *A, int *B, int l, int r);
void MergeSort (Elenco elementi, int *A);
void Stampa (Elenco elementi, Programma programma);
void Check (Elenco elementi, Programma *programma, Mod m);
int Check_Ultimo (int *v);

int main()
{
    Elenco elementi;
    Programma programma;

    Acquisisci_elementi (&elementi);
    if (elementi.elenco==NULL) return 1;

    SetUp(elementi,&programma);
    if (programma.indici==NULL) return 1;

    Greedy(elementi,&programma);

    Stampa(elementi, programma);

    return 0;
}

void Acquisisci_elementi (Elenco *elementi)
{
    FILE *fp;
    int i;

    fp=fopen("elementi.txt","r");
    if (fp==NULL) {
        printf("Errore nell'apertura del file.");
        return;
    }

    elementi->elenco=NULL;

    fscanf(fp, "%d", &elementi->N);

    elementi->elenco = (elemento *) malloc((elementi->N) * sizeof(elemento));
    if (elementi->elenco==NULL) {
        printf("\nErrore nell'allocazione dell'elenco di elementi.");
        return;
    }

    for (i=0; i<elementi->N; i++) {
        fscanf(fp, "%s %d %d %d %d %d %f %d", elementi->elenco[i].nome, &elementi->elenco[i].tipologia, &elementi->elenco[i].ingresso, &elementi->elenco[i].uscita, &elementi->elenco[i].precedenza, &elementi->elenco[i].finale, &elementi->elenco[i].valore, &elementi->elenco[i].difficolta);
        elementi->elenco[i].punteggio_specifico = elementi->elenco[i].valore / (float) elementi->elenco[i].difficolta;
    }
    fclose(fp);

    return;
}

void SetUp(Elenco elementi, Programma *programma)
{
    int i, j;

    programma->indici=NULL;

    programma->indici = (int *) malloc((elementi.N)*sizeof(int));
    if (programma->indici==NULL) {
        printf("\nErrore nell'allocazione del vettore di indici.");
        return;
    }

    for (i=0; i<(elementi.N); i++) programma->indici[i]=i;

    for (i=0; i<MAX_DIAG; i++) {
        programma->diff_raggiunta[i]=0;
        for (j=0; j<MAX_EL; j++) programma->matrice[i][j]=-1;
    }

    printf("Inserire la difficolta' massima di una diagonale:\n");
    scanf("%d", &programma->DD);
    printf("Inserire la difficolta' massima del programma:\n");
    scanf("%d", &programma->DP);
    printf("\n");

    programma->res=0;
    programma->tot=0.0;
    programma->bonus=0;

    return;
}

void Greedy (Elenco elementi, Programma *programma)
{
    int i, j, k, ultimo;

    for (j=0; j<MAX_EL; j++) {
        if (j==0) {
            for (i=0; i<MAX_DIAG; i++) {
                if (i==0) {
                    if (programma->DD>=8) Check(elementi, programma, m_frontale_indietro);  //alternativa m_acrobatico
                    else Check(elementi, programma, m_acrobatico);
                    for (k=0; k<elementi.N; k++) {
                        if (elementi.elenco[programma->indici[k]].ingresso==1 && elementi.elenco[programma->indici[k]].precedenza==0 && (programma->diff_raggiunta[i]+elementi.elenco[programma->indici[k]].difficolta)<=programma->DD && (programma->res+elementi.elenco[programma->indici[k]].difficolta)<=programma->DP) {
                            programma->matrice[i][j] = programma->indici[k];
                            programma->parziali[i] += elementi.elenco[programma->indici[k]].valore;
                            programma->diff_raggiunta[i] += elementi.elenco[programma->indici[k]].difficolta;
                            programma->res += elementi.elenco[programma->indici[k]].difficolta;
                            break;
                        }
                    }
                }
                else if (i==1) {
                    Check(elementi, programma, m_frontale_indietro);
                    for (k=0; k<elementi.N; k++) {
                        if (elementi.elenco[programma->indici[k]].tipologia==0 && elementi.elenco[programma->indici[k]].ingresso==1 && elementi.elenco[programma->indici[k]].uscita==0 && elementi.elenco[programma->indici[k]].precedenza==0 && (programma->diff_raggiunta[i]+elementi.elenco[programma->indici[k]].difficolta)<=programma->DD && (programma->res+elementi.elenco[programma->indici[k]].difficolta)<=programma->DP) {
                            programma->matrice[i][j] = programma->indici[k];
                            programma->parziali[i] += elementi.elenco[programma->indici[k]].valore;
                            programma->diff_raggiunta[i] += elementi.elenco[programma->indici[k]].difficolta;
                            programma->res += elementi.elenco[programma->indici[k]].difficolta;
                            break;
                        }
                    }
                }
                else {
                    Check(elementi, programma, m_acrobatico_avanti);
                    for (k=0; k<elementi.N; k++) {
                        if (elementi.elenco[programma->indici[k]].tipologia==2 && elementi.elenco[programma->indici[k]].ingresso==1 && elementi.elenco[programma->indici[k]].precedenza==0 && (programma->diff_raggiunta[i]+elementi.elenco[programma->indici[k]].difficolta)<=programma->DD && (programma->res+elementi.elenco[programma->indici[k]].difficolta)<=programma->DP) {
                            programma->matrice[i][j] = programma->indici[k];
                            programma->parziali[i] += elementi.elenco[programma->indici[k]].valore;
                            programma->diff_raggiunta[i] += elementi.elenco[programma->indici[k]].difficolta;
                            programma->res += elementi.elenco[programma->indici[k]].difficolta;
                            break;
                        }
                    }
                }
            }
        }
        else {
            Check(elementi, programma, m_punteggio);
            for (i=0; i<MAX_DIAG; i++) {
                for (k=0; k<elementi.N; k++) {
                    if (elementi.elenco[programma->indici[k]].tipologia!=0 && elementi.elenco[programma->matrice[i][j-1]].uscita==elementi.elenco[programma->indici[k]].ingresso && (programma->diff_raggiunta[i]+elementi.elenco[programma->indici[k]].difficolta)<=programma->DD && (programma->res+elementi.elenco[programma->indici[k]].difficolta)<=programma->DP) {
                        programma->matrice[i][j] = programma->indici[k];
                        programma->parziali[i] += elementi.elenco[programma->indici[k]].valore;
                        programma->diff_raggiunta[i] += elementi.elenco[programma->indici[k]].difficolta;
                        programma->res += elementi.elenco[programma->indici[k]].difficolta;
                        break;
                    }
                }
            }
        }
    }

    ultimo = Check_Ultimo(programma->matrice[0]);
    if (elementi.elenco[programma->matrice[0][ultimo]].difficolta>=8) programma->bonus=1;
    for (i=0; i<MAX_DIAG; i++) {
        if (i==0 && programma->bonus==1) programma->tot += programma->parziali[i] * 1.5;
        else programma->tot += programma->parziali[i];
    }

    return;
}

int elementoEq (elemento *elenco, int A, int B)
{
    if (elenco[A].supporto == elenco[B].supporto) return 0;
    else if (elenco[A].supporto > elenco[B].supporto) return 1;
    else return -1;
}

void Merge (Elenco elementi, int *A, int *B, int l, int q, int r)
{
    int i, j, k;

    i=l;
    j=q+1;

    for (k=l; k<=r; k++) {
        if (i>q) B[k] = A[j++];
        else if (j>r) B[k] = A[i++];
        else if ((elementoEq(elementi.elenco,A[i],A[j])==1) || (elementoEq(elementi.elenco,A[i],A[j])==0))   B[k] = A[i++];
        else B[k] = A[j++];
    }

    for (k=l; k<=r; k++) A[k] = B[k];

    return;
}

void MergeSortR (Elenco elementi, int *A, int *B, int l, int r)
{
    int q;

    if (r<=l) return;

    q = (l+r)/2;
    MergeSortR(elementi,A,B,l,q);
    MergeSortR(elementi,A,B,q+1,r);
    Merge(elementi,A,B,l,q,r);

    return;
}

void MergeSort (Elenco elementi, int *A)
{
    int l=0, r=(elementi.N)-1;
    int *B;

    B = (int *) malloc((elementi.N)*sizeof(int));

    MergeSortR(elementi,A,B,l,r);

    free(B);

    return;
}

void Stampa (Elenco elementi, Programma programma)
{
    int i, j;

    printf("\n\nTOT = %.3f\nDifficolta': %d\n\n", programma.tot, programma.res);

    for (i=(MAX_DIAG-1); i>=0; i--) {
        if (i==0 && programma.bonus==1) printf("DIAG #%d > %.3f * 1.5 (BONUS)  Difficolta': %d\n", MAX_DIAG-i, programma.parziali[i], programma.diff_raggiunta[i]);
        else printf("DIAG #%d > %.3f  Difficolta': %d\n", MAX_DIAG-i, programma.parziali[i], programma.diff_raggiunta[i]);
        for (j=0; j<MAX_EL; j++) {
            if (programma.matrice[i][j]!=-1) printf("%s ", elementi.elenco[programma.matrice[i][j]].nome);
        }
        printf("\n\n");
    }

    return;
}

void Check (Elenco elementi, Programma *programma, Mod m)
{
    int i;

    for (i=0; i<elementi.N; i++) {

        switch (m)
        {
            case m_frontale_indietro:
                if (elementi.elenco[i].ingresso==1 && elementi.elenco[i].uscita==0) {
                    if (elementi.elenco[i].finale==0) elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 4000.0;
                    else elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 2000.0;
                }
                else {
                    if (elementi.elenco[i].finale==0) elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 3000.0;
                    else elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 1000.0;
                }
                break;

            case m_acrobatico:
                if (elementi.elenco[i].tipologia!=0) {
                    if (elementi.elenco[i].finale==0) elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 4000.0;
                    else elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 2000.0;
                }
                else {
                    if (elementi.elenco[i].finale==0) elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 3000.0;
                    else elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 1000.0;
                }
                break;

            case m_acrobatico_avanti:
                if (elementi.elenco[i].tipologia==2) {
                    if (elementi.elenco[i].finale==0) elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 4000.0;
                    else elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 2000.0;
                }
                else {
                    if (elementi.elenco[i].finale==0) elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 3000.0;
                    else elementi.elenco[i].supporto = elementi.elenco[i].punteggio_specifico + 1000.0;
                }
                break;

            case m_punteggio:
                elementi.elenco[i].supporto = elementi.elenco[i].valore;
                break;
        }
    }

    MergeSort(elementi,programma->indici);

    return;
}

int Check_Ultimo (int *v)
{
    int i;

    for (i=(MAX_EL-1); i>=0; i--) {
        if (v[i]!=-1) return i;
    }

    return -1;
}
