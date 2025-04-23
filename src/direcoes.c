#include "../include/direcoes.h"

const Posicao direcoes_uma_casa_diagonal[QUANTIDADE_DIRECOES_DIAGONAIS] = {
    {-1, -1}, // Diagonal superior esquerda
    {-1, 1},  // Diagonal superior direita
    {1, -1},  // Diagonal inferior esquerda
    {1, 1}    // Diagonal inferior direita
};

const Posicao direcoes_duas_casas_diagonal[QUANTIDADE_DIRECOES_DIAGONAIS] = {
    {-2, -2}, // Dois passos superior esquerda
    {-2, 2},  // Dois passos superior direita
    {2, -2},  // Dois passos inferior esquerda
    {2, 2}    // Dois passos inferior direita
};
