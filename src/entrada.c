#include "../include/entrada.h"

#include <stdbool.h>
#include <string.h>

bool is_argumentos_validos(int argc, char *argv[]) {
  // A entrada do programa deve possuir 3 argumentos ou 5 argumentos
  if (argc != NUM_MIN_ARGS_ESPERADOS && argc != NUM_MAX_ARGS_ESPERADOS) {
    return false;
  }

  // Se não possui a flag -i como argumento considera-se invalido
  if (strcmp(argv[1], FLAG_INPUT) != 0) {
    return false;
  }

  /*
    Se possui o número minimo de argumentos a validação já feita é suficiente
    portanto é válido os argumentos
  */
  if (argc == NUM_MIN_ARGS_ESPERADOS) {
    return true;
  }

  // Caso tenha 5 argumentos o 4 argumento obrigatoriamente deve ser o -o
  return strcmp(argv[3], FLAG_OUTPUT) == 0;
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

void *get_output_path(int argc, char *argv[], char *output_path) {
  strcpy(output_path, "output/");
  strcat(output_path,
         (NUM_MAX_ARGS_ESPERADOS == argc) ? argv[4] : "output.txt");

  return output_path;
}