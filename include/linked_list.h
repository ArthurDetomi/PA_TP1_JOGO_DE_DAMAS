#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdbool.h>

typedef int elemento;

typedef struct celula {
  elemento elemento;
  struct celula *proximo;
} celula;

typedef struct celula *lista_encadeada;

// cria uma nova lista
lista_encadeada cria_lista_encadeada();

// Adiciona um elemento ao inicio da lista, complexidade O(1)
void lista_encadeada_add_elemento(lista_encadeada lista,
                                  elemento elemento_param);

// Verifica se a lista está vazia
bool lista_encadeada_esta_vazia(lista_encadeada lista);

// Retorna a quantidade de itens presente na lista
int lista_encadeada_tamanho(lista_encadeada lista);

// Libera o espaço alocado da lista
void destroi_lista_encadeada(lista_encadeada lista);

#endif