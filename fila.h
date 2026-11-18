/* fila.h - a interface do TAD Fila (questao 2, aula 9).
 *
 * NAO MODIFIQUE ESTE ARQUIVO. A cabeceira da pista (pista.c) so conhece
 * este contrato; fila_circular.c e fila_encadeada.c tem que cumpri-lo
 * exatamente.
 *
 * Quem entra primeiro sai primeiro: fila_enfileirar poe no fim,
 * fila_desenfileirar tira da frente. As funcoes que podem falhar devolvem
 * 1 para sucesso e 0 para falha (fila vazia ou falta de memoria).
 */

#ifndef FILA_H
#define FILA_H

#include "voo.h"

// #trecho: ciclo
typedef struct Fila Fila;

Fila *fila_criar(void);
void fila_destruir(Fila *f);

int fila_tamanho(const Fila *f);
int fila_vazia(const Fila *f);
// #fim: ciclo

// #trecho: operacoes
int fila_enfileirar(Fila *f, Voo x);
int fila_desenfileirar(Fila *f, Voo *x);
int fila_frente(const Fila *f, Voo *x);
// #fim: operacoes

#endif /* FILA_H */
