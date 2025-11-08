#include <stdio.h>


int main() {
    FILE *fp;
    char file[20];
    int max=0,pr=0,pc=0,sum=0,min=0;
    int nr=0,nc=0,dim=0,i=0,j=0,k=0,y=0;

    printf("Inserisci il nome del file: ");
    scanf("%s", &file);
    fp=fopen(file,"r");
    if(fp==NULL){
        printf("Errore nell'apertura del file\n");
        return 1;
    }

    fscanf(fp,"%d %d", &nr,&nc);

    int mat[nr][nc];
    int max_m[nr][nc];

    for(i=0; i<nr;i++){
        for(j=0; j<nc;j++){
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
    min=nc;
    if(nr<min)
        min=nr;

    printf("Inserire un valore tra 1 e %d: ",min);
    scanf("%d",&dim);
    while(dim<1 && dim>min){
        printf("Valore non valido, inserire di nuovo: ");
        scanf("%d", &dim);
    }

    printf("Le sottomatrici quadrate di dimensione %d sono:\n",dim);

    for(i=0; i<nr+1-dim;i++){
        sum=0;
        for(j=0;j<nc+1-dim;j++){
            sum=0;
            for(k=i;k<dim+i;k++){
                for(y=j; y<dim+j;y++){
                    printf("%d ",mat[k][y]);
                    sum+=mat[k][y];
                }
                printf("\n");
            }
            printf("\n");
            if(sum>max){
                max=sum;
                pr=k-dim;
                pc=y-dim;
            }
        }
    }

    printf("La sottomatrice con somma degli elementi massima (%d) è: \n\n",max);
    for(i=pr; i<pr+dim;i++){
        for(j=pc; j<pc+dim;j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}
