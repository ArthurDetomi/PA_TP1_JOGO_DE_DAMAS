#include "../include/entrada.h"
#include "../include/jogo.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (!is_argumentos_validos(argc, argv)) {
    printf("Erro: Parâmetros inválidos.\n");
    printf("Uso correto: ./tp1 -i entrada.txt\n");
    printf("Onde '-i' indica o arquivo de entrada.\n");

    return 1;
  }

  char *input_path = argv[2];

  FILE *file_pointer = fopen(input_path, "r");

  if (file_pointer == NULL) {
    perror("Erro ao abrir arquivo");
    return 1;
  }

  while (true) {
    int total_linhas, total_colunas;

    fscanf(file_pointer, "%d %d", &total_linhas, &total_colunas);

    if (total_linhas == 0 || total_colunas == 0) {
      break;
    }

    Tabuleiro *tab = criar_tabuleiro(total_linhas, total_colunas);

    carregar_tabuleiro_arquivo(tab, file_pointer);

    int maximo_capturas = calcular_maximo_capturas_tabuleiro(tab);

    printf("%d\n", maximo_capturas);

    destruir_tabuleiro(tab);
  }

  fclose(file_pointer);

  return 0;
}