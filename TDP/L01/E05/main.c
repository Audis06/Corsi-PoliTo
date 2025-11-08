#include <stdio.h>

int main() {
    printf("Inserire l'operazione da eseguire: ");
    char opex=getchar();
    float op1, op2, res;
    printf("Inserire il primo e il secondo operatore dell'operazione: ");
    scanf("%f %f", &op1,&op2);
    switch(opex){
        case '+':
            res=op1+op2;
            break;
        case '-':
            res=op1-op2;
            break;
        case '*':
            res=op1*op2;
            break;
        case '/':
            res=op1/op2;
            break;
    }
    printf("%c %.2f", opex, res);
    return 0;
}
