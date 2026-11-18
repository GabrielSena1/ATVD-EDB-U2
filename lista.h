/* lista.h - a interface do TAD Lista (questao 1, aula 8).
 *
 * NAO MODIFIQUE ESTE ARQUIVO. A grade de partidas (grade.c) so conhece
 * este contrato; lista_vetor.c, lista_simples.c e lista_dupla.c tem que
 * cumpri-lo exatamente.
 *
 * Os indices vao de 0 a n - 1. As funcoes que podem falhar devolvem 1
 * para sucesso e 0 para falha (indice invalido ou falta de memoria).
 * lista_buscar devolve -1 quando o codigo nao esta na lista.
 */

#ifndef LISTA_H
#define LISTA_H

#include "voo.h"

// #trecho: ciclo
typedef struct Lista Lista;

Lista *lista_criar(void);
void lista_destruir(Lista *l);

int lista_tamanho(const Lista *l);
int lista_vazia(const Lista *l);
// #fim: ciclo

// #trecho: posicao
int lista_obter(const Lista *l, int i, Voo *x);
int lista_inserir(Lista *l, int i, Voo x);
int lista_remover(Lista *l, int i, Voo *x);
int lista_buscar(const Lista *l, const char *codigo);
// #fim: posicao

#endif /* LISTA_H */
