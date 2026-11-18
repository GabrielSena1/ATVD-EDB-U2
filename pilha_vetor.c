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
    Pilha *p = malloc(sizeof *p);
    if (p == NULL)
        return NULL;
    p->cap = 8;
    p->n = 0;
    p->itens = malloc(p->cap * sizeof *p->itens);
    if (p->itens == NULL) {
        free(p);
        return NULL;
    }
    return p;
}

void pilha_destruir(Pilha *p) {
    if (p == NULL)
        return;
    free(p->itens);
    free(p);
}

int pilha_tamanho(const Pilha *p) {
    return p->n;
}

int pilha_vazia(const Pilha *p) {
    return p->n == 0;
}

int pilha_empilhar(Pilha *p, Voo x) {
    if (p->n == p->cap) {
        int novo_cap = p->cap * 2;
        Voo *novo = realloc(p->itens, novo_cap * sizeof *novo);
        if (novo == NULL)
            return 0;
        p->itens = novo;
        p->cap = novo_cap;
    }
    p->itens[p->n] = x;
    p->n++;
    return 1;
}

int pilha_desempilhar(Pilha *p, Voo *x) {
    if (p->n == 0)
        return 0;
    p->n--;
    *x = p->itens[p->n];
    return 1;
}

int pilha_topo(const Pilha *p, Voo *x) {
    if (p->n == 0)
        return 0;
    *x = p->itens[p->n - 1];
    return 1;
}