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

bool insere_aresta(Grafo *grafo, int vertice, int aresta) {
  if (is_grafo_empty(grafo)) {
    return false;
  }

  if (vertice > grafo->nro_vertices || aresta > grafo->nro_vertices) {
    return false;
  }

  lista_encadeada_add_elemento(grafo->vertices[vertice], aresta);

  return true;
}

void imprimir_aresta(lista_encadeada vizinhos) {
  printf("[");

  int qtd_vizinho = lista_encadeada_tamanho(vizinhos);

  int i = 0;

  for (int i = 0; i < qtd_vizinho; i++) {
    vizinhos = vizinhos->proximo;

    printf("%d", vizinhos->elemento);

    if (i != qtd_vizinho - 1) {
      printf(",");
    }
  }

  printf("]");
}

void imprimir_grafo(Grafo *grafo) {
  if (is_grafo_empty(grafo)) {
    printf("Error: Não é possível imprimir um grafo vazio");
    return;
  }

  for (int i = 0; i <= grafo->nro_vertices; i++) {
    printf("%d : => ", i);
    imprimir_aresta(grafo->vertices[i]);
    printf("\n");
  }
}
