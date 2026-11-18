/* deque_circular.c - TAD Deque em VETOR CIRCULAR (questao 4).
 *
 * Complete as funcoes abaixo como no pseudocodigo da aula 11: ini e a
 * celula do primeiro e anda para os dois lados; o ultimo fica em
 * (ini + n - 1) % cap. Inserir no inicio recua ini somando cap antes do
 * resto da divisao. Comece com cap = 4 e DOBRE quando lotar.
 * Confira com: make q4 DEQUE=circular
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

struct Deque {
    Voo *itens;
    int ini; /* a celula do primeiro */
    int n;   /* quantos ha */
    int cap;
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
