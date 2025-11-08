#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pgList.h"

typedef struct nodoPg_s {
  pg_t pg;
  struct nodoPg_s *next;
} nodoPg_t, *linkPg;

struct pgList_s {
  linkPg head, tail;
  int nPg;
};

//Funzione statica visibile solo all'interno del nodo
static linkPg newNodoPg(pg_t pg, linkPg next);
//Iniziazione della lista
pgList_t pgList_init() {
    pgList_t pgList = calloc(1, sizeof(*pgList));
    return pgList;
}
//Lettura e inserimento tramite la pgList_insert dei pg in lista
void pgList_read(char *filename, pgList_t pgList) {
    pg_t pg;
    FILE *fp = fopen(filename, "r");
    //controlli sulla lista e sul file
    if (pgList == NULL)
        return;
    if (fp == NULL)
        return;
    //Letura tramite la pg_read delle informazioni del pg
    while((pg_read(fp, &pg)) != 0) {
        pgList_insert(pgList, pg);  //Inserimento in lista
        pgList->nPg++;  //Aumento del numero di pg presenti in lista
    }

    fclose(fp);
}
//Inserimento dei nuovi pg in lista con le informazioni prese da pg_read
void pgList_insert(pgList_t pgList, pg_t pg) {
    linkPg toAdd;
    //creazione di un nuovo nodo della lista tramite la funzione newNodoPg
    toAdd = newNodoPg(pg, NULL);
    if (toAdd == NULL || pgList == NULL)
        return;
    //controlo in che posizione inserire il nuovo nodo.. se la lista è vuota (head==NULL) si inserisce il nuovo nodo in prima posizione
    if(pgList->head == NULL)
        pgList->head = pgList->tail = toAdd;
    //Inserimento in coda se la lista non è vuota
    else {
        pgList->tail->next = toAdd;
        pgList->tail = toAdd;
    }
}
//creazione dei nuovi nodi
static linkPg newNodoPg(pg_t pg, linkPg next) {
  //Allocazione dinamica di un nuovo nodo
  linkPg n = calloc(1, sizeof(*n));
  if (n == NULL)
    return NULL;
  n->pg = pg;
  n->next = next;
  return n;
}
//stampa della lista tramitre la funzione pg_print nel modulo pg.c
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
  linkPg iter = NULL;
  if (pgList == NULL)
    return;
  for(iter=pgList->head; iter!=NULL; iter=iter->next)
    pg_print(fp, &iter->pg, invArray);
}
//Ricerca in lista del codice inserito da tastiera
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
  linkPg iter = NULL;
  if (pgList == NULL)
    return NULL;
  for(iter = pgList->head; iter != NULL; iter=iter->next) {
    if (strcmp(iter->pg.cod, cod) == 0) {
      return (&iter->pg);
    }
  }
  return NULL;
}
//Funzione wrapper per l'inserimento di un nuovo pg da tastiera
void pgList_add(pgList_t pgList){
  pg_t pg;
  printf("Cod Nome Classe HP MP ATK DEF MAG SPR: ");
  //Utilizzo della funzione pg_read nel modulo pg.c per leggere da tastiera le info di un nuovo pg
  if (pg_read(stdin, &pg) != 0) {
    //Inserimento del nuovo pg in lista
    pgList_insert(pgList, pg);
  }
}
//Funzione per rimozione di un pg dalla lista
void pgList_remove(pgList_t pgList_t, char* cod){
  linkPg iter, prev;
  //Scorrimento della lista dall'head
  for(iter = pgList_t->head, prev = NULL; iter != NULL; prev = iter, iter=iter->next) {
    //Ricerca del codice in lista
    if (strcmp(iter->pg.cod, cod) == 0) {
      //Ricerca in che posizione si trova
      if (iter == pgList_t->head && iter == pgList_t->tail) {
        pgList_t->head = pgList_t->tail = NULL;
      } else if (iter == pgList_t->head) {
        pgList_t->head = iter->next;
      } else if (iter == pgList_t->tail) {
        pgList_t->tail = prev;
        prev->next = NULL;
      } else {
        prev->next = iter->next;
      }
      pg_clean(&iter->pg);
      free(iter);
      break;
    }
  }
}
//deallocazione dello spazio occupato dalla lista
void pgList_free(pgList_t pgList) {
  linkPg iter, next;
  for(iter = pgList->head; iter != NULL; iter=next) {
    next = iter->next;
    pg_clean(&iter->pg);
    free(iter);
  }
}
//Funzione wrapper per la dealloxazione di invArray
void invArray_free_wrapper(invArray_t invArray, pgList_t pgList){
    linkPg y, next;
    for(y=pgList->head; y!=NULL; y=next)
        invArray_free(invArray);
}
