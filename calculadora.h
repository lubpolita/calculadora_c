#ifndef CALCULADORA_H
#define CALCULADORA_H
#include <stdio.h>
#include <stdlib.h>

/*Estrutura da pilha*/

typedef struct
{
    char num;
    int inteiro;
} TItem;

typedef struct celula
{
    TItem item;
    struct celula *prox;
} TCelula;

typedef struct
{
    TCelula *fundo;
    TCelula *topo;
    int tamanho;
} TPilha;

//operacoes auxiliares
void FPVazia(TPilha *pilha);
int Vazia(TPilha pilha);
void Push(TPilha *pilha, TItem item);
void Pop(TPilha *pilha, TItem *item);
void Liberar(TPilha *pilha);
void Imprimir(TPilha pilha);
void ImprimirInteiro(TPilha pilha);
char *infParaPos(TPilha *pilha, char *inf);
void operacao(TPilha *pilha, char *opcao);
void calculadora(TPilha *pilha, char *vetor);

#endif