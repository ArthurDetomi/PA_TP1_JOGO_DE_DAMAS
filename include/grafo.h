#ifndef GRAFO_H
#define GRAFO_H
#include <stdbool.h>

typedef struct grafo Grafo;

Grafo *cria_grafo(int nro_vert);

void libera_grafo(Grafo *grafo);

bool insere_aresta(Grafo *grafo, int vertice, int aresta);

void imprimir_grafo(Grafo *grafo);

#endif