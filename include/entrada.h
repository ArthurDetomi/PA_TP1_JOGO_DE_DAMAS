#ifndef ENTRADA_H
#define ENTRADA_H

#include "../include/tabuleiro.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Define a flag esperada para especificar o arquivo de entrada
#define FLAG_INPUT "-i"

// Define a quantidade de argumentos esperados pelo programa
#define NUM_ARGS_ESPERADOS 3

// Verifica se os argumentos de linha de comando são válidos
bool is_argumentos_validos(int argc, char *argv[]);

// Carrega o tabuleiro a partir de um arquivo
void carregar_tabuleiro_arquivo(Tabuleiro *tab, FILE *fp);

#endif