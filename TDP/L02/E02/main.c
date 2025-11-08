#include <stdio.h>

int main() {
    int n;
    int x[100];
    int X;
    x[0]=0;
    x[1]=1;
    printf("Inserisci il valore di N: ");
    scanf("%d",&n);

    for(int i=0; i<n; i++){
        if(i>1){
            X=x[i-1]+x[i-2];
            x[i]=X;
        }
    }
    for(int i=0; i<n; i++){
        printf("%d ", x[i]);
    }

    return 0;
}
