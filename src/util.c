#include "../include/util.h"
#include <stdio.h>
#include <stdlib.h>

void verifica_estouro_memoria(void *ponteiro, char *nome_funcao) {
  if (ponteiro == NULL) {
    fprintf(stderr, "ERRO: falha de alocação em %s\n", nome_funcao);
  }
}

int converter_char_para_int(char c) { return c - '0'; }

int max(int a, int b) { return (a > b) ? a : b; }