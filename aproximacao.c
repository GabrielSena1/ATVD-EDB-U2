/* aproximacao.c - questao 4: a espera para pouso (pronto: nao precisa mexer).
 *
 * Os avioes que chegam esperam a vez de pousar num Deque: quem chega
 * entra no fim, uma emergencia entra no inicio, o primeiro pousa e, se a
 * espera ficar longa, o ultimo desiste e segue para o aeroporto
 * alternativo. So usa o contrato deque.h.
 *
 *   CHEGA cod cidade    entra no fim da espera
 *   MAYDAY cod cidade   emergencia: entra no inicio da espera
 *   POUSA               o primeiro da espera pousa
 *   DESVIA              o ultimo da espera segue para o alternativo
 *   ESPERA              mostra a espera, do primeiro ao ultimo
 */

#include <stdio.h>
#include "torre.h"

#define FALTA_DEQUE "o deque da questao 4"

void espera_chegar(Torre *t, Voo v) {
    if (!torre_pronta(t->espera, "CHEGA", FALTA_DEQUE))
        return;
    v.horario = t->relogio;
    if (deque_inserir_fim(t->espera, v))
        printf("CHEGA %s de %s: entra na espera (%d na espera)\n",
               v.codigo, v.cidade, deque_tamanho(t->espera));
    else
        printf("CHEGA %s: sem memoria\n", v.codigo);
}

void espera_mayday(Torre *t, Voo v) {
    if (!torre_pronta(t->espera, "MAYDAY", FALTA_DEQUE))
        return;
    v.horario = t->relogio;
    if (deque_inserir_inicio(t->espera, v))
        printf("MAYDAY %s de %s: primeiro da espera (%d na espera)\n",
               v.codigo, v.cidade, deque_tamanho(t->espera));
    else
        printf("MAYDAY %s: sem memoria\n", v.codigo);
}

void espera_pousar(Torre *t) {
    Voo v;
    if (!torre_pronta(t->espera, "POUSA", FALTA_DEQUE))
        return;
    if (!deque_remover_inicio(t->espera, &v)) {
        printf("POUSA: ninguem na espera\n");
        return;
    }
    printf("POUSA %02d:%02d %s de %s\n", t->relogio / 100,
           t->relogio % 100, v.codigo, v.cidade);
}

void espera_desviar(Torre *t) {
    Voo v;
    if (!torre_pronta(t->espera, "DESVIA", FALTA_DEQUE))
        return;
    if (!deque_remover_fim(t->espera, &v)) {
        printf("DESVIA: ninguem na espera\n");
        return;
    }
    printf("DESVIA %s de %s: segue para o alternativo\n", v.codigo,
           v.cidade);
}

// #trecho: espera_mostrar
/* sem acesso por indice: gira o deque uma volta inteira */
void espera_mostrar(Torre *t) {
    Voo v, u;
    int n;
    if (!torre_pronta(t->espera, "ESPERA", FALTA_DEQUE))
        return;
    if (!deque_primeiro(t->espera, &v)) {
        printf("ESPERA: ninguem esperando\n");
        return;
    }
    deque_ultimo(t->espera, &u);
    n = deque_tamanho(t->espera);
    printf("ESPERA: %d aviao(oes), %s primeiro, %s ultimo\n",
           n, v.codigo, u.codigo);
    for (int i = 0; i < n; i++) {
        deque_remover_inicio(t->espera, &v);
        torre_imprimir_voo(&v);
        deque_inserir_fim(t->espera, v);
    }
}
// #fim: espera_mostrar
