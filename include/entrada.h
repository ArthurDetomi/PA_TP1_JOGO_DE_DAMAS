#ifndef ENTRADA_H
#define ENTRADA_H

#include "../include/tabuleiro.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Define a flag esperada para especificar o arquivo de entrada
#define FLAG_INPUT "-i"

// Define a flag esperada para especificar o arquivo de saída
#define FLAG_OUTPUT "-o"

// Define o minimo de argumentos que deve se passar para executar o programa
#define NUM_MIN_ARGS_ESPERADOS 4

// Define o maximo de argumentos que pode se passar para executar o programa
#define NUM_MAX_ARGS_ESPERADOS 6

enum argumento_posicao {
  ESTRATEGIA_P = 1,
  FLAG_INPUT_P = 2,
  ARQUIVO_ENTRADA_P = 3,
  FLAG_OUTPUT_P = 4,
  ARQUIVO_SAIDA_P = 5,
};

enum estrategias { FORCA_BRUTA = 1, BACKTRACKING = 2 };

// Verifica se os argumentos de linha de comando são válidos
bool is_argumentos_validos(int argc, char *argv[]);

// Carrega o tabuleiro a partir de um arquivo
void carregar_tabuleiro_arquivo(Tabuleiro *tab, FILE *fp);

// Obtem o arquivo de saída especificado nos argumentos do programa
void *get_output_path(int argc, char *argv[], char *output_path);

#endif