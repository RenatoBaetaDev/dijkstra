#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* criaFila(void){
	Fila *f = (Fila*) malloc (sizeof(Fila));
	f->ini = f->fim = NULL;
	return f;
}

Fila* insere(Fila* f, int vert, float dist){
	No* novo = (No*) malloc (sizeof(No));
	novo->vert = vert;
	novo->dist = dist;
	novo->prox = NULL;
	if(f->fim != NULL)
		f->fim->prox = novo;
	f->fim = novo;
	if (f->ini==NULL)
		f->ini = f->fim;
	return f;
}

// No *retira(Fila* f){
// 	No* novo;

// 	printf("%d", f->ini->vert);

// 	if (vaziaFila(f))
// 	{
// 		printf("Fila Vazia.\n");
// 		exit(1);
// 	}
// 	novo->vert = f->ini->vert;
// 	novo->dist = f->ini->dist;
// 	No* p = f->ini->prox;
// 	free(f->ini);
// 	f->ini = p;
// 	if (f->ini == NULL)
// 		f->fim = NULL;
// 	return novo;
// }

int retira(Fila* f){
	int v;
	if (vaziaFila(f))
	{
		printf("Fila Vazia.\n");
		exit(1);
	}
	v = f->ini->vert;
	No* p = f->ini->prox;
	free(f->ini);
	f->ini = p;
	if (f->ini == NULL)
		f->fim = NULL;
	return v;
}

int vaziaFila(Fila* f){
	return (f->ini==NULL);
}

void liberaFila(Fila *f){
	No* q = f->ini;
	while(q!=NULL)
	{
		No *t = q->prox;
		free(q);
		q = t;
	}

	free(f);
}

void imprimeFila(Fila *f){
	printf("Imprimindo Fila!\n");
	No *q;
	for (q = f->ini; q!= NULL; q= q->prox)
	{
		printf("%d\n", q->vert);
		printf("%.1f\n", q->dist);
	}
}


void criaHeap(int* vet, int inicio, int fim)
{
    int aux = vet[inicio];
    int filho = inicio * 2 + 1;

    while (filho <= fim) //tem filho?
    {   
        if (filho < fim) //tem dois filhos?
            if (vet[filho] < vet[filho + 1]) //pega o maior dos dois filhos
                filho = filho + 1;


        if ( aux < vet[filho] )     //se o filho maior que o pai
        {
            vet[inicio] = vet[filho];   
            inicio = filho;
            filho = 2 * inicio + 1;
        }
        else 
            filho = filho + 1;
    }

    vet[inicio] = aux;
}

void heapSort(int* vet, int n)
{
    int i, aux;

    for (i = (n - 1) / 2; i >= 0; i--)    
        criaHeap(vet, i, n-1);

    for (i = n - 1; i >= 1; i--)
    {
		
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;

		criaHeap(vet, 0, i - 1);
    }
    
}

void criaHeapTeste(Fila *f, int inicio , int fim)
{
	No *q, *noInicio;
	int atual = 0;	
	float auxDist, auxVert, filhoDist, filhoVert, inicioDist, inicioVert, filhoProxDist;

	int filho = inicio * 2 + 1 ;

	for (q = f->ini; q!= NULL; q= q->prox)
	{
		if ( atual == inicio)
		{
			auxDist = q->dist;
			auxVert = q->vert;
		}
		atual += 1;	
	}	

    while (filho <= fim) //tem filho?
	{		
		atual = 0;
		for (q = f->ini; q!= NULL; q= q->prox)
		{
			if  (atual == filho)
			{
				filhoDist = q->dist;
				filhoVert = q->vert;
				filhoProxDist = q->prox->dist;
				break;
			}
			atual++;	
		}

		atual = 0;
		for (q = f->ini; q!= NULL; q= q->prox)
		{
			if  (atual == inicio)
			{
				noInicio = q;
				break;
			}
			atual++;	
		}		

        if (filho < fim) //tem dois filhos?
		{
			if (filhoDist < filhoProxDist)
				filho = filho + 1;
		}		

		atual = 0;
		for (q = f->ini; q!= NULL; q= q->prox)
		{
			if  (atual == filho)
			{
				filhoDist = q->dist;
				filhoVert = q->vert;
				break;
			}
			atual++;	
		}

		if ( auxDist < filhoDist ) //se o filho maior que o pai
		{						
			noInicio->vert = filhoVert;
			noInicio->dist = filhoDist;
			inicio = filho;
			filho = 2 * inicio + 1;					
		}else 
			filho = filho + 1;			

	}	

	
	atual = 0;
	for (q = f->ini; q!= NULL; q= q->prox)
	{
		if ( atual == inicio)
		{		
			q->vert = auxVert;
			q->dist = auxDist;
			break;
		}	
		atual++;		
	}			
}

void heapSortTeste(Fila* f)
{
	No *q;
	int tamanho = 0;
	for (q = f->ini; q!= NULL; q= q->prox)
		tamanho += 1;
		

    int i, atual;

	int auxVert;
	float auxDist;
	No *auxProx;

    for (i = (tamanho - 1) / 2; i >= 0; i--)    
        criaHeapTeste(f, i, tamanho-1);		


    for (i = tamanho - 1; i >= 1; i--)
    {
		q = f->ini;
		auxVert = q->vert;
		auxDist = q->dist;
		auxProx = q->prox;
		
		atual = 0;
		for (No *no = f->ini; no!= NULL; no= no->prox)
		{
			//printf("%d", atual);
			if (atual == i)
			{
				q->vert = no->vert;
				q->dist = no->dist;

				no->vert = auxVert;
				no->dist = auxDist;

				break;						
			}
			atual++;
		}
	
        criaHeapTeste(f, 0, i-1);		
    }		
}

void alteraPesoVertice(Fila *f, int vert, float peso)
{
	No *q;
	for (q = f->ini; q!= NULL; q= q->prox)
	{
		if (q->vert == vert)
		{
			q->dist = peso;
			break;
		}
		
	}	
}