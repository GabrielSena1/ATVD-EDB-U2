/* deque.h - a interface do TAD Deque (questao 4, aula 11).
 *
 * NAO MODIFIQUE ESTE ARQUIVO. A espera para pouso (aproximacao.c) so
 * conhece este contrato; deque_circular.c e deque_dupla.c tem que
 * cumpri-lo exatamente.
 *
 * Deque e a fila de duas pontas: entra e sai pelo inicio e pelo fim. As
 * funcoes que podem falhar devolvem 1 para sucesso e 0 para falha (deque
 * vazio ou falta de memoria).
 */

#ifndef DEQUE_H
#define DEQUE_H

#include "voo.h"

// #trecho: ciclo
typedef struct Deque Deque;

Deque *deque_criar(void);
void deque_destruir(Deque *d);

int deque_tamanho(const Deque *d);
int deque_vazio(const Deque *d);
// #fim: ciclo

// #trecho: pontas
int deque_inserir_inicio(Deque *d, Voo x);
int deque_inserir_fim(Deque *d, Voo x);
int deque_remover_inicio(Deque *d, Voo *x);
int deque_remover_fim(Deque *d, Voo *x);
// #fim: pontas

// #trecho: consulta
int deque_primeiro(const Deque *d, Voo *x);
int deque_ultimo(const Deque *d, Voo *x);
// #fim: consulta

#endif /* DEQUE_H */
