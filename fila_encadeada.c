/* fila_encadeada.c - TAD Fila em LISTA ENCADEADA (questao 2).
 *
 * Complete as funcoes abaixo como no pseudocodigo da aula 9: um ponteiro
 * para o inicio (sai daqui) e outro para o fim (entra depois dele), para
 * que enfileirar e desenfileirar custem O(1). Cuidado com a fila que
 * fica vazia: o fim tambem tem que voltar a NULL.
 * Confira com: make q2 FILA=encadeada
 *
 * Regras do contrato (fila.h):
 *   - fila_enfileirar poe no fim; fila_desenfileirar tira da frente;
 *   - fila_desenfileirar e fila_frente devolvem 0 com a fila vazia;
 *   - fila_destruir libera toda a memoria e aceita NULL.
 *
 * Enquanto fila_criar devolver NULL, os comandos da questao 2 avisam.
 */

#include <stdlib.h>
#include "fila.h"

typedef struct No No;
struct No {
    Voo item;
    No *prox;
};

struct Fila {
    No *inicio; /* a frente: sai daqui */
    No *fim;    /* o ultimo: entra depois dele */
    int n;
};

Fila *fila_criar(void) {
    /* TODO */
    return NULL;
}

void fila_destruir(Fila *f) {
    /* TODO */
    (void)f;
}

int fila_tamanho(const Fila *f) {
    /* TODO */
    (void)f;
    return 0;
}

int fila_vazia(const Fila *f) {
    /* TODO */
    (void)f;
    return 1;
}

int fila_enfileirar(Fila *f, Voo x) {
    /* TODO */
    (void)f;
    (void)x;
    return 0;
}

int fila_desenfileirar(Fila *f, Voo *x) {
    /* TODO */
    (void)f;
    (void)x;
    return 0;
}

int fila_frente(const Fila *f, Voo *x) {
    /* TODO */
    (void)f;
    (void)x;
    return 0;
}
