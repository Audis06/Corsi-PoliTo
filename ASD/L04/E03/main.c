#include <stdio.h>
#include <stdlib.h>
#define N 4

int disp_ripet(int pos, int *dispGemme, int *sol, int n, int k, int prec);


int main(void){
  int  i, s, k, numGemme[N], dispGemme[N], maxlun, bestlun, numtestset, min, max, flen=0;
  char gemme[N] = {'Z', 'R', 'T', 'S'};
  int *sol;
  int scelta=0;
  char *fileName;
  //Scelta da parte del utente di quale file aprire
  printf("Vuoi aprire il file di superfacile, facile, medio o difficile livello(1,2,3,4)?\n");
  scanf("%d",&scelta);
  switch(scelta)
  {
    case 1:
    fileName="very_very_easy_test_set.txt";
    break;
    case 2:
    fileName="very_easy_test_set.txt";
    break;
    case 3:
    fileName="easy_test_set.txt";
    break;
    case 4:
    fileName="hard_test_set.txt";
    break;
    default:
    printf("Errore\n");
    break;
  }
  FILE *in = fopen(fileName, "r");
  if (in == NULL)
    return 0;

  fscanf(in, "%d", &numtestset);
  for (s=0; s<numtestset; s++) {
    printf("Test set #%d\n", s+1);
    min = 0;
    maxlun = 0;
    for (i=0; i<N; i++) {
      fscanf(in, "%d", &numGemme[i]);
      maxlun += numGemme[i];
    }
    max = maxlun;
    sol = malloc((maxlun) * sizeof(int));

    while (min <= max) {
      k = min + (max-min)/2;
      for (i=0; i<N; i++)
        dispGemme[i]=numGemme[i];
      if (disp_ripet(0, dispGemme, sol, N, k, -1)) {
        bestlun = k;
        min = k+1;
      } else {
        max = k-1;
      }
     }
    //Stampa delle soluzioni
    printf("Una soluzione a lunghezza massima %d e' \n",bestlun);
    for (i=0; i<bestlun; i++)
      printf("%c ", gemme[sol[i]]);
    printf("\n");

    free(sol);
  }
  fclose(in);
  return 0;
}


int disp_ripet(int pos, int *dispGemme, int *sol, int n, int k, int prec) {
  int i;
  if (pos >= k) {
    return 1;
  }

  for (i = 0; i < n; i++){
    //verifica delle condizioni
    if (dispGemme[i]>0) {
      if (prec != -1) {
        if (((sol[prec]==0) || (sol[prec]==2)) && (i!=0) && (i!=1))
          continue;
        if (((sol[prec]==3) || (sol[prec]==1)) && (i!=2) && (i!=3))
          continue;
      }
      dispGemme[i]--;
      sol[pos] = i;
      if (disp_ripet(pos+1, dispGemme, sol, n, k, pos))
        return 1;
      dispGemme[i]++;
    }
  }
  return 0;
}

