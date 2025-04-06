#include "../include/grafo.h"
#include "../include/linked_list.h"
#include "../include/util.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct grafo {
  int nro_vertices;
  lista_encadeada *vertices;
};

bool is_grafo_empty(Grafo *grafo) {
  return (grafo == NULL || grafo->vertices == NULL);
}

Grafo *cria_grafo(int nro_vert) {
  Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));

  verifica_estouro_memoria(grafo, "cria_grafo");

  grafo->nro_vertices = nro_vert;
  grafo->vertices =
      (lista_encadeada *)malloc((nro_vert + 1) * sizeof(lista_encadeada));

  verifica_estouro_memoria(grafo->vertices, "cria_grafo");

  for (int i = 0; i <= grafo->nro_vertices; i++) {
    grafo->vertices[i] = cria_lista_encadeada();
  }

  return grafo;
}

bool insere_aresta(Grafo *grafo, int vertice, int vizinho) {
  if (is_grafo_empty(grafo)) {
    return false;
  }

  if (vertice > grafo->nro_vertices || vizinho > grafo->nro_vertices) {
    return false;
  }

  lista_encadeada_add_elemento(grafo->vertices[vertice], vizinho);
  lista_encadeada_add_elemento(grafo->vertices[vizinho], vertice);

  return true;
}

void imprimir_grafo(Grafo *grafo) {
  if (is_grafo_empty(grafo)) {
    printf("Error: Não é possível imprimir um grafo vazio");
    return;
  }

  for (int i = 0; i <= grafo->nro_vertices; i++) {
    printf("%d : => ", i);
    imprimir_lista_encadeada(grafo->vertices[i]);
    printf("\n");
  }
}

void libera_grafo(Grafo *grafo) {
  if (is_grafo_empty(grafo)) {
    return;
  }

  for (int i = 0; i < grafo->nro_vertices; i++) {
    destroi_lista_encadeada(grafo->vertices[i]);
  }

  free(grafo->vertices);
  free(grafo);

  grafo = NULL;
  grafo->vertices = NULL;
}
