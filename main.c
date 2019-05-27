#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "entrada.h"

int main()
{

    grafo_t *grafo = criaGRAFO(qtdeNos, vertices);

    int linhas = sizeof( entrada ) / sizeof( entrada[0] ) ;

    for (int i = 0; i < linhas; i++)
    {
        addAresta(grafo, entrada[i][0] ,entrada[i][1], entrada[i][2]);
    }

    mostraGrafo(grafo);

    //Para ser um grafo, é só eu addAresta origem,destino e depois addAresta destino,origem
    // addAresta(grafo, 0 , 1);
    // addAresta(grafo, 0 , 4);
    // addAresta(grafo, 1 , 2);
    // addAresta(grafo, 1 , 3);
    // addAresta(grafo, 1 , 4);
    // addAresta(grafo, 2 , 3);
    // addAresta(grafo, 3 , 4);
    // addAresta(grafo, 0 , 0);        
    // addAresta(grafo, 4 , 4);      


    int origem, destino;
    printf("\n\n --- CAMINHO MAIS CURTO (Dijkstra) --- \n\n");
    printf("Por favor, digite o vertice de origem: \n");
    scanf("%d", &origem);
    float **matriz = dijkstra(grafo, origem);
    printf("Por favor, digite o vertice de destino: \n");
    scanf("%d", &destino);  

    printf("O caminho mais curto entre %d e %d eh %.1f\n", origem, destino, matriz[1][destino]);


    destroiGRAFO(grafo);

    //int **resposta = dijkstra(grafo, origem, destino);
    return 0;
}