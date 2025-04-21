#ifndef TABULEIRO_H
#define TABULEIRO_H

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
} Tabuleiro;

// Cria e inicializa uma nova instância de tabuleiro
Tabuleiro *criar_tabuleiro(int total_linhas, int total_colunas);

// Libera a memória alocada para o tabuleiro
void destruir_tabuleiro(Tabuleiro *tab);

void imprimir_tabuleiro(Tabuleiro *tab);

#endif
