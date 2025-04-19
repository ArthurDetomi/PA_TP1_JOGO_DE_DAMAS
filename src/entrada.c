#include "../include/entrada.h"

#include <string.h>

bool is_argumentos_validos(int argc, char *argv[]) {
  return argc == NUM_ARGS_ESPERADOS && strcmp(argv[1], FLAG_INPUT) == 0;
}

void carregar_tabuleiro_arquivo(Tabuleiro *tab, FILE *fp) {
  int qtd_pecas_jogador = 0;

  // Ponteiro para o array de posições das peças do jogador
  Posicao *posicoes_pecas_jogador = tab->jogador.posicoes;

  // Percorre todas as linhas do tabuleiro
  for (int i = 0; i < tab->total_linhas; i++) {
    // Percorre apenas as colunas válidas para peças de dama
    for (int j = i % 2; j < tab->total_colunas; j += 2) {
      fscanf(fp, " %c", &tab->casas[i][j]);

      // Se encontrou uma peça do jogador
      if (tab->casas[i][j] == PECA_JOGADOR) {
        posicoes_pecas_jogador[qtd_pecas_jogador].linha = i;
        posicoes_pecas_jogador[qtd_pecas_jogador].coluna = j;

        qtd_pecas_jogador++;
      }
    }
  }

  // Atualiza a quantidade total de peças do jogador no tabuleiro
  tab->jogador.quantidade = qtd_pecas_jogador;
}
