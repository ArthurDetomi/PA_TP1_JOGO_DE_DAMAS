#include "../include/entrada.h"

#include <string.h>

bool is_argumentos_validos(int argc, char *argv[]) {
  return argc == 3 && strcmp(argv[1], FLAG_INPUT) == 0;
}

void carregar_tabuleiro_arquivo(Tabuleiro *tab, FILE *fp) {
  int qtd_pecas_jogador = 0;

  Posicao *posicoes_pecas_jogador = tab->jogador.posicoes;

  for (int i = 0; i < tab->total_linhas; i++) {
    for (int j = i % 2; j < tab->total_colunas; j += 2) {
      fscanf(fp, " %c", &tab->casas[i][j]);

      if (tab->casas[i][j] == PECA_JOGADOR) {
        posicoes_pecas_jogador[qtd_pecas_jogador].linha = i;
        posicoes_pecas_jogador[qtd_pecas_jogador].coluna = j;

        qtd_pecas_jogador++;
      }
    }
  }

  tab->jogador.quantidade = qtd_pecas_jogador;
}
