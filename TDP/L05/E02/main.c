#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 200
#define Max 30
//struct contennente le ricodifiche del dizionario
typedef struct{
    char parola[N];
    char cod[N];
} Dizionario;
//funzione che carica le sostituzioni nella struct
int carica_dizionario(Dizionario diz[], FILE *fp);


int main()
{
    //dichiarazione variabili
    FILE *sorgente;
    FILE *fp;
    FILE *ricondizionato;
    Dizionario dizionario[Max];
    int i=0,j=0,n=0;
    char word[N];
    char acapo;
    int count = 0, k = 0 , l = 0, m = 0;
    int len_parola = 0, len_word = 0, flag = 0, check = 0;

    n = carica_dizionario(dizionario, fp);

    //apertura dei file
    sorgente= fopen("sorgente.txt","r");
    ricondizionato= fopen("ricondizionato.txt","w");

    while (fscanf(sorgente, "%s", &word) == 1) //lettura del file sorgente parola per parola
    {
        fscanf(sorgente, "%c", &acapo);
        len_parola = strlen(word);  //lunghezza della parola appena letta
        i = 0;
        flag = 0;
        while (i < n && flag == 0)
        {
            len_word = strlen(dizionario[i].parola);    //lunghezza della parola secondo l'indice i della sostituzione presente nel dizionario
            if (len_parola >= len_word) //verifico che la lunghezza della parola della sorgente sia più lunga rispetto alla lunghezza della parola del dizionario
            {
                for (j = 0; j <= len_parola - len_word; j++)
                {
                    l = j;
                    count = 0;
                    check = 0;
                    for (k = 0; k < len_word && check == 0; k++)
                    { 
                        if (word[l] == dizionario[i].parola[k]) //controllo carattere per carattere e in caso di uguaglianza incremento il conteggio per vedere se risulta lungo quanto la lunghezza della parola del dizionario in esame
                            count++;
                        else
                            check = 1;
                        l++;
                    }
                    if (count == len_word)      //se il conteggio risulta uguale alla lunghezza della parola del dizionario stampo la ricodifica
                    {
                        flag = 1;
                        for (m = 0; m < j; m++)
                        {
                            fprintf(ricondizionato, "%c", word[m]);
                        }
                        fprintf(ricondizionato, "%s", dizionario[i].cod);
                        for (m = j + len_word; m < len_parola; m++)
                        {
                            fprintf(ricondizionato, "%c", word[m]);
                        }
                    }
                }
            }
            i++;
        }
        if (flag == 0)      //se non è stata incontarta nessuna uguaglianza si riscrive la parola senza sostituzioni nel file ricondizionato
            fprintf(ricondizionato, "%s", word);
        if (acapo == '\r' || acapo == '\n')
            fprintf(ricondizionato, "\n");
        else
            fprintf(ricondizionato, " ");
    }

    //chiusura dei file
    fclose(ricondizionato);
    fclose(sorgente);
    return 0;
}

int carica_dizionario(Dizionario diz[], FILE *fp)
{
    int n = 0, i = 0;
    fp = fopen("dizionario.txt", "r");
    fscanf(fp, "%d", &n);
    for (i = 0; i < n; i++)     //for per caricare le sostituzioni contenute nel dizionario nella struct
    {
        fscanf(fp, "%s %s", &diz[i].cod, &diz[i].parola);
    }
    fclose(fp); //chiusura file
    return n;
}
