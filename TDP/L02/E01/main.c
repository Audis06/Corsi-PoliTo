#include <stdio.h>

int main() {
    int num1,num2, res=1;
    printf("Inserisci il primo valore: ");
    scanf("%d", &num1);
    printf("Inserisci il secondo valore: ");
    scanf("%d", &num2);
    while(res!=0){
        res=num1%num2;
        if(res!=0){
            num1=num2;
            num2=res;
        }
    }
    printf("MCD: %d", num2);
    return 0;
}
