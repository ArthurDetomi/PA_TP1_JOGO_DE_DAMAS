# Dama com Vovô

Este programa resolve um problema de jogo de dama com um tabuleiro retangular, onde o objetivo é determinar o número máximo de peças do oponente que o jogador (cuja peça é representada por 1) pode capturar em uma única jogada. O jogo segue as regras tradicionais de captura de peças em damas, mas com a possibilidade de realizar capturas múltiplas em um único movimento.

## Descrição do Problema

O tabuleiro do jogo é retangular, com `N` linhas e `M` colunas, onde as casas de cor escura são aquelas que podem ser ocupadas pelas peças. As peças podem ser representadas pelos seguintes números:

- `0`: casa vazia
- `1`: peça do jogador
- `2`: peça do oponente

### Regras de Jogo

- As peças se movem na diagonal.
- Para capturar uma peça do oponente, a peça do jogador deve saltar sobre a peça adversária para uma casa vazia imediatamente após ela.
- A captura múltipla é permitida, ou seja, o jogador pode saltar várias vezes, capturando diversas peças do oponente em sequência.
- Não é permitido saltar sobre uma peça do próprio jogador ou saltar a mesma peça do oponente mais de uma vez.

## Resolução do Problema

A solução foi implementada utilizando a técnica de **backtracking** (ou "retrocesso"), que permite explorar todas as possíveis capturas que o jogador pode realizar em um dado tabuleiro. O backtracking é uma abordagem eficiente para resolver problemas que envolvem múltiplas escolhas sequenciais, como o de capturar peças em várias etapas. O algoritmo tenta fazer uma captura, e, se for bem-sucedido, recursivamente tenta fazer capturas adicionais, voltando ao estado anterior se a solução não for promissora.

### Como Funciona:

1. O algoritmo começa verificando todas as direções possíveis para capturar peças do oponente a partir de uma posição válida da peça do jogador.

2. Para cada direção válida de captura (onde uma peça do oponente está seguida por uma casa vazia), o algoritmo realiza a captura e recursivamente tenta outras capturas a partir da nova posição.

3. A captura é **"desfeita"** (restaurando o tabuleiro ao estado anterior) após cada tentativa, garantindo que o algoritmo explore todas as possibilidades de captura múltipla.

4. A cada captura válida, o algoritmo mantém um registro do maior número de peças capturadas em uma sequência de saltos.

5. Este processo continua até que todas as peças do jogador tenham sido exploradas, e o número máximo de capturas possíveis é determinado.

## Entrada

A entrada contém vários casos de teste. Cada caso de teste é composto pelas seguintes linhas:

1. A primeira linha contém dois inteiros `N` e `M`, indicando respectivamente o número de linhas e o número de colunas do tabuleiro (3 ≤ N ≤ 20, 3 ≤ M ≤ 20, e N × M ≤ 200). O quadrado mais à esquerda do tabuleiro na borda mais próxima ao jogador é uma casa.
2. A segunda linha contém a descrição do estado do jogo. Cada descrição consiste de `(N × M)/2` inteiros, separados por um espaço, correspondendo às casas do tabuleiro, numeradas de 1 até `(N × M)/2`, da esquerda para a direita, da borda mais próxima ao jogador até a borda mais próxima ao oponente. Na descrição do estado do jogo:

   - `0` representa uma casa vazia.
   - `1` representa uma casa com uma peça do jogador.
   - `2` representa uma casa com uma peça do oponente.

   Há no máximo `(N × M)/4` peças de cada jogador no tabuleiro.

3. O final da entrada é indicado por `N = M = 0`.

### Exemplo de Entrada

```
3 3
2 1 2 0 1
5 3
1 0 2 1 0 2 0 0
8 8
2 2 2 2 0 0 0 0 2 2 2 2 0 0 0 0 2 2 2 2 0 0 0 0 2 2 2 2 0 1 0 0
0 0
```

## Saída

Para cada caso de teste, o programa deve retornar o número máximo de peças do oponente que o jogador (peça `1`) pode capturar em uma jogada de captura. A captura pode ser única ou múltipla (saltos seguidos). E o tempo de sistema e usuário.

### Exemplo de Saída

```
Tabuleiro (3x3)
Máximo de Capturas: 1
Tempo de execução:
Tempo Real: 0.000001 segundos
Tempo Usuário: 0.000000 segundos
Tempo Sistema: 0.000001 segundos
Tempo Total CPU: 0.000001 segundos

Tabuleiro (5x3)
Máximo de Capturas: 2
Tempo de execução:
Tempo Real: 0.000001 segundos
Tempo Usuário: 0.000000 segundos
Tempo Sistema: 0.000002 segundos
Tempo Total CPU: 0.000002 segundos

Tabuleiro (8x8)
Máximo de Capturas: 7
Tempo de execução:
Tempo Real: 0.000004 segundos
Tempo Usuário: 0.000000 segundos
Tempo Sistema: 0.000004 segundos
Tempo Total CPU: 0.000004 segundos

Tempo total de execução:
Tempo Real: 0.000084 segundos
Tempo Usuário: 0.000000 segundos
Tempo Sistema: 0.000083 segundos
Tempo Total CPU: 0.000083 segundos
```

## Documentação

- [📄 Instruções para o desenvolvimento do trabalho](docs/tp1.pdf)

## Como Rodar o Programa

### Passo 1: Compilação

Use o `make` para compilar o programa:

```bash
make
```

### Passo 2: Execução

Para rodar o programa, use o comando abaixo, passando o arquivo de entrada como argumento:

```bash
./tp1 -i entrada.txt
```

Onde `entrada.txt` contém a configuração inicial do tabuleiro e as peças.

## Licença

Este projeto é de uso acadêmico, com fins exclusivos para a resolução de um trabalho de faculdade.
