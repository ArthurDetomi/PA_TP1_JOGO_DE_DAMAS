#include "../include/tabuleiro.h"

#include <stdlib.h>

Posicao *alocar_posicoes(int total) {
  Posicao *posicoes = (Posicao *)malloc(sizeof(Posicao) * total);

  return posicoes;
}

Tabuleiro *criar_tabuleiro(int total_linhas, int total_colunas) {
  Tabuleiro *tab = (Tabuleiro *)malloc(sizeof(Tabuleiro));

  if (tab == NULL) {
    return NULL;
  }

  tab->total_linhas = total_linhas;
  tab->total_colunas = total_colunas;

  for (int i = 0; i < total_linhas; i++) {
    for (int j = 0; j < total_colunas; j++) {
      tab->casas[i][j] = CASA_BRANCA;
    }
  }

  const int MAXIMO_PECAS = (total_linhas * total_colunas / 2) + 1;

  ConjuntoDePecas jogador;

  jogador.posicoes = alocar_posicoes(MAXIMO_PECAS);

  if (jogador.posicoes == NULL) {
    free(tab);
    return NULL;
  }

  tab->jogador = jogador;

  return tab;
}

void destruir_tabuleiro(Tabuleiro *tab) {
  free(tab->jogador.posicoes);
  tab->jogador.posicoes = NULL;
  free(tab);
  tab = NULL;
}