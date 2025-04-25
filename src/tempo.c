#include "../include/tempo.h"

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

double calcularTempo(struct timeval inicio, struct timeval fim) {
  time_t seg = fim.tv_sec - inicio.tv_sec;
  suseconds_t microseg = fim.tv_usec - inicio.tv_usec;

  // Ajusta caso microsegundos do fim sejam menores que os do início
  if (microseg < 0) {
    seg -= 1;
    microseg += 1000000;
  }

  return (double)seg + (double)microseg / 1e6;
}

// Calcula diferença entre tempos reais (start e end) em segundos
double calcularTempoReal(Temporizador *t) {
  return calcularTempo(t->start_tv, t->end_tv);
}

// Calcula diferença entre tempos de sistema (start e end) em segundos
double calcularTempoSistema(Temporizador *t) {
  return calcularTempo(t->start_usage.ru_stime, t->end_usage.ru_stime);
}

// Imprime todos os tempos de execução de forma legível
void imprimirTempos(Temporizador *t) {
  printf("Tempo Real: %.8f segundos\n",
         calcularTempoReal(t)); // Tempo real é agora o "Tempo Usuário"
  printf("Tempo Sistema: %.8f segundos\n", calcularTempoSistema(t));
}

// Salva os resultados em um arquivo CSV
void salva_resultado_csv(int max, Temporizador *t, FILE *fp) {
  // Escreve os dados no formato CSV
  fprintf(fp, "%d,%.6f,%.6f\n", max, calcularTempoReal(t),
          calcularTempoSistema(t));
}
