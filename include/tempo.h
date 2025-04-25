#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

// Estrutura para armazenar os tempos de execução
typedef struct Temporizador {
  struct timeval start_tv, end_tv;
  struct rusage start_usage, end_usage;
} Temporizador;

// Inicia a contagem do temporizador
void iniciarTemporizador(Temporizador *t);

// Finaliza a contagem do temporizador
void finalizarTemporizador(Temporizador *t);

// Calcula o tempo real decorrido em segundos
double calcularTempoReal(Temporizador *t);

// Calcula o tempo de CPU em modo usuário em segundos
double calcularTempoUsuario(Temporizador *t);

// Calcula o tempo de CPU em modo sistema/kernel em segundos
double calcularTempoSistema(Temporizador *t);

// Imprime todos os tempos medidos de forma formatada
void imprimirTempos(Temporizador *t);

// Salva os resultados em um arquivo CSV
void salva_resultado_csv(int max, Temporizador *t, FILE *fp);

#endif