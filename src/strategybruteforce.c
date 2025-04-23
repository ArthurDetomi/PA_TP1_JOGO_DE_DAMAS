#include "../include/strategybruteforce.h"
#include "../include/direcoes.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x, y) x > y ? x : y

char movimentos[QUANTIDADE_DIRECOES_DIAGONAIS] = {'0', '1', '2', '3'};

void realizar_captura(char casas[20][20], Posicao origem, Posicao oponente,
                      Posicao destino) {
  casas[oponente.linha][oponente.coluna] = CASA_VAZIA;
  casas[origem.linha][origem.coluna] = CASA_VAZIA;
  casas[destino.linha][destino.coluna] = PECA_JOGADOR;
}

bool captura_valida(Tabuleiro *tab, char casas_copy[20][20],
                    Posicao pos_oponente, Posicao pos_vazia) {
  return posicao_esta_dentro_tabuleiro(tab, pos_oponente) &&
         casas_copy[pos_oponente.linha][pos_oponente.coluna] == PECA_OPONENTE &&
         posicao_esta_dentro_tabuleiro(tab, pos_vazia) &&
         casas_copy[pos_vazia.linha][pos_vazia.coluna] == CASA_VAZIA;
}

/*
  Recebe um caminho e simula a capturas das peças realizando as respectivas
  direções para cada peça do jogador
*/
int calcular_maximo_capturas(char *path, int path_size_max, Tabuleiro *tab) {
  Posicao *posicoes = tab->jogador.posicoes;

  int max_capturas = 0;

  // Para cada peça do jogador faça
  for (int i = 0; i < tab->jogador.quantidade; i++) {
    char casas_copy[20][20];

    // Copia as casas do tabuleiro de forma a proteger contra alteração
    copiar_casas_tabuleiro(casas_copy, tab);

    Posicao peca_atual = posicoes[i];

    Posicao pos_atual = peca_atual;

    int qtd_capturas = 0;

    // Realizar movimentações realizando capturas e contando a qtd de capturas
    // da mesma
    for (int j = 0; j < path_size_max; j++) {
      int movimento_idx = path[j] - '0';

      Posicao posicao_oponente = {
          pos_atual.linha + direcoes_uma_casa_diagonal[movimento_idx].linha,
          pos_atual.coluna + direcoes_uma_casa_diagonal[movimento_idx].coluna};
      Posicao posicao_vazia = {
          pos_atual.linha + direcoes_duas_casas_diagonal[movimento_idx].linha,
          pos_atual.coluna +
              direcoes_duas_casas_diagonal[movimento_idx].coluna};

      if (!captura_valida(tab, casas_copy, posicao_oponente, posicao_vazia)) {
        break;
      }

      realizar_captura(casas_copy, pos_atual, posicao_oponente, posicao_vazia);

      pos_atual = posicao_vazia;

      qtd_capturas++;
    }

    max_capturas = max(max_capturas, qtd_capturas);
  }

  return max_capturas;
}

/*
  Gera todas as combinações de movimentos possíveis para realizar de forma a
  capturar todas as peças do oponente (que são passiveis a ser capturada) no
  melhor caso.

  Complexidade:
  O(QUANTIDADE_DIRECOES_DIAGONAIS ^ path_size_max)
*/
void simular_todos_os_caminhos(char *current_path, int n, int path_size_max,
                               int *maximo_capturas, Tabuleiro *tab) {
  if (n == path_size_max) {
    // Maximo de capturas para a  combinação de movimentos atual
    int maximo = calcular_maximo_capturas(current_path, path_size_max, tab);

    (*maximo_capturas) = max(maximo, *maximo_capturas);

    return;
  }

  for (int i = 0; i < 4; i++) {
    current_path[n] = movimentos[i];

    simular_todos_os_caminhos(current_path, n + 1, path_size_max,
                              maximo_capturas, tab);
  }
}

int calcular_maximo_capturas_tabuleiro_brute(Tabuleiro *tab) {
  const int PATH_SIZE_MAX = tab->max_peças_capturaveis;

  char *current_path = (char *)malloc(PATH_SIZE_MAX * sizeof(char));

  if (current_path == NULL) {
    perror("ERRO: falha em alocar memória\n");
    exit(1);
  }

  /*
  Gera todos os caminhos e simula o andar das peças e calcula o maximo de
  capturas
  */
  int maximo_capturas = 0;
  simular_todos_os_caminhos(current_path, 0, PATH_SIZE_MAX, &maximo_capturas,
                            tab);

  free(current_path);
  current_path = NULL;

  return maximo_capturas;
}