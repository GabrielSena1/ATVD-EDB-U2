/* hangar.c - questao 3: o hangar de manutencao (pronto: nao precisa mexer).
 *
 * O hangar e um corredor estreito com uma porta so: o ultimo aviao a
 * entrar fica na porta e e o primeiro que consegue sair. Para tirar um
 * aviao do fundo, os que estao na frente dele saem para o patio, numa
 * segunda pilha, e voltam depois na mesma ordem. So usa os contratos
 * lista.h e pilha.h.
 *
 *   PANE cod          o voo sai da grade e e rebocado para o hangar
 *   LIBERA cod hhmm   o aviao sai do hangar e volta para a grade
 *   HANGAR            mostra o hangar, da porta para o fundo
 */

#include <stdio.h>
#include <string.h>
#include "torre.h"

#define FALTA_PILHA "a pilha da questao 3"

void hangar_pane(Torre *t, const char *codigo) {
    Voo v;
    int i;
    if (!torre_pronta(t->hangar, "PANE", FALTA_PILHA))
        return;
    i = lista_buscar(t->grade, codigo);
    if (i < 0) {
        printf("PANE %s: nao esta na grade\n", codigo);
        return;
    }
    lista_remover(t->grade, i, &v);
    if (pilha_empilhar(t->hangar, v))
        printf("PANE %s: rebocado para o hangar (%d no hangar)\n",
               codigo, pilha_tamanho(t->hangar));
    else
        printf("PANE %s: sem memoria\n", codigo);
}

// #trecho: liberar
void hangar_liberar(Torre *t, const char *codigo, int horario) {
    Voo v, w;
    int achou = 0, manobras = 0;
    Pilha *patio;
    if (!torre_pronta(t->hangar, "LIBERA", FALTA_PILHA))
        return;
    patio = pilha_criar();
    if (patio == NULL) {
        printf("LIBERA %s: sem memoria para o patio\n", codigo);
        return;
    }
    while (pilha_desempilhar(t->hangar, &v)) {
        if (strcmp(v.codigo, codigo) == 0) {
            achou = 1;
            break;
        }
        pilha_empilhar(patio, v);   /* sai para o patio */
        manobras++;
    }
    while (pilha_desempilhar(patio, &w))
        pilha_empilhar(t->hangar, w);  /* volta na ordem */
    pilha_destruir(patio);
// #fim: liberar
    if (!achou) {
        printf("LIBERA %s: nao esta no hangar (%d manobra(s))\n",
               codigo, manobras);
        return;
    }
    v.horario = horario;
    if (!grade_inserir(t, v)) {
        printf("LIBERA %s: sem memoria\n", codigo);
        return;
    }
    printf("LIBERA %s: %d manobra(s), volta a grade %02d:%02d\n",
           codigo, manobras, horario / 100, horario % 100);
}

void hangar_mostrar(Torre *t) {
    Voo v;
    Pilha *patio;
    if (!torre_pronta(t->hangar, "HANGAR", FALTA_PILHA))
        return;
    if (pilha_vazia(t->hangar)) {
        printf("HANGAR: vazio\n");
        return;
    }
    patio = pilha_criar();
    if (patio == NULL) {
        printf("HANGAR: sem memoria para o patio\n");
        return;
    }
    pilha_topo(t->hangar, &v);
    printf("HANGAR: %d aviao(oes), %s na porta\n",
           pilha_tamanho(t->hangar), v.codigo);
    while (pilha_desempilhar(t->hangar, &v)) {
        torre_imprimir_voo(&v);
        pilha_empilhar(patio, v);
    }
    while (pilha_desempilhar(patio, &v))
        pilha_empilhar(t->hangar, v);
    pilha_destruir(patio);
}
