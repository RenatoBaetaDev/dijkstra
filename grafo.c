#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

// LISTA DE ADJ

grafo_t *criaGRAFO(int n, float *vertices)
{
    int i;
    grafo_t *grafo = (grafo_t*) malloc (sizeof(grafo_t));
    if (!grafo){
        printf("[ERRO FATAL]: Incapaz de Alocar Memoria para o Grafo \n Saindo.. \n");
        exit(EXIT_FAILURE);
    }

    grafo->num_vertices = n;
    grafo->VETOR_list_adj = (no_t*) malloc (n * sizeof(no_t));
    if (!grafo->VETOR_list_adj){
        printf("[ERRO FATAL]: Incapaz de Alocar Memoria para o Vetor de Lista Adjacente \n Saindo.. \n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < n; i++)
    {
        grafo->VETOR_list_adj[i].vertice = vertices[i];
        grafo->VETOR_list_adj[i].prox = NULL;
    }
    
    return grafo;
}


no_t *criaNO(float v, float peso)
{
    no_t *novoNO = (no_t*) malloc (sizeof(no_t));
    if (!novoNO){
        printf("[ERRO FATAL]: Incapaz de Alocar Memoria para um Novo No \n Saindo.. \n");
        exit(EXIT_FAILURE);        
    }

    novoNO->vertice = v;
    novoNO->pesoAresta = peso;
    novoNO->prox = NULL;
    return novoNO;
}


void addAresta(grafo_t *grafo, int origem, int dest, float peso)
{

    for (int i = 0; i < grafo->num_vertices; i++)
    {
        if (origem == grafo->VETOR_list_adj[i].vertice )
        {
            no_t *novoNO = criaNO(dest, peso);
            novoNO->prox = grafo->VETOR_list_adj[i].prox;
            grafo->VETOR_list_adj[i].prox = novoNO;
        }

        if (dest == grafo->VETOR_list_adj[i].vertice )
        {
            no_t *novoNO = criaNO(origem, peso);
            novoNO->prox = grafo->VETOR_list_adj[i].prox;
            grafo->VETOR_list_adj[i].prox = novoNO;            
        }

    }    

    
    // no_t *novoNO = criaNO(dest);
    // novoNO->prox = grafo->VETOR_list_adj[origem].prox;
    // grafo->VETOR_list_adj[origem].prox = novoNO;


    // novoNO = criaNO(origem);
    // novoNO->prox = grafo->VETOR_list_adj[dest].prox;
    // grafo->VETOR_list_adj[dest].prox = novoNO;

}


void mostraGrafo(grafo_t *grafo)
{
    int i;
    printf("VERT - DIST - VERT \n\n");
    for (i = 0; i < grafo->num_vertices; i++)
    {
        no_t *Atual = grafo->VETOR_list_adj[i].prox;
        while (Atual)
        {            
            printf("[%.1f] - ", grafo->VETOR_list_adj[i].vertice);        
            printf("%.1f - ", Atual->pesoAresta);        
            printf("[%.1f] \n", Atual->vertice);        
            Atual = Atual->prox;
        }   
        printf("\n")     ;
    }
}


void destroiGRAFO(grafo_t* grafo)
{
    if(grafo)
    {
        if(grafo->VETOR_list_adj)
        {
            int v;
            for(v = 0; v < grafo->num_vertices; v++)
            {
                no_t *Atual = grafo->VETOR_list_adj[v].prox;
                while (Atual)
                {
                    no_t *tmp = Atual;
                    Atual = Atual->prox;
                    free(tmp);
                }
            }
            free(grafo->VETOR_list_adj);            
        }
        free(grafo);
    }
}

float **criaMatriz(int total_linha, int total_coluna, int valor){
	int linha, coluna;
	float **matriz = (float **) malloc (total_coluna * sizeof(float *));
	for (linha = 0; linha < total_linha; linha++)
		matriz[linha] = (float *) malloc (total_coluna * sizeof(float));

	for (linha = 0; linha < total_linha; linha++)
		for (coluna = 0; coluna < total_coluna; coluna++)
			matriz[linha][coluna] = valor;

	return matriz;
}

float peso(grafo_t* grafo, float origem, float destino)
{
    if (origem == destino)
        return 0;

    int i;
    for (i = 0; i < grafo->num_vertices; i++)
    {
        if ( grafo->VETOR_list_adj[i].vertice == origem)
        {
            no_t *Atual = grafo->VETOR_list_adj[i].prox;
            while (Atual)
            {       
                if (Atual->vertice == destino)     
                    return Atual->pesoAresta;      
                Atual = Atual->prox;
            }   
        }
    }
    return 9999999;
}

float ** dijkstra(grafo_t* grafo, int vertice)
{

    int qtdeDeNos = grafo->num_vertices+1;
    int linhas = 2;
    int paiVertice = 0;
    int distVertice = 1;

    float **matriz  = criaMatriz(linhas, qtdeDeNos, 0);    //Matriz para armazenar o pai do vertice atual, e a distancia da origem ate o vertice atual
       
    int v;

    for (int i = 0; i < grafo->num_vertices; i++)
    {
        float teste = grafo->VETOR_list_adj[i].vertice;
        matriz[distVertice][(int)teste] = peso(grafo, vertice, teste);
        matriz[paiVertice][(int)teste] = 0;        
    } 

    matriz[distVertice][vertice] = 0;

    for (int i = 0; i < linhas; i++){
        for (int z = 1; z <qtdeDeNos; z++)
            printf("%.1f ", matriz[i][z]);
        printf("\n");
    }    

    Fila *Q = criaFila(); //Distancia provisoria
    Fila *S = criaFila(); //Distancia definitiva

    for (int i = 0; i < grafo->num_vertices; i++)
    {
        float teste = grafo->VETOR_list_adj[i].vertice;
        Q = insere(Q, teste, peso(grafo, vertice, teste));
    }

    imprimeFila(Q);

    heapSortTeste(Q);

    imprimeFila(Q);

    while( !vaziaFila(Q) )    
    {
        int salame =  retira(Q); 
        S = insere(S, salame, matriz[distVertice][salame]);

        for (int i = 0; i < grafo->num_vertices; i++)
        {            
            if ( grafo->VETOR_list_adj[i].vertice == salame)
            {
                printf("No atual %d \n", salame);
                no_t *Atual = grafo->VETOR_list_adj[i].prox;
                while (Atual)
                {       
                    if (Atual->vertice != vertice)
                    {
                        float distAtual = matriz[distVertice][(int)Atual->vertice];
                        float distPai = matriz[distVertice][salame];
                        // float pesoAtual = peso(grafo, salame, Atual->vertice);
                        float pesoAtual = peso(grafo, salame, Atual->vertice);

                        printf("No atual %.1f \n", Atual->vertice);
                        printf("dist Atual %.1f \n", distAtual);
                        printf("dist Pai %.1f \n", distPai);
                        printf("peso aresta %.1f \n", pesoAtual);

                        if ( distAtual > ( distPai + pesoAtual ) )
                        {
                            alteraPesoVertice(Q, Atual->vertice, distPai + pesoAtual);
                            matriz[distVertice][(int)Atual->vertice] = distPai + pesoAtual;
                            matriz[paiVertice][(int)Atual->vertice] = salame;
                        }   
                    }                 
                    Atual = Atual->prox;
                }              
            }
        }  

    }

    imprimeFila(S);

    for (int i = 0; i < linhas; i++){
        for (int z = 1; z <qtdeDeNos; z++)
            printf("%.1f ", matriz[i][z]);
        printf("\n");
    }

    return matriz;  
        
}