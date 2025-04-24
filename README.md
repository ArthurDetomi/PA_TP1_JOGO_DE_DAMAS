# Trabalho prático de Projeto e Analise de Algoritmos

## Problema

Este é um jogo de damas adaptado, jogado em um tabuleiro retangular com N linhas e M colunas. As peças se movimentam pulando na diagonal sobre peças do oponente, indo para a casa vazia logo após. É possível capturar tanto para frente quanto para trás.

Também é permitido fazer capturas múltiplas com uma mesma peça, pulando sobre várias peças em sequência, mudando de direção se necessário. Não pode pular sobre a mesma peça duas vezes, nem sobre as próprias peças.

Dado o estado atual do tabuleiro, o programa deve calcular o máximo de peças adversárias que podem ser capturadas em uma única jogada.

A entrada contém vários casos de teste e termina com 0 0. A solução deve ser feita de duas formas: uma usando força bruta e outra mais eficiente.

## 💻 Pré-requisitos

Antes de começar, verifique se você atendeu aos seguintes requisitos:
Você instalou um compilador C (como gcc) e a versão mais recente do make.

Você leu este README até o final para entender como compilar e executar o programa.

## 🚀 Compilando o código <nome_do_projeto>

Para compilar o código, siga estas etapas:

- Estando na pasta do projeto, rode o seguinte comando:

```bash
make
```

---

## ☕ Rodando o programa

Para rodar o programa, utilize o seguinte formato:

```bash
./tp1 {estratégia} -i entrada.txt -o saida.txt
```

- `{estratégia}` deve ser `1` para usar a abordagem de força bruta ou `2` para usar a abordagem mais eficiente (backtracking).
- Os parâmetros de estratégia (`1` ou `2`) e o arquivo de entrada (`-i`) **são obrigatórios**.
- O parâmetro de saída (`-o`) é **opcional**. Se for omitido, o arquivo de saída será criado automaticamente no diretório `output/` com o nome `output.txt`.
- Sempre que um nome de arquivo de saída for fornecido, ele será utilizado.

Exemplos:

```bash
./tp1 1 -i entrada.txt
# Gera o arquivo output/output.txt

./tp1 2 -i entrada.txt -o resultado.txt
# Gera o arquivo resultado.txt
```

## Estrutura do projeto

🔗 [Acesse este repositório no GitHub](https://github.com/ArthurDetomi/PA_TP1_JOGO_DE_DAMAS)

- A documentação segue-se no diretorio /docs

[Documentação](/docs/Documentação%20TP1%20-%20Oscar%20e%20Arthur%20Geraldo.pdf)

[Instruções](/docs/tp1.pdf)

## 🤝 Dupla

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/arthurdetomi" title="Perfil do GitHub de Geraldo Arthur">
        <img src="https://avatars.githubusercontent.com/u/99772832?v=4" width="100px;" alt="Foto do perfil do Geraldo Arthur Detomi no GitHub"/><br>
        <sub>
          <b>Geraldo Arthur Detomi</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/HomoGodzilla" title="Perfil do GitHub de Oscar Alves">
        <img src="https://avatars.githubusercontent.com/u/89045220?v=4" width="100px;" alt="Foto do perfil do Oscar Alves no GitHub"/><br>
        <sub>
          <b>Oscar Alves</b>
        </sub>
      </a>
    </td>
  </tr>
</table>
