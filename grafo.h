#include <stdio.h>
#include <stdlib.h>

// LISTA de ADJACENCIA

typedef struct no 
{
    float vertice;
    float pesoAresta;
    struct no *prox;
}no_t;

typedef struct grafo
{
    int num_vertices;
    no_t *VETOR_list_adj;
}grafo_t;


grafo_t *criaGRAFO(int n, float *vertices);
no_t *criaNO(float v, float peso);
void addAresta(grafo_t *grafo, int origem, int dest, float peso);
void mostraGrafo(grafo_t *grafo);
void destroiGRAFO(grafo_t* grafo);
float **criaMatriz(int total_linha, int total_coluna, int valor);
float **dijkstra(grafo_t* grafo, int vertice);
float peso(grafo_t* grafo, float origem, float destino);
