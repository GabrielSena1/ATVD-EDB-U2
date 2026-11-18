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
    Fila *f = malloc(sizeof *f);
    if (f == NULL)
        return NULL;
    f->cap = 4;
    f->ini = 0;
    f->n = 0;
    f->itens = malloc(f->cap * sizeof *f->itens);
    if (f->itens == NULL) {
        free(f);
        return NULL;
    }
    return f;
}

void fila_destruir(Fila *f) {
    if (f == NULL)
        return;
    free(f->itens);
    free(f);
}

int fila_tamanho(const Fila *f) {
    return f->n;
}

int fila_vazia(const Fila *f) {
    return f->n == 0;
}

int fila_enfileirar(Fila *f, Voo x) {
    if (f->n == f->cap) {
        int novo_cap = f->cap * 2;
        Voo *novo = malloc(novo_cap * sizeof *novo);
        if (novo == NULL)
            return 0;
        for (int i = 0; i < f->n; i++)
            novo[i] = f->itens[(f->ini + i) % f->cap];
        free(f->itens);
        f->itens = novo;
        f->cap = novo_cap;
        f->ini = 0;
    }
    int fim = (f->ini + f->n) % f->cap;
    f->itens[fim] = x;
    f->n++;
    return 1;
}

int fila_desenfileirar(Fila *f, Voo *x) {
    if (f->n == 0)
        return 0;
    *x = f->itens[f->ini];
    f->ini = (f->ini + 1) % f->cap;
    f->n--;
    return 1;
}

int fila_frente(const Fila *f, Voo *x) {
    if (f->n == 0)
        return 0;
    *x = f->itens[f->ini];
    return 1;
}