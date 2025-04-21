#include "../include/entrada.h"
#include "../include/jogo.h"
#include "../include/tempo.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Verifica se os argumentos de linha de comando são válidos
  if (!is_argumentos_validos(argc, argv)) {
    printf("Erro: Parâmetros inválidos.\n");
    printf("Uso correto: ./tp1 -i input/in.txt\n");
    printf("Onde '-i' indica o arquivo de entrada.\n");

    return 1;
  }

  // Obtém o caminho do arquivo de entrada a partir dos argumentos
  char *input_path = argv[2];

  // Tenta abrir o arquivo de entrada no modo leitura
  FILE *file_pointer = fopen(input_path, "r");

  // Verifica se o arquivo foi aberto com sucesso
  if (file_pointer == NULL) {
    perror("Erro ao abrir arquivo\n");
    return 1;
  }

  // Inicia o temporizador para medir o tempo total de execução
  Temporizador tempo_total;
  iniciarTemporizador(&tempo_total);

  while (true) {
    int total_linhas, total_colunas;

    // Lê as dimensões do tabuleiro (linhas x colunas)
    fscanf(file_pointer, "%d %d", &total_linhas, &total_colunas);

    // Condição de parada
    if (total_linhas == 0 || total_colunas == 0) {
      break;
    }

    // Cria uma nova estrutura de tabuleiro com as dimensões lidas
    Tabuleiro *tab = criar_tabuleiro(total_linhas, total_colunas);

    // Carrega o conteúdo do tabuleiro a partir do arquivo
    carregar_tabuleiro_arquivo(tab, file_pointer);
    for (int i = 0; i < total_linhas; i++) {
      for (int j = 0; j < total_colunas; j++) {
        printf("%3c", tab->casas[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    // Inicia o temporizador para medir o tempo deste teste específico
    Temporizador tempo_teste;
    iniciarTemporizador(&tempo_teste);

    // Calcula o número máximo de capturas possíveis para este tabuleiro
    int maximo_capturas = calcular_maximo_capturas_tabuleiro(tab);

    // Finaliza a medição de tempo para este teste
    finalizarTemporizador(&tempo_teste);

    // Exibe os resultados para o tabuleiro atual
    printf("Tabuleiro (%dx%d)\n", total_linhas, total_colunas);
    printf("Máximo de Capturas: %d\n", maximo_capturas);
    printf("Tempo de execução:\n");
    imprimirTempos(&tempo_teste);
    salva_resultado_csv(maximo_capturas,&tempo_teste,"resultados.csv");
    printf("\n");
    
    // Libera memória alocada para o tabuleiro
    destruir_tabuleiro(tab);
  }

  // Finaliza a medição do tempo total de execução
  finalizarTemporizador(&tempo_total);

  // Exibe o tempo total de execução do programa
  printf("Tempo total de execução:\n");
  imprimirTempos(&tempo_total);

  // Fecha o arquivo de entrada
  fclose(file_pointer);

  return 0;
}