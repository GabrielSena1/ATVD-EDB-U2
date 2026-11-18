/* pilha.h - a interface do TAD Pilha (questao 3, aula 10).
 *
 * NAO MODIFIQUE ESTE ARQUIVO. O hangar (hangar.c) so conhece este
 * contrato; pilha_vetor.c e pilha_encadeada.c tem que cumpri-lo
 * exatamente.
 *
 * O ultimo a entrar e o primeiro a sair: pilha_empilhar poe no topo,
 * pilha_desempilhar tira do topo. As funcoes que podem falhar devolvem 1
 * para sucesso e 0 para falha (pilha vazia ou falta de memoria).
 */

#ifndef PILHA_H
#define PILHA_H

#include "voo.h"

// #trecho: ciclo
typedef struct Pilha Pilha;

Pilha *pilha_criar(void);
void pilha_destruir(Pilha *p);

int pilha_tamanho(const Pilha *p);
int pilha_vazia(const Pilha *p);
// #fim: ciclo

// #trecho: operacoes
int pilha_empilhar(Pilha *p, Voo x);
int pilha_desempilhar(Pilha *p, Voo *x);
int pilha_topo(const Pilha *p, Voo *x);
// #fim: operacoes

#endif /* PILHA_H */
