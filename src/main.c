#include "../include/grafo.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
  printf("ola\n");
  Grafo *grafo = cria_grafo(5);

  insere_aresta(grafo, 0, 1);
  insere_aresta(grafo, 0, 2);
  insere_aresta(grafo, 0, 3);
  insere_aresta(grafo, 1, 0);
  insere_aresta(grafo, 1, 2);

  imprimir_grafo(grafo);
  /*
  while (true) {
    char mat[20][20];

    int N, M;

    scanf("%d %d", &N, &M);

    if (N == 0 && M == 0) {
      break;
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        mat[i][j] = 'x';
      }
    }

    for (int i = 0; i < N; i++) {
      for (int j = i % 2; j < M; j += 2) {
        scanf(" %c", &mat[i][j]);
      }
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        printf("%c ", mat[i][j]);
      }
      printf("\n");
    }
  }
  */

  return 0;
}