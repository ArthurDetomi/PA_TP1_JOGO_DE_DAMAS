#include "../include/util.h"
#include <stdio.h>
#include <stdlib.h>

void verifica_estouro_memoria(void *ponteiro, char *nome_funcao) {
  if (ponteiro == NULL) {
    printf("ERRO: %s falha ao alocar memoria na função\n", nome_funcao);
    ponteiro = NULL;
  }
  return;
}

int converter_char_para_int(char c) { return c - '0'; }