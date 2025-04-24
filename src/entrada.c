#include "../include/entrada.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool is_argumentos_validos(int argc, char *argv[]) {
  // A entrada do programa deve possuir 3 argumentos ou 5 argumentos
  if (argc != NUM_MIN_ARGS_ESPERADOS && argc != NUM_MAX_ARGS_ESPERADOS) {
    return false;
  }

  int estrategia = (int)atoi(argv[ESTRATEGIA_P]);

  if (estrategia != FORCA_BRUTA && estrategia != BACKTRACKING) {
    return false;
  }

  // Se não possui a flag -i como argumento considera-se invalido
  if (strcmp(argv[FLAG_INPUT_P], FLAG_INPUT) != 0) {
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
  return strcmp(argv[FLAG_OUTPUT_P], FLAG_OUTPUT) == 0;
}

void carregar_tabuleiro_arquivo(Tabuleiro *tab, FILE *fp) {
  int qtd_pecas_jogador = 0, max_pecas_capturaveis = 0;

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

      Posicao pos;
      pos.linha = i;
      pos.coluna = j;

      if (tab->casas[i][j] == PECA_OPONENTE &&
          eh_posicao_valida_para_ser_capturada(tab, pos)) {
        max_pecas_capturaveis++;
      }
    }
  }

  // Atribui a quantidade total de peças do jogador no tabuleiro
  tab->jogador.quantidade = qtd_pecas_jogador;

  // Atribui a quantidade total de peças do oponente que estão em posicionamento
  // favoravel
  tab->max_pecas_capturaveis = max_pecas_capturaveis;
}

void *get_output_path(int argc, char *argv[], char *output_path) {
  strcpy(output_path, "output/");
  strcat(output_path, (NUM_MAX_ARGS_ESPERADOS == argc) ? argv[ARQUIVO_SAIDA_P]
                                                       : "output.txt");

  return output_path;
}