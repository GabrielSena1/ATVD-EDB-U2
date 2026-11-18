# A torre de controle: lista, fila, pilha e deque (unidade 2).
#
#   make build                 compila ./torre com as representacoes abaixo
#   make q1                    questao 1: compila, roda entradas/q1.txt e
#                              compara com esperadas/q1.txt
#   make q2, make q3, make q4  o mesmo para as questoes 2, 3 e 4
#   make todas                 as quatro questoes em todas as representacoes
#   make run arquivo.txt       roda ./torre com os comandos de arquivo.txt
#   make clean                 apaga o executavel
#
# A representacao de cada TAD se escolhe na linha de comando:
#   make q1 LISTA=dupla
#   make q2 FILA=encadeada
#   make q4 LISTA=simples FILA=encadeada PILHA=encadeada DEQUE=dupla
#
# SAN=1 compila com o sanitizer, que acusa acesso invalido e no liberado
# duas vezes:  make q2 FILA=encadeada SAN=1

LISTA ?= vetor
FILA  ?= circular
PILHA ?= vetor
DEQUE ?= circular

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -pedantic
ifdef SAN
  CFLAGS += -g -fsanitize=address,undefined
endif
CLIENTE = main.c torre.c grade.c pista.c hangar.c aproximacao.c
TADS    = lista_$(LISTA).c fila_$(FILA).c pilha_$(PILHA).c deque_$(DEQUE).c
ENTRADA = entradas/q1.txt

# make run arquivo.txt: o segundo objetivo vira a entrada, nao um alvo
ifeq (run,$(firstword $(MAKECMDGOALS)))
  ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  ifneq ($(ARGS),)
    ENTRADA := $(firstword $(ARGS))
    $(eval $(ARGS):;@:)
  endif
endif

# conferir(N, descricao): roda entradas/qN.txt e compara com esperadas/qN.txt
define conferir
	@if ./torre entradas/q$(1).txt | diff esperadas/q$(1).txt -; then \
	    echo "OK q$(1) ($(2))"; \
	else \
	    echo "FALHOU q$(1) ($(2)): acima, < esperado e > obtido"; \
	    exit 1; \
	fi
endef

build:
	$(CC) $(CFLAGS) $(CLIENTE) $(TADS) -o torre

q1: build
	$(call conferir,1,lista $(LISTA))

q2: build
	$(call conferir,2,lista $(LISTA) + fila $(FILA))

q3: build
	$(call conferir,3,lista $(LISTA) + pilha $(PILHA))

q4: build
	$(call conferir,4,lista $(LISTA) + fila $(FILA) + pilha $(PILHA) + deque $(DEQUE))

todas:
	@falhou=0; \
	for x in vetor simples dupla; do \
	    $(MAKE) -s --no-print-directory q1 LISTA=$$x || falhou=1; done; \
	for x in circular encadeada; do \
	    $(MAKE) -s --no-print-directory q2 FILA=$$x || falhou=1; done; \
	for x in vetor encadeada; do \
	    $(MAKE) -s --no-print-directory q3 PILHA=$$x || falhou=1; done; \
	for x in circular dupla; do \
	    $(MAKE) -s --no-print-directory q4 DEQUE=$$x || falhou=1; done; \
	exit $$falhou

run:
	@test -x torre || $(MAKE) --no-print-directory build
	./torre $(ENTRADA)

clean:
	rm -rf torre torre.dSYM

.PHONY: build q1 q2 q3 q4 todas run clean
