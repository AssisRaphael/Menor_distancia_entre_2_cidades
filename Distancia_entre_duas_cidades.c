#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define infinito 99999998

int ** Aloca_matriz(int **matriz, int lin, int col){
    matriz = (int **) malloc(sizeof(int *) * lin);
    for(int i = 0; i < lin; i++)
        matriz[i] = (int *) malloc(sizeof(int) * col);
    return matriz;
}

int main(){

    FILE * fp, *fv;
    char arquivo[100];
    int n, i, j, N, pesoCidades,na,nb;
    int **matriz = NULL;
    char **cidades;
    char A[21], B[21], a[21], b[21];
    int nA, nB, menor, u, Terminou, cont,repetida;
    int *d, *p, *aberto, *caminho;

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s",arquivo);

    //Abre o arquivo para leitura
    fp = fopen(arquivo,"r");
        if(fp==NULL){
            printf("\nErro ao abrir Arquivo\n");
            exit(404);
    }

    fscanf(fp,"%d",&n);//le o numero de estradas

    cidades = (char **) malloc(sizeof(char *)*2);//aloca o vetor de nomes das cidades
     for( i = 0; i < 2; i++){//aloca 2 cidades
        cidades[i] = (char *) malloc(sizeof(char) * 21); //Aloca 21 espaços para cada nome
     }
     cont = 2;
     fscanf(fp,"%s %s %d",cidades[0],cidades[1],&pesoCidades);

    for(i = 1 ; i < n ; i++){//Descobre o número correto de cidades (cont) e salva os nomes das cidades
                fscanf(fp,"%s %s %d",a,b,&pesoCidades);
                repetida = 0;
                for(j = 0 ; j < cont ; j++){//verifica se a cidade a é repetida
                    if(strcmp(a,cidades[j])==0){
                        repetida = 1;
                        break;
                    }
                }
                if(repetida==0){//Aloca a cidade a no vetor cidades se não for repetida
                    cont+=1;
                    cidades = (char **) realloc(cidades,sizeof(char *)*cont);//aloca o vetor de nomes das cidades
                    cidades[cont-1] = (char *) malloc(sizeof(char) * 21); //Aloca 21 espaços para cada nome
                    strcpy(cidades[cont-1] ,a);
                }

                repetida = 0;

                for(j = 0 ; j < cont ; j++){//verifica se a cidade b é repetida
                    if(strcmp(b,cidades[j])==0){
                        repetida = 1;
                        break;
                    }
                }
                if(repetida==0){//Aloca a cidade b no vetor cidades se não for repetida
                    cont+=1;
                    cidades = (char **) realloc(cidades,sizeof(char *)*cont);//aloca o vetor de nomes das cidades
                    cidades[cont-1] = (char *) malloc(sizeof(char) * 21); //Aloca 21 espaços para cada nome
                    strcpy(cidades[cont-1] ,b);
                }
    }

     N = cont;// N recebe o numero correto de cidades
    fscanf(fp,"%s %s",A,B);
    //printf("\n%s %s\n",A,B);


    matriz = Aloca_matriz(matriz, N, N);//aloca a matriz de cidades
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            matriz[i][j]=0;

    d = (int *) malloc(sizeof(int) * N); //Aloca o vetor de estimativas
    p = (int *) malloc(sizeof(int) * N); //Aloca o vetor de vértices pai
    aberto = (int *) malloc(sizeof(int) * N); //Aloca o vetor de visitas
    caminho = (int *) malloc(sizeof(int) * N); //Aloca o caminho desejado

    fclose(fp);//fecha o arquivo

    //Abre o arquivo para leitura
    fv = fopen(arquivo,"r");
        if(fv==NULL){
            printf("\nErro ao abrir Arquivo\n");
            exit(404);
    }

    fscanf(fv,"%d",&n);//le o numero de estradas

    for(i=0;i<N;i++){//encontra a posição das cidades A e B na matriz
        if(strcmp(A,cidades[i])==0)
            nA = i;
        if(strcmp(B,cidades[i])==0)
            nB = i;
    }

    //Lê as cidades e distâncias do arquivo
    for(i=0;i<n;i++){
                   fscanf(fv,"%s %s %d",a,b,&pesoCidades);//Lê o arquivo
                   //printf("%s %s %d\n",a,b,pesoCidades);
                   for(j = 0 ; j < N ; j++){//Aloca a cidade a no vetor cidades
                        if(strcmp(a,cidades[j])==0)
                            na = j;
                        if(strcmp(b,cidades[j])==0)
                            nb = j;
                    }
                   matriz[na][nb] = pesoCidades;
                   matriz[nb][na] = pesoCidades;

    }


    for(i = 0 ; i < N ; i++){
            d[i] = infinito;
            p[i] = -1;
            aberto[i] = 1;
            caminho[i] = -1;
    }

    d[nA] = 0; //Estimativa da cidade de destino é zero

    fclose(fv);
    //Inicia o algoritmo dijkstra
    for(Terminou = 0;Terminou < N+1; Terminou++){

            menor = infinito+1;

                for(i=0;i<N;i++) //Seleciona a cidade com menor estimativa que esteja aberta
                    if(aberto[i] && d[i]<menor){
                        menor = d[i];
                        u = i;
                    }

                    aberto[u] = 0;

                    for(i=0;i<N;i++){ //Relaxamento para todas as cidades adjacentes a u
                            if(matriz[u][i]>0 && d[u] + matriz[u][i] < d[i]){
                                d[i] = d[u] + matriz[u][i];
                                p[i] = u;
                            }
                    }
    }


    i = 0;
    int aux = nB;
    do{
        caminho[i] = aux;
        aux = p[aux];
        i++;//proxima posição do vetor caminho
    }while(aux != nA);

    printf("Menor percurso: ");
    //printf("caminho : ");
    printf("%s",cidades[nA]);
    for(j=i-1;j>=0;j--)
        printf(" %s",cidades[caminho[j]]);

    printf("\nDistancia total: %d Km\n",d[nB]);

    return 0;
}
