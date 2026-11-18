/* pilha_vetor.c - TAD Pilha em VETOR (questao 3).
 *
 * Complete as funcoes abaixo como no pseudocodigo da aula 10: a base e
 * itens[0] e o topo e itens[n - 1]; comece com cap = 8 e DOBRE
 * (realloc) quando lotar.
 * Confira com: make q3 PILHA=vetor
 *
 * Regras do contrato (pilha.h):
 *   - pilha_empilhar poe no topo; pilha_desempilhar tira do topo;
 *   - pilha_desempilhar e pilha_topo devolvem 0 com a pilha vazia;
 *   - pilha_destruir libera toda a memoria e aceita NULL.
 *
 * Enquanto pilha_criar devolver NULL, os comandos da questao 3 avisam.
 */

#include <stdlib.h>
#include "pilha.h"

struct Pilha {
    Voo *itens; /* a base e itens[0] */
    int n;      /* o topo e itens[n - 1] */
    int cap;
};

Pilha *pilha_criar(void) {
    /* TODO */
    return NULL;
}

void pilha_destruir(Pilha *p) {
    /* TODO */
    (void)p;
}

int pilha_tamanho(const Pilha *p) {
    /* TODO */
    (void)p;
    return 0;
}

int pilha_vazia(const Pilha *p) {
    /* TODO */
    (void)p;
    return 1;
}

int pilha_empilhar(Pilha *p, Voo x) {
    /* TODO */
    (void)p;
    (void)x;
    return 0;
}

int pilha_desempilhar(Pilha *p, Voo *x) {
    /* TODO */
    (void)p;
    (void)x;
    return 0;
}

int pilha_topo(const Pilha *p, Voo *x) {
    /* TODO */
    (void)p;
    (void)x;
    return 0;
}
