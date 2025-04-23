#include "../include/strategybacktracking.h"
#include "../include/direcoes.h"

#include <stdbool.h>

// Macro que avalia e retorna o maior entre dois valores
#define max(x, y) x > y ? x : y

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

//  Calcula o máximo de capturas possíveis para uma peça específica
int calcular_maximo_captura_por_peca(Tabuleiro *tab, Posicao pos) {

  int maximo_capturas = 0;

  for (int i = 0; i < QUANTIDADE_DIRECOES_DIAGONAIS; i++) {
    Posicao posicao_oponente = {pos.linha + direcoes_uma_casa_diagonal[i].linha,
                                pos.coluna +
                                    direcoes_uma_casa_diagonal[i].coluna};
    Posicao posicao_vazia = {pos.linha + direcoes_duas_casas_diagonal[i].linha,
                             pos.coluna +
                                 direcoes_duas_casas_diagonal[i].coluna};

    bool is_peca_oponente =
        posicao_esta_dentro_tabuleiro(tab, posicao_oponente) &&
        tab->casas[posicao_oponente.linha][posicao_oponente.coluna] ==
            PECA_OPONENTE;
    bool is_peca_vazia =
        posicao_esta_dentro_tabuleiro(tab, posicao_vazia) &&
        tab->casas[posicao_vazia.linha][posicao_vazia.coluna] == CASA_VAZIA;

    /*
      Verifica se a captura nesta direção é válida : Se para essa respectiva
      direção existe uma peça do oponente seguida de uma casa vazia
    */
    if (is_peca_oponente && is_peca_vazia) {
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
int calcular_maximo_capturas_tabuleiro_backtracking(Tabuleiro *tab) {
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
