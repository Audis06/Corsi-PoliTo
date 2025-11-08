#include <stdio.h>

int main() {
    FILE *fp_read, *fp_out;
    if ((fp_read = fopen("input.txt", "r")) == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    if ((fp_out = fopen("output.txt", "w")) == NULL) {
        printf("Error opening file\n");
        return 2;
    }

    char opex;
    float op1, op2, res;

    while(fscanf(fp_read,"%c %f %f", &opex, &op1, &op2)!=EOF)
    {
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
    if(opex!='\n')
        fprintf(fp_out,"%c %.2f\n", opex, res);
    }

    fclose(fp_read);
    fclose(fp_out);
    return 0;
}
