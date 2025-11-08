#include <stdio.h>
#include <ctype.h>
#include<string.h>

#define filein "expr.txt"
#define MAX 50

void check(FILE *fin);

int main() {
    FILE *fin;
    fin=fopen(filein, "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file\n");
        return 0;
    }

    check(fin);

    fclose(fin);
    return 1;
}

void check(FILE *fin){
    char riga[MAX];
    int n_expr=1, flag=0, len, par_c=0, par_a=0;

    while(fgets(riga,MAX,fin) != NULL){
        len=strlen(riga);
        for(int i=0; i<len && flag==0; i++){
            if(isdigit(riga[i])){
                if(riga[i-1]==')' || riga[i-2]==')')
                    flag=1;
            }
            if(riga[i]==' '){
                if(isdigit(riga[i-1]) && isdigit(riga[i+1])){
                    flag=1;
                }
            }
            if(riga[i]=='+' || riga[i]=='-' || riga[i]=='*' || riga[i]=='/' || riga[i]=='%'){
                if(riga[i-1]=='(' || riga[i+1]==')')
                    flag=3;
                if(riga[i+1]=='\n' || riga[i+2] == '\n')
                    flag=3;
            }
            if(riga[i]=='('){
                par_a++;
            }
            if(riga[i]==')'){
                par_c++;
            }
        }
        if(flag==0) {
            if (par_a != par_c) {
                flag = 2;
            }
        }

        if(flag!=0){
            switch (flag){
                case 1:
                    printf("Errore nella lettura del numero (espressione %d)\n", n_expr);
                    break;
                case 2:
                    printf("Errore nella lettura delle parentesi (espressione %d)\n", n_expr);
                    break;
                case 3:
                    printf("Errore nella lettura dell'operatore aritmetico (espressione %d)\n", n_expr);
                    break;
            }
        }
        n_expr++;
        par_a=0;
        par_c=0;
        flag=0;
    }
}
