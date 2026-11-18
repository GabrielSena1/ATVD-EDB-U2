/* lista_simples.c - TAD Lista em LISTA SIMPLESMENTE ENCADEADA (questao 1).
 *
 * Complete as funcoes abaixo com um no-cabeca (um no sem item antes do
 * primeiro) e um ponteiro para o ultimo no, como no pseudocodigo da aula
 * 8: inserir no fim usa a cauda e nao percorre a lista.
 * Confira com: make q1 LISTA=simples
 *
 * Regras do contrato (lista.h):
 *   - indices de 0 a n - 1; lista_inserir aceita i de 0 a n;
 *   - funcoes que podem falhar devolvem 1 (sucesso) ou 0 (falha);
 *   - lista_buscar compara o codigo com strcmp e devolve o indice, ou -1;
 *   - lista_destruir libera toda a memoria e aceita NULL.
 *
 * Enquanto lista_criar devolver NULL, a torre avisa e para.
 */

#include <stdlib.h>
#include <string.h>
#include "lista.h"

typedef struct No No;
struct No {
    Voo item;
    No *prox;
};

struct Lista {
    No *cab;   /* no-cabeca, sem item */
    No *cauda; /* o ultimo no (cab se vazia) */
    int n;
};

Lista *lista_criar(void) {
    Lista *l = malloc(sizeof *l);
    if (l == NULL)
        return NULL;
    l->cab = malloc(sizeof *l->cab);
    if (l->cab == NULL) {
        free(l);
        return NULL;
    }
    l->cab->prox = NULL;
    l->cauda = l->cab;
    l->n = 0;
    return l;
}

void lista_destruir(Lista *l) {
    if (l == NULL)
        return;
    No *no = l->cab;
    while (no != NULL) {
        No *prox = no->prox;
        free(no);
        no = prox;
    }
    free(l);
}

int lista_tamanho(const Lista *l) {
    return l->n;
}

int lista_vazia(const Lista *l) {
    return l->n == 0;
}

/* devolve o no na posicao i - 1 (cab se i == 0) */
static No *no_anterior(const Lista *l, int i) {
    No *no = l->cab;
    for (int j = 0; j < i; j++)
        no = no->prox;
    return no;
}

int lista_obter(const Lista *l, int i, Voo *x) {
    if (i < 0 || i >= l->n)
        return 0;
    *x = no_anterior(l, i)->prox->item;
    return 1;
}

int lista_inserir(Lista *l, int i, Voo x) {
    if (i < 0 || i > l->n)
        return 0;
    No *novo = malloc(sizeof *novo);
    if (novo == NULL)
        return 0;
    novo->item = x;
    No *ant = no_anterior(l, i);
    novo->prox = ant->prox;
    ant->prox = novo;
    if (novo->prox == NULL)
        l->cauda = novo;
    l->n++;
    return 1;
}

int lista_remover(Lista *l, int i, Voo *x) {
    if (i < 0 || i >= l->n)
        return 0;
    No *ant = no_anterior(l, i);
    No *alvo = ant->prox;
    *x = alvo->item;
    ant->prox = alvo->prox;
    if (alvo == l->cauda)
        l->cauda = ant;
    free(alvo);
    l->n--;
    return 1;
}

int lista_buscar(const Lista *l, const char *codigo) {
    No *no = l->cab->prox;
    int i = 0;
    while (no != NULL) {
        if (strcmp(no->item.codigo, codigo) == 0)
            return i;
        no = no->prox;
        i++;
    }
    return -1;
}