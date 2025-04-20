#include "../include/tempo.h"
#include <stdio.h>

// Inicia a medição do tempo, armazenando os valores atuais
void iniciarTemporizador(Temporizador *t) {
  gettimeofday(&t->start_tv, NULL);
  getrusage(RUSAGE_SELF, &t->start_usage);
}

// Finaliza a medição do tempo, armazenando os valores finais
void finalizarTemporizador(Temporizador *t) {
  gettimeofday(&t->end_tv, NULL);
  getrusage(RUSAGE_SELF, &t->end_usage);
}

// Calcula diferença entre tempos reais (start e end) em segundos
double calcularTempoReal(Temporizador *t) {
  return (t->end_tv.tv_sec - t->start_tv.tv_sec) +
         (t->end_tv.tv_usec - t->start_tv.tv_usec) / 1000000.0;
}

// Calcula diferença entre tempos de usuário (start e end) em segundos
double calcularTempoUsuario(Temporizador *t) {
  return (t->end_usage.ru_utime.tv_sec - t->start_usage.ru_utime.tv_sec) +
         (t->end_usage.ru_utime.tv_usec - t->start_usage.ru_utime.tv_usec) /
             1000000.0;
}

// Calcula diferença entre tempos de sistema (start e end) em segundos
double calcularTempoSistema(Temporizador *t) {
  return (t->end_usage.ru_stime.tv_sec - t->start_usage.ru_stime.tv_sec) +
         (t->end_usage.ru_stime.tv_usec - t->start_usage.ru_stime.tv_usec) /
             1000000.0;
}

// Imprime todos os tempos de execução de forma legível
void imprimirTempos(Temporizador *t) {
  printf("Tempo Real: %.6f segundos\n", calcularTempoReal(t));
  printf("Tempo Usuário: %.6f segundos\n", calcularTempoUsuario(t));
  printf("Tempo Sistema: %.6f segundos\n", calcularTempoSistema(t));
  printf("Tempo Total CPU: %.6f segundos\n",
         calcularTempoUsuario(t) + calcularTempoSistema(t));
}

// Salva os resultados em um arquivo CSV
void salva_resultado_csv(int max, Temporizador *t,const char *nome_arquivo){
  FILE *file = fopen(nome_arquivo, "a");
  if (file == NULL) {
      perror("Erro ao abrir arquivo CSV");
      return;
  }

  // Escreve os dados no formato CSV
  fprintf(file, "%d,%.6f,%.6f,%.6f\n", max, calcularTempoReal(t),calcularTempoUsuario(t),calcularTempoSistema(t));

  fclose(file);
}