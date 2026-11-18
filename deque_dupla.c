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
    /* TODO */
    return NULL;
}

void deque_destruir(Deque *d) {
    /* TODO */
    (void)d;
}

int deque_tamanho(const Deque *d) {
    /* TODO */
    (void)d;
    return 0;
}

int deque_vazio(const Deque *d) {
    /* TODO */
    (void)d;
    return 1;
}

int deque_inserir_inicio(Deque *d, Voo x) {
    /* TODO */
    (void)d;
    (void)x;
    return 0;
}

int deque_inserir_fim(Deque *d, Voo x) {
    /* TODO */
    (void)d;
    (void)x;
    return 0;
}

int deque_remover_inicio(Deque *d, Voo *x) {
    /* TODO */
    (void)d;
    (void)x;
    return 0;
}

int deque_remover_fim(Deque *d, Voo *x) {
    /* TODO */
    (void)d;
    (void)x;
    return 0;
}

int deque_primeiro(const Deque *d, Voo *x) {
    /* TODO */
    (void)d;
    (void)x;
    return 0;
}

int deque_ultimo(const Deque *d, Voo *x) {
    /* TODO */
    (void)d;
    (void)x;
    return 0;
}
