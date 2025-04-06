#include "../include/grafo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int N, M;

typedef struct Pos {
  int l;
  int c;
} Pos;

int max(int a, int b) { return (a > b) ? a : b; }

Pos moves_oponent[4] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
Pos moves_vazio[4] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}};

bool eh_valida(Pos pos) {
  return (pos.l >= 0 && pos.l < N) && (pos.c >= 0 && pos.c < M);
}

void show(char mat[][20]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      printf("%c ", mat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int max_path_solve(char mat[][20], Pos pos) {
  int max_capturas = 0;

  for (int i = 0; i < 4; i++) {
    Pos pos_oponente = {pos.l + moves_oponent[i].l, pos.c + moves_oponent[i].c};
    Pos pos_vazio = {pos.l + moves_vazio[i].l, pos.c + moves_vazio[i].c};

    if (eh_valida(pos_oponente) && eh_valida(pos_vazio) &&
        mat[pos_oponente.l][pos_oponente.c] == '2' &&
        mat[pos_vazio.l][pos_vazio.c] == '0') {

      mat[pos.l][pos.c] = '0';
      mat[pos_oponente.l][pos_oponente.c] = '0';
      mat[pos_vazio.l][pos_vazio.c] = '1';

      // show(mat);

      int capturas = 1 + max_path_solve(mat, pos_vazio);

      mat[pos.l][pos.c] = '1';
      mat[pos_oponente.l][pos_oponente.c] = '2';
      mat[pos_vazio.l][pos_vazio.c] = '0';

      // show(mat);

      max_capturas = max(max_capturas, capturas);
    }
  }

  return max_capturas;
}

int solve(char mat[][20], Pos *raizes, int n) {
  int max_value = -1;

  for (int i = 0; i < n; i++) {
    Pos raiz = raizes[i];

    int max_path = max_path_solve(mat, raiz);

    printf("max path = %d\n", max_path);

    max_value = max(max_path, max_value);
  }

  return max_value;
}

int main() {
  while (true) {
    char mat[20][20];

    scanf("%d %d", &N, &M);

    if (N == 0 && M == 0) {
      break;
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        mat[i][j] = 'x';
      }
    }

    Pos *raizes = (Pos *)malloc(((N * M / 2) + 1) * sizeof(Pos));
    int qtd_raiz = 0;

    for (int i = 0; i < N; i++) {
      for (int j = i % 2; j < M; j += 2) {
        scanf(" %c", &mat[i][j]);

        if (mat[i][j] == '1') {
          raizes[qtd_raiz].l = i;
          raizes[qtd_raiz].c = j;

          qtd_raiz++;
        }
      }
    }

    show(mat);

    int result = solve(mat, raizes, qtd_raiz);

    printf("result = %d\n", result);

    free(raizes);
    raizes = NULL;
  }

  return 0;
}