/* torre.c - cria e destroi a torre (pronto: nao precisa mexer). */

#include <stdio.h>
#include <stdlib.h>
#include "torre.h"

Torre *torre_criar(void) {
    Torre *t = malloc(sizeof *t);
    if (t == NULL)
        return NULL;
    t->relogio = 0;
    t->grade = lista_criar();
    t->pista = fila_criar();
    t->hangar = pilha_criar();
    t->espera = deque_criar();
    return t;
}

void torre_destruir(Torre *t) {
    if (t == NULL)
        return;
    lista_destruir(t->grade);
    fila_destruir(t->pista);
    pilha_destruir(t->hangar);
    deque_destruir(t->espera);
    free(t);
}

void torre_imprimir_voo(const Voo *v) {
    printf("  %02d:%02d  %-6s  %s\n", v->horario / 100, v->horario % 100,
           v->codigo, v->cidade);
}

int torre_pronta(const void *estrutura, const char *cmd, const char *o_que) {
    if (estrutura != NULL)
        return 1;
    printf("%s: falta %s\n", cmd, o_que);
    return 0;
}
