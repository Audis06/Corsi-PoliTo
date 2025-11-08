#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXRIGHE 1000
#define MAXSTR 31
#define N_C 6

typedef struct
{
    int a;
    int m;
    int g;
} data_struct;

typedef struct
{
    int h;
    int min;
    int s;
} ora_struct;

typedef struct
{
    char codice_tratta[MAXSTR];
    char partenza[MAXSTR];
    char destinazione[MAXSTR];
    char data_s[MAXSTR];
    char ora_p[MAXSTR];
    char ora_a[MAXSTR];
    int ritardo;
    data_struct data;
    ora_struct p, a;
} dati;

typedef struct
{
    int n;
    dati log[MAXRIGHE];
} tabella;

typedef enum
{
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
    r_fine
} comando_e;

tabella leggitabella();
comando_e leggicomando(char comandi[][MAXSTR]);
void stampacomandi(char comandi[][MAXSTR]);
void selezionadati(tabella tab, comando_e cmd);

int main()
{
    int continua = 1;
    char comandi[][MAXSTR] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    comando_e cmd;
    tabella tab;
    tab = leggitabella();
    stampacomandi(comandi);
    do
    {
        cmd = leggicomando(comandi);
        switch (cmd)
        {
        case r_date:
            selezionadati(tab, r_date);
            break;
        case r_partenza:
            selezionadati(tab, r_partenza);
            break;
        case r_capolinea:
            selezionadati(tab, r_capolinea);
            break;
        case r_ritardo:
            selezionadati(tab, r_ritardo);
            break;
        case r_ritardo_tot:
            selezionadati(tab, r_ritardo_tot);
            break;
        case r_fine:
            continua = 0;
            break;
        default:
            stampacomandi(comandi);
        }
    } while (continua);

    return 0;
}

tabella leggitabella()
{
    int i;
    tabella tab;
    FILE *fp;
    fp = fopen("log.txt", "r");
    if (fp == NULL)
        exit(-1);
    fscanf(fp, "%d", &tab.n);
    for (i = 0; i < tab.n; i++)
    {
        fscanf(fp, "%s %s %s %s %s %s %d\n", tab.log[i].codice_tratta, tab.log[i].partenza, tab.log[i].destinazione, tab.log[i].data_s, tab.log[i].ora_p, tab.log[i].ora_a, &tab.log[i].ritardo);
        sscanf(tab.log[i].data_s, "%d/%d/%d", &tab.log[i].data.a, &tab.log[i].data.m, &tab.log[i].data.g);
        sscanf(tab.log[i].ora_p, "%d:%d:%d", &tab.log[i].p.h, &tab.log[i].p.min, &tab.log[i].p.s);
        sscanf(tab.log[i].ora_a, "%d:%d:%d", &tab.log[i].a.h, &tab.log[i].a.min, &tab.log[i].a.s);
    }
    return tab;
}

comando_e leggicomando(char comandi[][MAXSTR])
{
    comando_e i;
    char cmd[MAXSTR];
    printf("Comando:");
    scanf("%s", cmd);
    for (i = 0; i < N_C; i++)
    {
        if (strcmp(cmd, comandi[i]) == 0)
            return i;
    }
    return -1;
}

void stampacomandi(char comandi[][MAXSTR])
{
    int i;
    printf("Comandi disponibili:\n");
    for (i = 0; i < N_C; i++)
    {
        printf("%s", comandi[i]);
        printf("\n");
    }
}

int confrontadate(data_struct d1, data_struct d2)
{
    if (d1.a != d2.a)
        return (d1.a - d2.a);
    else if (d1.m != d2.m)
        return (d1.m - d2.m);
    else if (d1.g != d2.g)
        return (d1.g - d2.g);
    else
        return 0;
}

void stampadati(dati dat)
{
    printf("La tratta (%s) da %s a %s del %s (dalle %s alle %s) e' in ritardo di %d\n", dat.codice_tratta, dat.partenza,
           dat.destinazione, dat.data_s, dat.ora_p, dat.ora_a, dat.ritardo);
}
void selezionadati(tabella tab, comando_e cmd)
{
    data_struct d1, d2;
    char istruzione[MAXSTR];
    int i, ritardo_totale = 0, check=0;
    if (cmd == r_date)
    {
        printf("Inserire prima data (aaaa/mm/gg): ");
        scanf("%d/%d/%d", &d1.a, &d1.m, &d1.g);
        printf("Inserisci seconda data (aaaa/mm/gg): ");
        scanf("%d/%d/%d", &d2.a, &d2.m, &d2.g);
    }
    else if (cmd == r_partenza)
    {
        printf("Inserire luogo di partenza: ");
        scanf("%s", istruzione);
        istruzione[0] = toupper(istruzione[0]);
    }
    else if (cmd == r_capolinea)
    {
        printf("Inserire capolinea: ");
        scanf("%s", istruzione);
    }
    else if (cmd == r_ritardo)
    {
        printf("Inserire prima data (aaaa/mm/gg): ");
        scanf("%d/%d/%d", &d1.a, &d1.m, &d1.g);
        printf("Inserisci seconda data (aaaa/mm/gg): ");
        scanf("%d/%d/%d", &d2.a, &d2.m, &d2.g);
    }
    else if (cmd == r_ritardo_tot)
    {
        printf("Inserisci codice della tratta: ");
        scanf("%s", istruzione);
        for (i = 0; i < 3; i++)
            istruzione[i] = toupper(istruzione[i]);
    }
    for (i = 0; i < tab.n; i++)
    {
        switch (cmd)
        {
        case r_date:
            if (confrontadate(d1, tab.log[i].data) <= 0 && confrontadate(d2, tab.log[i].data) >= 0)
                stampadati(tab.log[i]);
            break;
        case r_partenza:
            if (!strcmp(tab.log[i].partenza, istruzione)) {
                check=1;
                stampadati(tab.log[i]);
            }
            break;
        case r_capolinea:
            if (!strcmp(tab.log[i].destinazione, istruzione)) {
                check=1;
                stampadati(tab.log[i]);
            }
            break;
        case r_ritardo:
            if (confrontadate(d1, tab.log[i].data) <= 0 && confrontadate(d2, tab.log[i].data) >= 0 && tab.log[i].ritardo > 0)
                stampadati(tab.log[i]);
            break;
        case r_ritardo_tot:
            if (!strcmp(tab.log[i].codice_tratta, istruzione))
                ritardo_totale += tab.log[i].ritardo;
            break;
        default:
            printf("Errore");
        }
    }
    if(cmd==r_partenza || cmd==r_capolinea) {
        if (check == 0)
            printf("Errore nell'inserimento del nome della fermata\n");
    }

    if (cmd == r_ritardo_tot)
        printf("Il ritardo totale e' %d\n", ritardo_totale);
}
