# A torre de controle: lista, fila, pilha e deque

[![Conferir](https://github.com/varellalexandre/tads_sequencia/actions/workflows/conferir.yml/badge.svg)](https://github.com/varellalexandre/tads_sequencia/actions/workflows/conferir.yml)

IMD0029 · Estrutura de Dados Básicas I · Lista Unidade 2 · 2026.2 · Prof. Alexandre Varella

## O problema

A torre de controle do aeroporto de São Gonçalo do Amarante cuida de quatro coisas ao mesmo tempo: a grade de partidas do dia, a fila de aviões na cabeceira da pista, o hangar de manutenção e os aviões que circulam esperando para pousar.

O programa da torre já existe e lê os comandos do dia num arquivo de texto. Só que cada uma das quatro partes guarda os voos atrás de um contrato (um `.h`) que ainda não tem implementação. Cada questão desta lista dá vida a uma dessas partes, e o mesmo executável passa a responder a mais comandos a cada questão resolvida.

▶️ **Assista ao short que explica a lógica do exercício:** [youtube.com/shorts/_YyiMebafPE](https://www.youtube.com/shorts/_YyiMebafPE)

O item que passa pelas quatro estruturas é o `Voo`, declarado em `voo.h`:

| Campo | Tipo | Significado |
|---|---|---|
| `codigo` | `char[8]` | companhia e número, por exemplo `AD4521` |
| `horario` | `int` | horário em hhmm: 1430 é 14h30 |
| `cidade` | `char[24]` | destino ou origem do voo |

## Quais arquivos você modifica

Você modifica **só estes 9 arquivos**, os esqueletos dos TADs:

| Questão | TAD | Arquivos que você completa |
|---|---|---|
| 1 | Lista | `lista_vetor.c`, `lista_simples.c`, `lista_dupla.c` |
| 2 | Fila | `fila_circular.c`, `fila_encadeada.c` |
| 3 | Pilha | `pilha_vetor.c`, `pilha_encadeada.c` |
| 4 | Deque | `deque_circular.c`, `deque_dupla.c` |

Em cada esqueleto, as funções estão marcadas com `/* TODO */`, e os campos da `struct` já estão declarados. São esses 9 arquivos que você entrega.

Todo o resto fica como veio:

| Arquivos | O que são |
|---|---|
| `voo.h`, `lista.h`, `fila.h`, `pilha.h`, `deque.h`, `torre.h` | os contratos |
| `main.c`, `torre.c`, `grade.c`, `pista.c`, `hangar.c`, `aproximacao.c` | a torre pronta, que usa os contratos |
| `Makefile` | compila, roda e confere cada questão |
| `entradas/`, `esperadas/` | os cenários de cada questão e as saídas que a torre tem que imprimir |
| `README.md`, `.gitignore`, `.github/` | esta explicação, o que o git ignora e a integração contínua |

## As quatro questões

| Questão | Parte da torre | TAD | Você completa | Confere com |
|---|---|---|---|---|
| 1 | grade de partidas | Lista | `lista_vetor.c` `lista_simples.c` `lista_dupla.c` | `make q1` |
| 2 | cabeceira da pista | Fila | `fila_circular.c` `fila_encadeada.c` | `make q2` |
| 3 | hangar de manutenção | Pilha | `pilha_vetor.c` `pilha_encadeada.c` | `make q3` |
| 4 | espera para pouso | Deque | `deque_circular.c` `deque_dupla.c` | `make q4` |

As questões dependem umas das outras. A questão 2 precisa da lista pronta, porque a fila recebe os voos da grade. A 3 precisa da lista, mas não da fila. A 4 usa os quatro TADs.

Cada questão pede o mesmo TAD em todas as representações vistas em aula, e só está resolvida quando `make qN` imprime `OK` em todas elas.

### Questão 1 · A grade de partidas

A grade guarda os voos do dia em ordem de horário. Em empate, quem foi programado antes sai antes. Os comandos `PROGRAMA`, `CANCELA`, `ATRASA` e `GRADE` (em `grade.c`) inserem na posição certa, procuram pelo código do voo, removem do meio e reposicionam um voo atrasado, sempre pelo contrato `lista.h`.

Implemente as oito funções de `lista.h` três vezes, uma por representação vista na aula 8. Os campos de cada `struct` já estão declarados nos esqueletos.

- Vetor: começa com capacidade 8 e dobra quando lota; `lista_obter` custa O(1), inserir e remover deslocam os vizinhos.
- Lista simples com nó-cabeça e ponteiro para o último nó: inserir no fim não percorre a lista, e remover o último atualiza esse ponteiro.
- Lista dupla circular com sentinela: para chegar à posição i, ande pelo lado mais perto (no máximo n/2 passos).
- `lista_buscar` compara o código com `strcmp` e devolve o índice, ou -1.
- `make q1` imprime `OK` nas três representações, e `make q1 SAN=1` também, sem nenhum erro do sanitizer.

### Questão 2 · A cabeceira da pista

Quando o relógio da torre passa do horário de um voo, ele sai da frente da grade e taxia até a cabeceira, onde espera a vez de decolar: quem chegou primeiro decola primeiro. Os comandos `RELOGIO`, `DECOLA` e `PISTA` (em `pista.c`) usam o contrato `fila.h`. Como a fila não tem acesso por posição, `PISTA` mostra a cabeceira girando a fila uma volta inteira: tira da frente, imprime e põe de volta no fim.

Implemente as sete funções de `fila.h` em `fila_circular.c` e em `fila_encadeada.c`, as duas representações da aula 9.

- Vetor circular: `ini` marca a frente, o fim fica em `(ini + n) % cap` e ninguém se move ao desenfileirar; começa com capacidade 4 e dobra quando lota.
- Ao dobrar, os itens vão para o bloco novo na ordem da fila, da frente para o fim, e não na ordem das células.
- Lista encadeada com ponteiros para o início e o fim: enfileirar e desenfileirar custam O(1); quando a fila esvazia, o fim também volta a NULL.
- `make q2` imprime `OK` nas duas representações, e `make q2 SAN=1` também, sem nenhum erro do sanitizer.

### Questão 3 · O hangar de manutenção

O hangar é um corredor estreito com uma porta só: o último avião rebocado para dentro fica na porta e é o primeiro que consegue sair. Para liberar um avião do fundo, os que estão na frente dele saem para o pátio, numa segunda pilha, e voltam depois na mesma ordem. Os comandos `PANE`, `LIBERA` e `HANGAR` (em `hangar.c`) usam o contrato `pilha.h`, e um avião liberado volta para a grade num horário novo.

Implemente as sete funções de `pilha.h` em `pilha_vetor.c` e em `pilha_encadeada.c`, as duas representações da aula 10.

- Vetor: a base é `itens[0]` e o topo é `itens[n - 1]`; começa com capacidade 8 e dobra quando lota.
- Lista encadeada: o topo é o primeiro nó, e empilhar e desempilhar mexem só nele, em O(1).
- `pilha_destruir` libera todos os nós e aceita NULL: o pátio é criado e destruído a cada `LIBERA` e a cada `HANGAR`.
- `make q3` imprime `OK` nas duas representações, e `make q3 SAN=1` também, sem nenhum erro do sanitizer.

### Questão 4 · A espera para pouso

Os aviões que chegam circulam sobre o aeroporto esperando a vez de pousar. Quem chega entra no fim da espera; uma emergência (`MAYDAY`) entra no início; o primeiro pousa; e, se a espera fica longa demais, o último desiste e segue para o aeroporto alternativo. A pista é uma só, e pouso tem prioridade: enquanto houver avião na espera, `DECOLA` é recusado. Os comandos ficam em `aproximacao.c` e usam o contrato `deque.h`.

Implemente as dez funções de `deque.h` em `deque_circular.c` e em `deque_dupla.c`, as duas representações da aula 11. A entrada `entradas/q4.txt` é a tarde inteira da torre e usa os quatro TADs, então a questão 4 só passa com as questões 1, 2 e 3 prontas.

- Vetor circular: `ini` anda para os dois lados; inserir no início recua `ini` somando a capacidade antes do resto da divisão; começa com capacidade 4 e dobra quando lota.
- Lista dupla circular com sentinela: `sent->prox` é o primeiro e `sent->ant` é o último; duas funções auxiliares, ligar e desligar um nó, atendem às quatro pontas.
- As quatro operações de ponta e as duas consultas custam O(1) (amortizado, no vetor).
- `make q4` imprime `OK` nas duas representações, e `make q4 SAN=1` também, sem nenhum erro do sanitizer.

## Os comandos da torre

| Comando | Questão | Arquivo |
|---|---|---|
| `PROGRAMA cod hhmm cidade` | 1 · grade | `grade.c` |
| `CANCELA cod` | 1 · grade | `grade.c` |
| `ATRASA cod hhmm` | 1 · grade | `grade.c` |
| `GRADE` | 1 · grade | `grade.c` |
| `RELOGIO hhmm` | 2 · pista | `pista.c` |
| `DECOLA` | 2 · pista | `pista.c` |
| `PISTA` | 2 · pista | `pista.c` |
| `PANE cod` | 3 · hangar | `hangar.c` |
| `LIBERA cod hhmm` | 3 · hangar | `hangar.c` |
| `HANGAR` | 3 · hangar | `hangar.c` |
| `CHEGA cod cidade` | 4 · espera | `aproximacao.c` |
| `MAYDAY cod cidade` | 4 · espera | `aproximacao.c` |
| `POUSA` | 4 · espera | `aproximacao.c` |
| `DESVIA` | 4 · espera | `aproximacao.c` |
| `ESPERA` | 4 · espera | `aproximacao.c` |

O arquivo de entrada tem um comando por linha, e linha que começa com `#` é comentário. Horário é sempre em hhmm: 1430 é 14h30.

## Como rodar

### Primeiro passo: a casca como veio

Antes de escrever qualquer linha, rode:

```console
$ make q1
```

Isso confirma que `gcc` e `make` funcionam na sua máquina. O resultado é `FALHOU`, e isso é o esperado: os esqueletos devolvem NULL em `lista_criar`, e a torre avisa e para.

### Conferir uma questão

`make qN` compila a torre, roda `entradas/qN.txt` e compara a saída com `esperadas/qN.txt`. Se as duas forem iguais, imprime `OK`; se não, imprime o diff e `FALHOU`.

Ao ler o diff, `<` é o que a torre deveria imprimir e `>` é o que ela imprimiu. Linhas como `31c31` dizem em que linha da saída está a diferença.

### Trocando a representação

A representação de cada TAD se escolhe na linha de comando:

| Variável | Valores | Padrão | Exemplo |
|---|---|---|---|
| `LISTA` | vetor · simples · dupla | vetor | `make q1 LISTA=dupla` |
| `FILA` | circular · encadeada | circular | `make q2 FILA=encadeada` |
| `PILHA` | vetor · encadeada | vetor | `make q3 PILHA=encadeada` |
| `DEQUE` | circular · dupla | circular | `make q4 DEQUE=dupla` |
| `SAN` | 1 liga o sanitizer | desligado | `make q2 SAN=1` |

`SAN=1` compila com `-fsanitize=address,undefined`, que acusa acesso inválido à memória e nó liberado duas vezes, apontando o arquivo e a linha. As variáveis se combinam: `make q4 LISTA=simples FILA=encadeada PILHA=encadeada DEQUE=dupla` compila a torre inteira só com representações encadeadas.

### Outros comandos

| Comando | O que faz |
|---|---|
| `make todas` | roda as quatro questões em todas as representações: nove combinações, uma linha cada |
| `make run arquivo.txt` | roda a torre com os comandos de um cenário seu |
| `make clean` | apaga o executável |

O `make run` usa o último executável compilado: para testar o seu cenário com a lista dupla, rode `make q1 LISTA=dupla` antes.

### No Windows

O melhor caminho é o WSL, onde `make` e o sanitizer funcionam. Sem o WSL, compile com o mesmo `gcc`, troque `./torre` por `torre.exe` e `diff` por `fc`:

```console
> gcc -Wall -Wextra -std=c11 -pedantic main.c torre.c grade.c pista.c hangar.c aproximacao.c lista_vetor.c fila_circular.c pilha_vetor.c deque_circular.c -o torre.exe
> torre.exe entradas\q1.txt > minha_q1.txt
> fc esperadas\q1.txt minha_q1.txt
```

Para outra representação, troque o nome do arquivo correspondente na linha do `gcc` (por exemplo, `lista_dupla.c` no lugar de `lista_vetor.c`).

## Antes de entregar

- `make todas` imprime só `OK`, em nove linhas.
- `make todas SAN=1` também imprime só `OK`, em nove linhas.
- A entrega é dos 9 arquivos de TAD no SIGAA.
- Altere só os 9 esqueletos: os contratos, a torre, o `Makefile`, as entradas e as saídas esperadas ficam como vieram.

## Integração contínua

A cada push, o GitHub roda as duas conferências (`make todas` e `make todas SAN=1`). O resultado aparece na aba **Actions** do repositório e no selo do topo deste README.

Num repositório recém-criado a partir da casca, o resultado é vermelho, e isso é o esperado: os esqueletos ainda não fazem nada. Ele fica verde quando as quatro questões estiverem resolvidas em todas as representações, com e sem o sanitizer.

## Arquivos protegidos

O arquivo `.github/CODEOWNERS` dá um dono aos arquivos fixos da torre: os contratos (`*.h`), a torre (`main.c`, `torre.c`, `grade.c`, `pista.c`, `hangar.c`, `aproximacao.c`), o `Makefile`, as pastas `entradas/` e `esperadas/`, além do próprio `.github/`, deste README e do `.gitignore`. Qualquer mudança neles precisa da aprovação do docente.

Os 9 esqueletos (`lista_*.c`, `fila_*.c`, `pilha_*.c`, `deque_*.c`) não têm dono e são livres: é neles que você trabalha.
