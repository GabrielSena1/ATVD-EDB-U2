/* lista_dupla.c - TAD Lista em LISTA DUPLAMENTE ENCADEADA (questao 1).
 *
 * Complete as funcoes abaixo com uma lista dupla circular com sentinela
 * (um no sem item antes do primeiro e depois do ultimo), como no
 * pseudocodigo da aula 8: para chegar a posicao i, ande pelo lado mais
 * perto (no maximo n/2 passos).
 * Confira com: make q1 LISTA=dupla
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
    No *ant;
    No *prox;
};

struct Lista {
    No *sent; /* sentinela: vazia, aponta para si mesmo */
    int n;
};

Lista *lista_criar(void) {
    Lista *l = malloc(sizeof *l);
    if (l == NULL)
        return NULL;
    l->sent = malloc(sizeof *l->sent);
    if (l->sent == NULL) {
        free(l);
        return NULL;
    }
    l->sent->ant = l->sent;
    l->sent->prox = l->sent;
    l->n = 0;
    return l;
}

void lista_destruir(Lista *l) {
    if (l == NULL)
        return;
    No *no = l->sent->prox;
    while (no != l->sent) {
        No *prox = no->prox;
        free(no);
        no = prox;
    }
    free(l->sent);
    free(l);
}

int lista_tamanho(const Lista *l) {
    return l->n;
}

int lista_vazia(const Lista *l) {
    return l->n == 0;
}

/* no na posicao i (0 a n - 1), andando pelo lado mais perto */
static No *no_na_posicao(const Lista *l, int i) {
    No *no;
    if (i <= l->n / 2) {
        no = l->sent->prox;
        for (int j = 0; j < i; j++)
            no = no->prox;
    } else {
        no = l->sent->ant;
        for (int j = l->n - 1; j > i; j--)
            no = no->ant;
    }
    return no;
}

int lista_obter(const Lista *l, int i, Voo *x) {
    if (i < 0 || i >= l->n)
        return 0;
    *x = no_na_posicao(l, i)->item;
    return 1;
}

int lista_inserir(Lista *l, int i, Voo x) {
    if (i < 0 || i > l->n)
        return 0;
    No *novo = malloc(sizeof *novo);
    if (novo == NULL)
        return 0;
    novo->item = x;
    /* depois de inserir em i, o no que ocupava i (ou sent se i == n)
       fica logo apos o novo no */
    No *depois = (i == l->n) ? l->sent : no_na_posicao(l, i);
    No *antes = depois->ant;
    novo->ant = antes;
    novo->prox = depois;
    antes->prox = novo;
    depois->ant = novo;
    l->n++;
    return 1;
}

int lista_remover(Lista *l, int i, Voo *x) {
    if (i < 0 || i >= l->n)
        return 0;
    No *alvo = no_na_posicao(l, i);
    *x = alvo->item;
    alvo->ant->prox = alvo->prox;
    alvo->prox->ant = alvo->ant;
    free(alvo);
    l->n--;
    return 1;
}

int lista_buscar(const Lista *l, const char *codigo) {
    No *no = l->sent->prox;
    int i = 0;
    while (no != l->sent) {
        if (strcmp(no->item.codigo, codigo) == 0)
            return i;
        no = no->prox;
        i++;
    }
    return -1;
}