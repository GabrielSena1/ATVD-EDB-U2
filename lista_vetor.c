/* lista_vetor.c - TAD Lista em VETOR (questao 1).
 *
 * Complete as funcoes abaixo guardando os voos num vetor alocado com
 * malloc, como no pseudocodigo da aula 8: comece com cap = 8 e DOBRE
 * (realloc) quando lotar; inserir e remover deslocam os vizinhos.
 * Confira com: make q1 LISTA=vetor
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

struct Lista {
    Voo *itens; /* bloco contiguo */
    int n;      /* itens em uso */
    int cap;    /* posicoes reservadas */
};

Lista *lista_criar(void) {
    Lista *l = malloc(sizeof *l);
    if (l == NULL)
        return NULL;
    l->cap = 8;
    l->n = 0;
    l->itens = malloc(l->cap * sizeof *l->itens);
    if (l->itens == NULL) {
        free(l);
        return NULL;
    }
    return l;
}

void lista_destruir(Lista *l) {
    if (l == NULL)
        return;
    free(l->itens);
    free(l);
}

int lista_tamanho(const Lista *l) {
    return l->n;
}

int lista_vazia(const Lista *l) {
    return l->n == 0;
}

int lista_obter(const Lista *l, int i, Voo *x) {
    if (i < 0 || i >= l->n)
        return 0;
    *x = l->itens[i];
    return 1;
}

int lista_inserir(Lista *l, int i, Voo x) {
    if (i < 0 || i > l->n)
        return 0;
    if (l->n == l->cap) {
        int novo_cap = l->cap * 2;
        Voo *novo = realloc(l->itens, novo_cap * sizeof *novo);
        if (novo == NULL)
            return 0;
        l->itens = novo;
        l->cap = novo_cap;
    }
    for (int j = l->n; j > i; j--)
        l->itens[j] = l->itens[j - 1];
    l->itens[i] = x;
    l->n++;
    return 1;
}

int lista_remover(Lista *l, int i, Voo *x) {
    if (i < 0 || i >= l->n)
        return 0;
    *x = l->itens[i];
    for (int j = i; j < l->n - 1; j++)
        l->itens[j] = l->itens[j + 1];
    l->n--;
    return 1;
}

int lista_buscar(const Lista *l, const char *codigo) {
    for (int i = 0; i < l->n; i++)
        if (strcmp(l->itens[i].codigo, codigo) == 0)
            return i;
    return -1;
}