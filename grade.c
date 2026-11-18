/* grade.c - questao 1: a grade de partidas (pronto: nao precisa mexer).
 *
 * A grade guarda os voos numa Lista em ordem de horario; em empate, quem
 * foi programado antes fica na frente. So usa o contrato lista.h.
 *
 *   PROGRAMA cod hhmm cidade   programa uma partida
 *   CANCELA cod                tira a partida da grade
 *   ATRASA cod hhmm            muda o horario e reposiciona
 *   GRADE                      mostra a grade inteira
 */

#include <stdio.h>
#include "torre.h"

// #trecho: grade_inserir
/* entra antes do primeiro que sai depois dele */
int grade_inserir(Torre *t, Voo v) {
    Voo atual;
    int i = 0;
    while (lista_obter(t->grade, i, &atual)
           && atual.horario <= v.horario)
        i++;
    return lista_inserir(t->grade, i, v);
}
// #fim: grade_inserir

void grade_programar(Torre *t, Voo v) {
    if (lista_buscar(t->grade, v.codigo) >= 0)
        printf("PROGRAMA %s: codigo repetido, ignorado\n", v.codigo);
    else if (grade_inserir(t, v))
        printf("PROGRAMA %s %02d:%02d %s\n", v.codigo, v.horario / 100,
               v.horario % 100, v.cidade);
    else
        printf("PROGRAMA %s: sem memoria\n", v.codigo);
}

void grade_cancelar(Torre *t, const char *codigo) {
    Voo v;
    int i = lista_buscar(t->grade, codigo);
    if (i < 0) {
        printf("CANCELA %s: nao esta na grade\n", codigo);
        return;
    }
    lista_remover(t->grade, i, &v);
    printf("CANCELA %s %02d:%02d %s\n", v.codigo, v.horario / 100,
           v.horario % 100, v.cidade);
}

// #trecho: grade_atrasar
void grade_atrasar(Torre *t, const char *codigo, int horario) {
    Voo v;
    int antes, i = lista_buscar(t->grade, codigo);
    if (i < 0) {
        printf("ATRASA %s: nao esta na grade\n", codigo);
        return;
    }
    lista_remover(t->grade, i, &v);   /* sai de i */
    antes = v.horario;
    v.horario = horario;
    grade_inserir(t, v);              /* lugar novo */
    printf("ATRASA %s %02d:%02d -> %02d:%02d: posicao %d -> %d\n",
           codigo, antes / 100, antes % 100, horario / 100,
           horario % 100, i, lista_buscar(t->grade, codigo));
}
// #fim: grade_atrasar

void grade_mostrar(const Torre *t) {
    Voo v;
    if (lista_vazia(t->grade)) {
        printf("GRADE: vazia\n");
        return;
    }
    printf("GRADE: %d voo(s)\n", lista_tamanho(t->grade));
    for (int i = 0; lista_obter(t->grade, i, &v); i++)
        torre_imprimir_voo(&v);
}
