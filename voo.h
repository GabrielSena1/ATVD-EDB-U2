/* voo.h - o item que passa pelas quatro estruturas da torre.
 *
 * NAO MODIFIQUE ESTE ARQUIVO. A grade (lista), a cabeceira da pista
 * (fila), o hangar (pilha) e a espera para pouso (deque) guardam Voo.
 */

#ifndef VOO_H
#define VOO_H

// #trecho: voo
typedef struct {
    char codigo[8];   /* "AD4521": companhia e numero */
    int horario;      /* hhmm: 1430 e 14h30 */
    char cidade[24];  /* destino ou origem */
} Voo;
// #fim: voo

#endif /* VOO_H */
