#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "invArray.h"
#include "pg.h"
#include "pgList.h"

void menu();

int main()
{
    int continua=1,c;
    char codiceRicerca[LEN];

    pgList_t pgList = pgList_init();
    invArray_t invArray = invArray_init();
    pg_t *pgp, pg;

    equipArray_t x=equipArray_init();

    pgList_read("pg.txt", pgList);

    invArray_read("inventario.txt", invArray);

    printf("Elenco personaggi:\n");
    pgList_print(stdout, pgList, invArray);

    printf("Inventario:\n");
    invArray_print(stdout, invArray);
    //Menù
    while(continua){
        menu();
        //Scelta operazione da eseguire
        printf("Inserisci codice comando da eseguire: ");
        scanf("%d",&c);
        printf("\n");
        switch(c){
            case 1:
                //stampa dell'elenco della lista di pg
                printf("Elenco personaggi:\n");
                pgList_print(stdout, pgList, invArray);
                break;
            case 2:
                //stampa del inventario
                printf("Inventario:\n");
                invArray_print(stdout, invArray);
                break;
            case 3:
                //Aggiunta di un pg da tastiera
                pgList_add(pgList);
                break;
            case 4:
                //Rimozione di un pg dalla lista
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgList_remove(pgList, codiceRicerca);
                break;
            case 5:
                //Modifica del equipaggiamento
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgp = pgList_searchByCode(pgList, codiceRicerca);
                if (pgp!=NULL) {
                    pg_updateEquip(pgp, invArray);
                }
                break;
            case 6:
                //Ricerca in lista ordinata e stampa delle statistiche di uno specifico pg
                printf("Inserire codice personaggio: ");
                scanf("%s", codiceRicerca);
                pgp = pgList_searchByCode(pgList, codiceRicerca);
                if (pgp!=NULL) {
                    pg_print(stdout, pgp, invArray);
                }
                break;
            case 7:
                //Fine ed uscita dal menù
                continua=0;
                break;
            default:
                printf("Comando errato\n");
        }
    }
    //Deallocazione dello spazio occupato dalla lista e dagli oggetti
    pgList_free(pgList);
    equipArray_free(x);
    invArray_free_wrapper(invArray,pgList);
    return 0;
}

void menu(){
//Menu
    printf("Menu:\n");
    printf("1. Stampa della lista aggiornata");
    printf("\n");
    printf("2. Stampa del inventario");
    printf("\n");
    printf("3. Aggiungi personaggio alla lista da tastiera");
    printf("\n");
    printf("4. Elimina personaggio dalla lista");
    printf("\n");
    printf("5. Modifica equipaggiamento");
    printf("\n");
    printf("6. Ricerca e stampa di un personaggio");
    printf("\n");
    printf("7. fine");
    printf("\n");
}
