#ifndef TABULEIRO_H
#define TABULEIRO_H

#define CASA_VAZIA '0'
#define PECA_JOGADOR '1'
#define PECA_OPONENTE '2'
#define CASA_BRANCA 'x'

typedef struct {
  int linha;
  int coluna;
} Posicao;

typedef struct {
  Posicao *posicoes;
  int quantidade;
} ConjuntoDePecas;

typedef struct {
  int total_linhas;
  int total_colunas;
  char casas[20][20];
  ConjuntoDePecas jogador;
} Tabuleiro;

Tabuleiro *criar_tabuleiro(int total_linhas, int total_colunas);

void destruir_tabuleiro(Tabuleiro *tab);

#endif
