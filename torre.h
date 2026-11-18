/* torre.h - a torre de controle do aeroporto de Sao Goncalo do Amarante.
 *
 * ESTE ARQUIVO ESTA PRONTO: nao precisa mexer nele. A torre junta as
 * quatro estruturas da unidade 2, cada uma atras do seu contrato:
 *
 *   grade    Lista   partidas do dia, em ordem de horario    (questao 1)
 *   pista    Fila    avioes na cabeceira, prontos para sair  (questao 2)
 *   hangar   Pilha   corredor de manutencao sem saida        (questao 3)
 *   espera   Deque   avioes na aproximacao, esperando pouso  (questao 4)
 *
 * Os comandos de cada questao moram em grade.c, pista.c, hangar.c e
 * aproximacao.c. Enquanto uma estrutura nao estiver implementada (o seu
 * _criar devolve NULL), os comandos dela avisam e o resto segue.
 */

#ifndef TORRE_H
#define TORRE_H

#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "deque.h"

// #trecho: torre
typedef struct {
    int relogio;    /* hhmm; comeca em 0000 */
    Lista *grade;   /* questao 1 */
    Fila *pista;    /* questao 2 */
    Pilha *hangar;  /* questao 3 */
    Deque *espera;  /* questao 4 */
} Torre;
// #fim: torre

/* NULL so se faltar memoria para a propria torre */
Torre *torre_criar(void);
void torre_destruir(Torre *t);

/* "  08:10  AD4521  Recife" */
void torre_imprimir_voo(const Voo *v);
/* 1 se a estrutura existe; senao avisa "cmd: falta o_que" e devolve 0 */
int torre_pronta(const void *estrutura, const char *cmd, const char *o_que);

/* grade.c - questao 1 */
void grade_programar(Torre *t, Voo v);
void grade_cancelar(Torre *t, const char *codigo);
void grade_atrasar(Torre *t, const char *codigo, int horario);
void grade_mostrar(const Torre *t);
int grade_inserir(Torre *t, Voo v);

/* pista.c - questao 2 */
void pista_relogio(Torre *t, int horario);
void pista_decolar(Torre *t);
void pista_mostrar(Torre *t);

/* hangar.c - questao 3 */
void hangar_pane(Torre *t, const char *codigo);
void hangar_liberar(Torre *t, const char *codigo, int horario);
void hangar_mostrar(Torre *t);

/* aproximacao.c - questao 4 */
void espera_chegar(Torre *t, Voo v);
void espera_mayday(Torre *t, Voo v);
void espera_pousar(Torre *t);
void espera_desviar(Torre *t);
void espera_mostrar(Torre *t);

#endif /* TORRE_H */
