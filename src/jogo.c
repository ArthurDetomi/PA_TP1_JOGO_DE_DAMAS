#include "../include/jogo.h"
#include "../include/util.h"

#include <stdbool.h>

#define DIRECOES_MOVIMENTO 4

// Direções para captura (peça oponente e casa vazia)
Posicao direcoes_oponente[DIRECOES_MOVIMENTO] = {
    {-1, -1}, // Diagonal superior esquerda
    {-1, 1},  // Diagonal superior direita
    {1, -1},  // Diagonal inferior esquerda
    {1, 1}    // Diagonal inferior direita
};

// Vetores com as direções relativas para posições vazias após captura
Posicao direcoes_vazio[DIRECOES_MOVIMENTO] = {
    {-2, -2}, // Dois passos superior esquerda
    {-2, 2},  // Dois passos superior direita
    {2, -2},  // Dois passos inferior esquerda
    {2, 2}    // Dois passos inferior direita
};

// Atualiza o tabuleiro após uma captura
void atualizar_tabuleiro(Tabuleiro *tab, Posicao peca, Posicao oponente,
                         Posicao vazio) {
  tab->casas[peca.linha][peca.coluna] = CASA_VAZIA;
  tab->casas[oponente.linha][oponente.coluna] = CASA_VAZIA;
  tab->casas[vazio.linha][vazio.coluna] = PECA_JOGADOR;
}

// Restaura o tabuleiro ao estado anterior a uma captura
void restaurar_tabuleiro(Tabuleiro *tab, Posicao peca, Posicao oponente,
                         Posicao vazio) {
  tab->casas[peca.linha][peca.coluna] = PECA_JOGADOR;
  tab->casas[oponente.linha][oponente.coluna] = PECA_OPONENTE;
  tab->casas[vazio.linha][vazio.coluna] = CASA_VAZIA;
}

// Verifica se uma posição está dentro dos limites do tabuleiro
bool posicao_eh_valida(Tabuleiro *tab, Posicao pos) {
  return (pos.linha >= 0 && pos.linha < tab->total_linhas) &&
         (pos.coluna >= 0 && pos.coluna < tab->total_colunas);
}

//  Calcula o máximo de capturas possíveis para uma peça específica
int calcular_maximo_captura_por_peca(Tabuleiro *tab, Posicao pos) {

  int maximo_capturas = 0;

  for (int i = 0; i < DIRECOES_MOVIMENTO; i++) {
    Posicao posicao_oponente = {pos.linha + direcoes_oponente[i].linha,
                                pos.coluna + direcoes_oponente[i].coluna};
    Posicao posicao_vazia = {pos.linha + direcoes_vazio[i].linha,
                             pos.coluna + direcoes_vazio[i].coluna};

    bool oponente_valido =
        posicao_eh_valida(tab, posicao_oponente) &&
        tab->casas[posicao_oponente.linha][posicao_oponente.coluna] ==
            PECA_OPONENTE;
    bool vazio_valido =
        posicao_eh_valida(tab, posicao_vazia) &&
        tab->casas[posicao_vazia.linha][posicao_vazia.coluna] == CASA_VAZIA;

    /*
      Verifica se a captura nesta direção é válida : Se para essa respectiva
      direção existe uma peça do oponente seguida de uma casa vazia
    */
    if (oponente_valido && vazio_valido) {
      // Realiza a captura (modifica o tabuleiro)
      atualizar_tabuleiro(tab, pos, posicao_oponente, posicao_vazia);

      // Calcula capturas recursivamente a partir da nova posição
      int capturas = 1 + calcular_maximo_captura_por_peca(tab, posicao_vazia);

      // Desfaz a captura (restaura o tabuleiro)
      restaurar_tabuleiro(tab, pos, posicao_oponente, posicao_vazia);

      // Atualiza o máximo de capturas encontrado
      maximo_capturas = max(maximo_capturas, capturas);
    }
  }

  return maximo_capturas;
}

// Calcula o número máximo de capturas possíveis em todo o tabuleiro
int calcular_maximo_capturas_tabuleiro(Tabuleiro *tab) {
  int maior_captura_possivel = -1;

  // Obtém todas as peças do jogador
  ConjuntoDePecas pecas_do_jogador = tab->jogador;
  Posicao *posicoes_pecas_jogador = pecas_do_jogador.posicoes;

  // Para cada peça do jogador faça
  for (int i = 0; i < pecas_do_jogador.quantidade; i++) {
    Posicao peca_atual = posicoes_pecas_jogador[i];

    // Calcula máximo de capturas que a peça atual é capaz de fazer
    int capturas_posicao_atual =
        calcular_maximo_captura_por_peca(tab, peca_atual);

    // Atualiza o máximo geral
    maior_captura_possivel =
        max(capturas_posicao_atual, maior_captura_possivel);
  }

  return maior_captura_possivel;
}
