#ifndef ENTRADA_H
#define ENTRADA_H

#include "../include/tabuleiro.h"

#include <stdbool.h>
#include <stdio.h>

#define FLAG_INPUT "-i"

bool is_argumentos_validos(int argc, char *argv[]);

void carregar_tabuleiro_arquivo(Tabuleiro *tab, FILE *fp);

#endif