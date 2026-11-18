/* fila_circular.c - TAD Fila em VETOR CIRCULAR (questao 2).
 *
 * Complete as funcoes abaixo como no pseudocodigo da aula 9:
 *   - itens: o bloco; ini: a celula da frente; n: quantos estao na fila;
 *   - o fim fica em (ini + n) % cap, e ninguem se move ao desenfileirar;
 *   - comece com cap = 4 e DOBRE quando lotar, copiando os itens para o
 *     bloco novo na ordem da fila (da frente para o fim).
 * Confira com: make q2 FILA=circular
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

struct Fila {
    Voo *itens;
    int ini; /* a celula da frente */
    int n;   /* quantos estao na fila */
    int cap; /* tamanho do bloco */
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
