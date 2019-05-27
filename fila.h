#include <stdio.h>
#include <stdlib.h>

// FILA

//estruta que define os valores do Nos da fila
typedef struct noFila
{
	int vert;
	float dist;
	struct noFila* prox;
}No;

//estrutura fila que armazena o primeiro e o ultimo valor inseridos na fila
typedef struct fila{
	No* ini;
	No* fim;
}Fila;

Fila* criaFila(void);
Fila* insere(Fila* f, int vert, float dist);
int retira(Fila* f);
// No *retira(Fila* f);
int vaziaFila(Fila* f);
void liberaFila(Fila *f);
void imprimeFila(Fila *f);

void criaHeap(int* vet, int inicio, int fim);
void heapSort(int* vet, int n);

void criaHeapTeste(Fila *f, int i, int tamanho);
void heapSortTeste(Fila* f);

void alteraPesoVertice(Fila *f, int vert, float peso);