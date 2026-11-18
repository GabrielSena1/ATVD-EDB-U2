/* main.c - le os comandos da torre e os despacha (pronto: nao precisa
 * mexer). Cada comando mora no arquivo da questao em que aparece.
 *
 *   make q1             compila e confere a questao 1 (veja o Makefile)
 *   make run entradas/q4.txt
 *
 * Comandos (um por linha; linhas que comecam com # sao ignoradas):
 *   questao 1  PROGRAMA cod hhmm cidade; CANCELA cod; ATRASA cod hhmm
 *              GRADE
 *   questao 2  RELOGIO hhmm; DECOLA; PISTA
 *   questao 3  PANE cod; LIBERA cod hhmm; HANGAR
 *   questao 4  CHEGA cod cidade; MAYDAY cod cidade; POUSA; DESVIA
 *              ESPERA
 */

#include <stdio.h>
#include <string.h>
#include "torre.h"

/* "cod hhmm cidade" ou "cod cidade" depois do comando; 0 se mal formada */
int ler_voo(const char *resto, int com_horario, Voo *v) {
    int pos = 0, lidos;
    v->horario = 0;
    if (com_horario)
        lidos = sscanf(resto, "%7s %d %n", v->codigo, &v->horario, &pos);
    else
        lidos = sscanf(resto, "%7s %n", v->codigo, &pos);
    if (lidos < 1 + com_horario || pos == 0)
        return 0;
    strncpy(v->cidade, resto + pos, sizeof v->cidade - 1);
    v->cidade[sizeof v->cidade - 1] = '\0';
    v->cidade[strcspn(v->cidade, "\r\n")] = '\0';
    return v->cidade[0] != '\0';
}

void executar(Torre *t, const char *cmd, const char *resto) {
    char cod[8];
    int hora;
    Voo v;
    if (strcmp(cmd, "PROGRAMA") == 0 && ler_voo(resto, 1, &v))
        grade_programar(t, v);
    else if (strcmp(cmd, "CANCELA") == 0 && sscanf(resto, "%7s", cod) == 1)
        grade_cancelar(t, cod);
    else if (strcmp(cmd, "ATRASA") == 0 &&
             sscanf(resto, "%7s %d", cod, &hora) == 2)
        grade_atrasar(t, cod, hora);
    else if (strcmp(cmd, "GRADE") == 0)
        grade_mostrar(t);
    else if (strcmp(cmd, "RELOGIO") == 0 && sscanf(resto, "%d", &hora) == 1)
        pista_relogio(t, hora);
    else if (strcmp(cmd, "DECOLA") == 0)
        pista_decolar(t);
    else if (strcmp(cmd, "PISTA") == 0)
        pista_mostrar(t);
    else if (strcmp(cmd, "PANE") == 0 && sscanf(resto, "%7s", cod) == 1)
        hangar_pane(t, cod);
    else if (strcmp(cmd, "LIBERA") == 0 &&
             sscanf(resto, "%7s %d", cod, &hora) == 2)
        hangar_liberar(t, cod, hora);
    else if (strcmp(cmd, "HANGAR") == 0)
        hangar_mostrar(t);
    else if (strcmp(cmd, "CHEGA") == 0 && ler_voo(resto, 0, &v))
        espera_chegar(t, v);
    else if (strcmp(cmd, "MAYDAY") == 0 && ler_voo(resto, 0, &v))
        espera_mayday(t, v);
    else if (strcmp(cmd, "POUSA") == 0)
        espera_pousar(t);
    else if (strcmp(cmd, "DESVIA") == 0)
        espera_desviar(t);
    else if (strcmp(cmd, "ESPERA") == 0)
        espera_mostrar(t);
    else
        printf("%s: comando desconhecido ou mal formado\n", cmd);
}

int main(int argc, char *argv[]) {
    const char *caminho = argc > 1 ? argv[1] : "entradas/q1.txt";
    char linha[200], cmd[16];
    int pos;
    FILE *f = fopen(caminho, "r");
    if (f == NULL) {
        printf("nao consegui abrir %s\n", caminho);
        return 1;
    }
    Torre *t = torre_criar();
    if (t == NULL || t->grade == NULL) {
        printf("lista_criar devolveu NULL: a lista ja foi implementada?\n");
        torre_destruir(t);
        fclose(f);
        return 1;
    }
    while (fgets(linha, sizeof linha, f) != NULL) {
        pos = 0;
        if (linha[0] == '#' || sscanf(linha, "%15s %n", cmd, &pos) != 1)
            continue;
        executar(t, cmd, linha + pos);
    }
    fclose(f);
    torre_destruir(t);
    return 0;
}
