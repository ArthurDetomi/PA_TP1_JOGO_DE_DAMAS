#include "../include/tabuleiro.h"

#include <stdio.h>
#include <stdlib.h>

// Função auxiliar para alocar dinamicamente um vetor de posições
Posicao *alocar_posicoes(int total) {
  Posicao *posicoes = (Posicao *)malloc(sizeof(Posicao) * total);

  return posicoes;
}

// Cria e retorna um novo tabuleiro
Tabuleiro *criar_tabuleiro(int total_linhas, int total_colunas) {
  // Aloca memória para a estrutura do tabuleiro
  Tabuleiro *tab = (Tabuleiro *)malloc(sizeof(Tabuleiro));

  if (tab == NULL) {
    return NULL;
  }

  // Configura as dimensões do tabuleiro
  tab->total_linhas = total_linhas;
  tab->total_colunas = total_colunas;

  // Inicializa todas as casas como brancas (inválidas)
  for (int i = 0; i < total_linhas; i++) {
    for (int j = 0; j < total_colunas; j++) {
      tab->casas[i][j] = CASA_BRANCA;
    }
  }

  // Calcula o número máximo de peças
  const int MAXIMO_PECAS = (total_linhas * total_colunas / 2) + 1;

  // Prepara a estrutura para armazenar as peças do jogador
  ConjuntoDePecas jogador;
  jogador.posicoes = alocar_posicoes(MAXIMO_PECAS);

  // Verifica se a alocação das posições foi bem sucedida
  if (jogador.posicoes == NULL) {
    free(tab);
    return NULL;
  }

  // Associa o conjunto de peças ao tabuleiro
  tab->jogador = jogador;

  return tab;
}

void destruir_tabuleiro(Tabuleiro *tab) {
  // Libera o vetor de posições das peças
  free(tab->jogador.posicoes);
  tab->jogador.posicoes = NULL;

  // Libera a estrutura principal do tabuleiro
  free(tab);
  tab = NULL;
}

void imprimir_tabuleiro(Tabuleiro *tab) {
  if (tab == NULL) {
    return;
  }

  printf("Imprimindo tabuleiro (%dx%d): \n", tab->total_linhas,
         tab->total_colunas);
  for (int i = 0; i < tab->total_linhas; i++) {
    for (int j = 0; j < tab->total_colunas; j++) {
      printf("%3c", tab->casas[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}