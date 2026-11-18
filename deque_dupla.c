/* deque_dupla.c - TAD Deque em LISTA DUPLA COM SENTINELA (questao 4).
 *
 * Complete as funcoes abaixo como no pseudocodigo da aula 11: sent->prox
 * e o primeiro e sent->ant e o ultimo. Duas funcoes auxiliares (ligar um
 * no antes de outro e desligar um no) bastam para as quatro pontas.
 * Confira com: make q4 DEQUE=dupla
 *
 * Regras do contrato (deque.h):
 *   - entra e sai pelas duas pontas; as quatro operacoes de pontas e as
 *     duas consultas custam O(1) (amortizado, no vetor);
 *   - remover, deque_primeiro e deque_ultimo devolvem 0 com o deque vazio;
 *   - deque_destruir libera toda a memoria e aceita NULL.
 *
 * Enquanto deque_criar devolver NULL, os comandos da questao 4 avisam.
 */

#include <stdlib.h>
#include "deque.h"

typedef struct No No;
struct No {
    Voo item;
    No *ant;
    No *prox;
};

struct Deque {
    No *sent; /* sent->prox e o primeiro; sent->ant, o ultimo */
    int n;
};

Deque *deque_criar(void) {
    Deque *d = malloc(sizeof *d);
    if (d == NULL)
        return NULL;
    d->sent = malloc(sizeof *d->sent);
    if (d->sent == NULL) {
        free(d);
        return NULL;
    }
    d->sent->ant = d->sent;
    d->sent->prox = d->sent;
    d->n = 0;
    return d;
}

void deque_destruir(Deque *d) {
    if (d == NULL)
        return;
    No *no = d->sent->prox;
    while (no != d->sent) {
        No *prox = no->prox;
        free(no);
        no = prox;
    }
    free(d->sent);
    free(d);
}

int deque_tamanho(const Deque *d) {
    return d->n;
}

int deque_vazio(const Deque *d) {
    return d->n == 0;
}

/* liga novo logo antes de depois */
static void ligar(No *novo, No *depois) {
    No *antes = depois->ant;
    novo->ant = antes;
    novo->prox = depois;
    antes->prox = novo;
    depois->ant = novo;
}

/* desliga o no da lista e devolve o item */
static void desligar(No *no, Voo *x) {
    *x = no->item;
    no->ant->prox = no->prox;
    no->prox->ant = no->ant;
    free(no);
}

int deque_inserir_inicio(Deque *d, Voo x) {
    No *novo = malloc(sizeof *novo);
    if (novo == NULL)
        return 0;
    novo->item = x;
    ligar(novo, d->sent->prox);
    d->n++;
    return 1;
}

int deque_inserir_fim(Deque *d, Voo x) {
    No *novo = malloc(sizeof *novo);
    if (novo == NULL)
        return 0;
    novo->item = x;
    ligar(novo, d->sent);
    d->n++;
    return 1;
}

int deque_remover_inicio(Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    desligar(d->sent->prox, x);
    d->n--;
    return 1;
}

int deque_remover_fim(Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    desligar(d->sent->ant, x);
    d->n--;
    return 1;
}

int deque_primeiro(const Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    *x = d->sent->prox->item;
    return 1;
}

int deque_ultimo(const Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    *x = d->sent->ant->item;
    return 1;
}