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
    Deque *d = malloc(sizeof *d);
    if (d == NULL)
        return NULL;
    d->cap = 4;
    d->ini = 0;
    d->n = 0;
    d->itens = malloc(d->cap * sizeof *d->itens);
    if (d->itens == NULL) {
        free(d);
        return NULL;
    }
    return d;
}

void deque_destruir(Deque *d) {
    if (d == NULL)
        return;
    free(d->itens);
    free(d);
}

int deque_tamanho(const Deque *d) {
    return d->n;
}

int deque_vazio(const Deque *d) {
    return d->n == 0;
}

/* copia os itens na ordem logica para um bloco de capacidade dobrada */
static int deque_crescer(Deque *d) {
    int novo_cap = d->cap * 2;
    Voo *novo = malloc(novo_cap * sizeof *novo);
    if (novo == NULL)
        return 0;
    for (int i = 0; i < d->n; i++)
        novo[i] = d->itens[(d->ini + i) % d->cap];
    free(d->itens);
    d->itens = novo;
    d->cap = novo_cap;
    d->ini = 0;
    return 1;
}

int deque_inserir_inicio(Deque *d, Voo x) {
    if (d->n == d->cap && !deque_crescer(d))
        return 0;
    d->ini = (d->ini - 1 + d->cap) % d->cap;
    d->itens[d->ini] = x;
    d->n++;
    return 1;
}

int deque_inserir_fim(Deque *d, Voo x) {
    if (d->n == d->cap && !deque_crescer(d))
        return 0;
    int fim = (d->ini + d->n) % d->cap;
    d->itens[fim] = x;
    d->n++;
    return 1;
}

int deque_remover_inicio(Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    *x = d->itens[d->ini];
    d->ini = (d->ini + 1) % d->cap;
    d->n--;
    return 1;
}

int deque_remover_fim(Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    int fim = (d->ini + d->n - 1) % d->cap;
    *x = d->itens[fim];
    d->n--;
    return 1;
}

int deque_primeiro(const Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    *x = d->itens[d->ini];
    return 1;
}

int deque_ultimo(const Deque *d, Voo *x) {
    if (d->n == 0)
        return 0;
    int fim = (d->ini + d->n - 1) % d->cap;
    *x = d->itens[fim];
    return 1;
}