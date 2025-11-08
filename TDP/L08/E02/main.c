#include <stdlib.h>
#include <stdio.h>

//prototipi delle funzioni
int checkBigEndian(void);
void stampaCodifica(void *p, int size, int bigEndian);

int main()
{
    //dichiarazione variabili
    float af;
    double ad;

    unsigned int af_unsigned;

    //verifico se il sistema è bigEndian o LittleEndian
    int BigEndian = checkBigEndian();

    //stampo il risultato della funzione checkBigEndian
    if (BigEndian == 0)
        printf("Il pc utilizza una codifica LittleEndian.\n");
    else
        printf("Il pc utilizza una codifica BigEndian.\n");

    //stampo le dimensione dei tipi di variabile usando sizeof(..)
    printf("Le dimensioni delle vasiabili af, ad e ald sono:\n");
    printf("\na) af: %d byte, %d bit\n", sizeof(float), sizeof(float) * 8);
    printf("b) ad: %d byte, %d bit\n", sizeof(double), sizeof(double) * 8);

    //inserisco il valore da codificare
    printf("Inserisci ora un valore numerico: ");
    //inserisoc il valore in float e succesiamente casto a double e long double
    scanf("%f", &af);
    ad = (double)af;

    //funzione di codifica
    stampaCodifica((void *)&af, sizeof(af), BigEndian);
    stampaCodifica((void *)&ad, sizeof(ad), BigEndian);
}

//funzione che verifica se il sistema è BigEndian o LittleEndian
int checkBigEndian(void)
{
    int variabile = 1;
    unsigned char *p = (char *)&variabile;

    if (*p == 0)
        return 1;
    else
        return 0;
}

void stampaCodifica(void *p, int size, int bigEndian)
{ // stampo codifica nel caso sia LittleEndian, nel caso fossi BigEndian, inverto il ciclo di stampa

    //dichiarazione variabili
    int i, decodifica[128], resto = 0, j;
    unsigned char *pc;
    pc = (unsigned char *)p;

    //codifico il numero in binario
    for (j = 0; j < size; j++)
    {
        for (i = 0; i < 8; i++)
        {
            resto = (*pc) % 2;
            (*pc) = (*pc) / 2;
            if (resto == 0)
                decodifica[j * 8 + i] = 0;  //moltiplico per 8 perche j rappresenta solo i byte
            else
                decodifica[j * 8 + i] = 1;
        }
        pc++;
    }

    //codifica del numero in float
    if (size == 4)
    {

        printf("Il numero in codifica float e': ");
        for (i = size * 8 - 1; i >= 0; i--)
        {
            printf("%d", decodifica[i]);
        }

        printf("\nIl bit di segno e': %d", decodifica[0]);

        printf("\nI bit di esponente sono: ");
        for (i = 9; i >= 2; i--)
        {
            printf("%d", decodifica[i]);
        }

        printf("\nI bit di mantissa sono: ");
        for (i = size * 8 - 1; i >= 10; i--)
        {
            printf("%d", decodifica[i]);
        }
    }

    //codifica del numero in double
    if (size == 8)
    {

        printf("\n\nIl numero in codifica double e': ");
        for (i = size * 8 - 1; i >= 0; i--)
        {
            printf("%d", decodifica[i]);
        }

        printf("\nIl bit di segno e': %d", decodifica[0]);

        printf("\nI bit di esponente sono: ");
        for (i = 12; i >= 2; i--)
        {
            printf("%d", decodifica[i]);
        }

        printf("\nI bit di mantissa sono: ");
        for (i = size * 8 - 1; i >= 13; i--)
        {
            printf("%d", decodifica[i]);
        }
    }
}
