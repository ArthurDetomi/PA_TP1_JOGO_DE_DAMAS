#include "../include/entrada.h"
#include "../include/strategybacktracking.h"
#include "../include/strategybruteforce.h"
#include "../include/tempo.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Verifica se os argumentos de linha de comando são válidos
  if (!is_argumentos_validos(argc, argv)) {
    printf("Erro: Parâmetros inválidos.\n");
    printf("Uso correto: ./tp1 {estrateǵia} -i input/in.txt -o saida.txt\n");
    printf("Onde '-i' indica o arquivo de entrada.\n");
    printf("Onde '-o' indica o arquivo de saída (Opcional)\n");
    printf("Estratégia aceita somente 1(Força bruta) e 2{Backtracking}\n");

    return 1;
  }

  // Obtém o caminho do arquivo de entrada a partir dos argumentos
  char *input_path = argv[ARQUIVO_ENTRADA_P];

  // Tenta abrir o arquivo de entrada no modo leitura
  FILE *input_fp = fopen(input_path, "r");

  // Verifica se o arquivo foi aberto com sucesso
  if (input_fp == NULL) {
    perror("Erro ao abrir arquivo de entrada\n");
    return 1;
  }

  // Inicia o temporizador para medir o tempo total de execução
  Temporizador tempo_total;
  iniciarTemporizador(&tempo_total);

  // Obtém o caminho de arquivo de saída através dos argumentos
  char output_path[80];
  get_output_path(argc, argv, output_path);

  // Tenta criar um arquivo para salvar a saída principal
  FILE *output_fp = fopen(output_path, "w");

  // Arquivo para salvar os tempos em um arquivo csv
  FILE *csv_output_fp = fopen("output/resultados.csv", "w");

  // Verifica se o arquivo foi aberto com sucesso
  if (output_fp == NULL || csv_output_fp == NULL) {
    perror("Erro ao abrir arquivo de saida\n");
    return 1;
  }

  int estrategia_escolhida = atoi(argv[ESTRATEGIA_P]);

  while (true) {
    int total_linhas, total_colunas;

    // Lê as dimensões do tabuleiro (linhas x colunas)
    fscanf(input_fp, "%d %d", &total_linhas, &total_colunas);

    // Condição de parada
    if (total_linhas == 0 || total_colunas == 0) {
      break;
    }

    // Cria uma nova estrutura de tabuleiro com as dimensões lidas
    Tabuleiro *tab = criar_tabuleiro(total_linhas, total_colunas);

    // Carrega o conteúdo do tabuleiro a partir do arquivo
    carregar_tabuleiro_arquivo(tab, input_fp);

    // Inicia o temporizador para medir o tempo deste teste específico
    Temporizador tempo_teste;
    iniciarTemporizador(&tempo_teste);

    int maximo_capturas;

    switch (estrategia_escolhida) {
    case FORCA_BRUTA:
      maximo_capturas = calcular_maximo_capturas_tabuleiro_brute(tab);
      break;
    case BACKTRACKING:
      maximo_capturas = calcular_maximo_capturas_tabuleiro_backtracking(tab);
      break;
    }

    // Finaliza a medição de tempo para este teste
    finalizarTemporizador(&tempo_teste);

    // Exibe os resultados para o tabuleiro atual
    printf("Tabuleiro (%dx%d)\n", total_linhas, total_colunas);
    printf("Máximo de Capturas: %d\n", maximo_capturas);
    printf("Tempo de execução:\n");
    imprimirTempos(&tempo_teste);

    // Salva o maximo de capturas no arquivo de saída
    fprintf(output_fp, "%d\n", maximo_capturas);

    // Salva resultados de tempo em um csv
    salva_resultado_csv(maximo_capturas, &tempo_teste, csv_output_fp);

    // Libera memória alocada para o tabuleiro
    destruir_tabuleiro(tab);

    printf("\n");
  }

  // Finaliza a medição do tempo total de execução
  finalizarTemporizador(&tempo_total);

  // Exibe o tempo total de execução do programa
  printf("Tempo total de execução:\n");
  imprimirTempos(&tempo_total);

  // Fecha todos os arquivos
  fclose(input_fp);
  fclose(output_fp);
  fclose(csv_output_fp);

  return 0;
}