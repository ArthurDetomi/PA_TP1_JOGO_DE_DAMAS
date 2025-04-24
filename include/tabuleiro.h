#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <stdbool.h>

// Definições dos tipos de casas no tabuleiro
#define CASA_VAZIA '0'
#define PECA_JOGADOR '1'
#define PECA_OPONENTE '2'
#define CASA_BRANCA 'x'

// Estrutura para representar uma posição no tabuleiro (linha, coluna)
typedef struct {
  int linha;
  int coluna;
} Posicao;

// Estrutura para agrupar um conjunto de peças com suas posições
typedef struct {
  Posicao *posicoes;
  int quantidade;
} ConjuntoDePecas;

// Estrutura principal que representa o tabuleiro do jogo
typedef struct {
  int total_linhas;
  int total_colunas;
  char casas[20][20];
  ConjuntoDePecas jogador;
  int max_pecas_capturaveis;
} Tabuleiro;

// Cria e inicializa uma nova instância de tabuleiro
Tabuleiro *criar_tabuleiro(int total_linhas, int total_colunas);

// Libera a memória alocada para o tabuleiro
void destruir_tabuleiro(Tabuleiro *tab);

// Imprimi o tabuleiro PS: para debug
void imprimir_tabuleiro(Tabuleiro *tab);

// Verifica se uma posição está dentro dos limites do tabuleiro
bool posicao_esta_dentro_tabuleiro(Tabuleiro *tab, Posicao pos);

// Copia o array casas do tabuleiro para outro array de destino
void copiar_casas_tabuleiro(char dest[20][20], Tabuleiro *tab);

/*
  Considera-se que a pos é uma peça do oponente e verifica se ela é passível a
  ser capturada, ou seja, não está nas bordas do tabuleiro e possui uma casa
  vazia uma casa vazia em sua diagonal
*/
bool eh_posicao_valida_para_ser_capturada(Tabuleiro *tab, Posicao pos);

#endif
