/* pista.c - questao 2: a cabeceira da pista (pronto: nao precisa mexer).
 *
 * Quando o relogio da torre passa do horario de um voo, ele sai da frente
 * da grade e taxia para a cabeceira, onde espera numa Fila a sua vez de
 * decolar. So usa os contratos lista.h, fila.h e deque.h.
 *
 *   RELOGIO hhmm   avanca o relogio; os voos vencidos taxiam
 *   DECOLA         o primeiro da cabeceira decola
 *   PISTA          mostra a fila da cabeceira, da frente para o fim
 */

#include <stdio.h>
#include "torre.h"

#define FALTA_FILA "a fila da questao 2"

// #trecho: relogio
void pista_relogio(Torre *t, int horario) {
    Voo v;
    if (!torre_pronta(t->pista, "RELOGIO", FALTA_FILA))
        return;
    if (horario < t->relogio) {
        printf("RELOGIO %02d:%02d: o relogio nao volta\n",
               horario / 100, horario % 100);
        return;
    }
    t->relogio = horario;
    printf("RELOGIO %02d:%02d\n", horario / 100, horario % 100);
    while (lista_obter(t->grade, 0, &v) && v.horario <= horario) {
        lista_remover(t->grade, 0, &v);
        if (fila_enfileirar(t->pista, v))
            printf("  %s taxia para a cabeceira (%d na fila)\n",
                   v.codigo, fila_tamanho(t->pista));
        else
            printf("  %s: sem memoria\n", v.codigo);
    }
}
// #fim: relogio

/* pista unica: com aviao esperando para pousar, ninguem decola */
void pista_decolar(Torre *t) {
    Voo v;
    if (!torre_pronta(t->pista, "DECOLA", FALTA_FILA))
        return;
    if (t->espera != NULL && !deque_vazio(t->espera)) {
        printf("DECOLA: pista reservada para pouso (%d na espera)\n",
               deque_tamanho(t->espera));
        return;
    }
    if (fila_vazia(t->pista)) {
        printf("DECOLA: ninguem na cabeceira\n");
        return;
    }
    fila_desenfileirar(t->pista, &v);
    printf("DECOLA %02d:%02d %s para %s\n", t->relogio / 100,
           t->relogio % 100, v.codigo, v.cidade);
}

// #trecho: pista_mostrar
/* sem acesso por indice: gira a fila uma volta inteira */
void pista_mostrar(Torre *t) {
    Voo v;
    int n;
    if (!torre_pronta(t->pista, "PISTA", FALTA_FILA))
        return;
    if (!fila_frente(t->pista, &v)) {
        printf("PISTA: cabeceira livre\n");
        return;
    }
    n = fila_tamanho(t->pista);
    printf("PISTA: %d na fila, %s na frente\n", n, v.codigo);
    for (int i = 0; i < n; i++) {
        fila_desenfileirar(t->pista, &v);
        torre_imprimir_voo(&v);
        fila_enfileirar(t->pista, v);
    }
}
// #fim: pista_mostrar
