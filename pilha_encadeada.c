/* pilha_encadeada.c - TAD Pilha em LISTA ENCADEADA (questao 3).
 *
 * Complete as funcoes abaixo como no pseudocodigo da aula 10: o topo e o
 * primeiro no, e empilhar e desempilhar mexem so nele.
 * Confira com: make q3 PILHA=encadeada
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

typedef struct No No;
struct No {
    Voo item;
    No *prox; /* aponta para baixo */
};

struct Pilha {
    No *topo; /* NULL se vazia */
    int n;
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
