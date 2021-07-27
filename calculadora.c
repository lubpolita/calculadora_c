#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdio_ext.h>

#include "calculadora.h"

/*Operacoes auxiliares*/

void FPVazia(TPilha *pilha) //cria uma nova pilha vazia
{
    pilha->topo = (TCelula *)malloc(sizeof(TCelula));
    pilha->fundo = pilha->topo;
    pilha->topo->prox = NULL;
    pilha->tamanho = 0;
}

int Vazia(TPilha pilha) //verifica se a pilha esta vazia
{
    return (pilha.topo == pilha.fundo);
}

void Push(TPilha *pilha, TItem item) //empilha novos elementos na pilha
{
    TCelula *aux;
    aux = (TCelula *)malloc(sizeof(TCelula));
    pilha->topo->item = item;
    aux->prox = pilha->topo;
    pilha->topo = aux;
    pilha->tamanho++;
}

void Pop(TPilha *pilha, TItem *item) //retira os elementos do topo da pilha
{
    TCelula *aux;
    if (Vazia(*pilha))
    {
        return;
    }
    aux = pilha->topo;
    pilha->topo = aux->prox;
    *item = aux->prox->item;
    free(aux);
    pilha->tamanho--;
}

//libera o espaco alocado antes na memoria
void Liberar(TPilha *pilha)
{
    TItem item;

    do
    {
        Pop(pilha, &item);

    } while (!Vazia(*pilha));

    free(pilha->fundo);
}

//imprime a pilha de char
void Imprimir(TPilha pilha)
{

    TItem item;
    TPilha aux;

    FPVazia(&aux);

    while (!Vazia(pilha))
    {
        Pop(&pilha, &item);
        Push(&aux, item);
    }
    printf("\t|%d|", pilha.fundo->item.num);

    while (!Vazia(aux))
    {
        Pop(&aux, &item);
        if (pilha.fundo != pilha.topo)
        {
            printf("\t|%d|", item.num);
        }
        Push(&pilha, item);
    }
    printf("\n");
    Liberar(&aux);
}

//imprime a pilha de inteiros
void ImprimirInteiro(TPilha pilha)
{

    TItem item;
    TPilha aux;

    FPVazia(&aux);

    while (!Vazia(pilha))
    {
        Pop(&pilha, &item);
        Push(&aux, item);
    }
    printf("\t|%d|", pilha.fundo->item.inteiro);

    while (!Vazia(aux))
    {

        Pop(&aux, &item);
        if (pilha.fundo != pilha.topo)
        {
            printf("\t|%d|", item.inteiro);
        }
        Push(&pilha, item);
    }
    printf("\n");
    Liberar(&aux);
}

//transforma de infixo para posfixo com espacos para que seja possivel calcular a expressao posteriormente
char *infParaPos(TPilha *pilha, char *inf)
{   
    //inicializando variaveis
    int n = strlen(inf);
    char *pos;
    pos = malloc((n + 1) * sizeof(char));
    FPVazia(pilha);
    TItem item;
    item.num = inf[0];
    Push(pilha, item);
    TItem aux;
    int i;
    int j = 0;
    int cont = 0; 

    //laco que passa pelo vetor infixo
    for (i = 1; inf[i] != '\0'; ++i)
    {
        switch (inf[i])
        {
        case '(':
            aux.num = inf[i];
            Push(pilha, aux);
            break;
        case ')':
            
            pos[j++] = ' ';
            Pop(pilha, &aux);
            while (aux.num != '(')
            {
                pos[j++] = aux.num;
                Pop(pilha, &aux);
            }
            break;
        case '+':
        case '-':
            pos[j++] = ' ';
            Pop(pilha, &aux);
            while (aux.num != '(')
            {
                pos[j++] = aux.num;
                Pop(pilha, &aux);
            }
            Push(pilha, aux);
            aux.num = inf[i];
            Push(pilha, aux);
            break;
        case '*':
        case '/':
            pos[j++] = ' ';
            Pop(pilha, &aux);
            while (aux.num != '(' && aux.num != '+' && aux.num != '-')
            {
                pos[j++] = aux.num;
                Pop(pilha, &aux);
            }
            Push(pilha, aux);
            aux.num = inf[i];
            Push(pilha, aux);
            break;
        default:
            pos[j++] = inf[i];
            break;
        }
    }
    pos[j] = '\0';
    return pos; //retorna a expressao no posfixo
}

//realiza a operacao escolhida
void operacao(TPilha *pilha, char *opcao)
{

    //inicializacao de variaveis auxiliares:
    char soma[] = "+";
    char subt[] = "-";
    char mult[] = "*";
    char div[] = "/";
    char clear[] = "c";
    char clearUp[] = "C";
    char enter[] = "e";
    char enterUp[] = "E";
    long int numero = -1;

    //declaracoes para as operacoes
    TItem aux;
    TItem retirado;
    TItem retirado2;
    TItem item;

    numero = strtol(opcao, NULL, 10); //transformacao de char para inteiro
    //condicoes
    if (strcmp(opcao, soma) == 0) //soma
    {
        printf("\nCaractere: %s ", soma);
        Pop(pilha, &retirado);
        Pop(pilha, &retirado2);
        aux.inteiro = retirado2.inteiro + retirado.inteiro;
        Push(pilha, aux);
    }
    else if (strcmp(opcao, subt) == 0) //subtracao
    {
        printf("\nCaractere: %s ", subt);
        Pop(pilha, &retirado);
        Pop(pilha, &retirado2);
        aux.inteiro = retirado2.inteiro - retirado.inteiro;
        Push(pilha, aux);
    }
    else if (strcmp(opcao, mult) == 0) //multiplicacao
    {
        printf("\nCaractere: %s ", mult);
        Pop(pilha, &retirado);
        Pop(pilha, &retirado2);
        aux.inteiro = (retirado2.inteiro * retirado.inteiro);
        Push(pilha, aux);
    }
    else if (strcmp(opcao, div) == 0) //divisao
    {
        printf("\nCaractere: %s ", div);
        Pop(pilha, &retirado);
        Pop(pilha, &retirado2);
        if(retirado.inteiro == 0){
            printf("\n\nERRO: nao eh possivel dividir por 0. \n");
            exit(0);
        }
        else{
        aux.inteiro = (retirado2.inteiro / retirado.inteiro);
        Push(pilha, aux);
        }
    }
    else if (strcmp(opcao, clear) == 0 || strcmp(opcao, clearUp) == 0) //clear
    {
        printf("\nCaractere: %s ", clear);
        Liberar(pilha);
        FPVazia(pilha);
        printf("\nSua pilha foi reiniciada com sucesso!\n");
    }
    else if (strcmp(opcao, enter) == 0 || strcmp(opcao, enterUp) == 0) //enter
    {
        printf("\nCaractere: %s ", enter);
        item.inteiro = 0;
        Push(pilha, item);
        printf("\nPilha: \n");
        ImprimirInteiro(*pilha);
    }
    else if (numero >= 0 && numero <= 9) //adiciona numeros na pilha
    {
        printf("\nCaractere: %ld ", numero);
        Pop(pilha, &retirado);
        aux.inteiro = (retirado.inteiro * 10) + numero;
        Push(pilha, aux);
    }
}

//funcao de funcionamento da calculadora
void calculadora(TPilha *pilha, char *vetor)
{
    //declaracoes para as operacoes
    int i;
    char enter[] = "e";
    char *aux;
    printf("\n\n---------------------R-E-S-U-L-T-A-D-O-----------------------\n");

    //inicializando a pilha com um enter inicial
    operacao(pilha, enter);
    //printf("\nPilha: \n");
    //imprimindo pilha 
    //ImprimirInteiro(*pilha);


    //laco que passa pelo vetor posfixo
    for (i = 0; vetor[i] != '\0'; i++)
    {

        if (vetor[i] == ' ') //caso seja um espaco em branco ele analisa o proximo caracter para saber se eh 
                                //um novo numero ou se eh uma operacao
        {
            switch (vetor[i + 1])
            {
            case '-':
            case '+':
            case '*':
            case '/':
                break;

            default:
                operacao(pilha, enter); //se o proximo for um numero ele da um enter para separa-los
                break;
            }
        }
        else
        {   
            switch (vetor[i])  //caso nao seja um espaco em branco, eh analisado qual simbolo ele eh 
            {                   //para que ele seja mandado para fazer as operacoes necessarias.
            case '0':
                aux = "0";
                operacao(pilha, aux);
                break;
            case '1':
                aux = "1";
                operacao(pilha, aux);
                break;
            case '2':
                aux = "2";
                operacao(pilha, aux);
                break;
            case '3':
                aux = "3";
                operacao(pilha, aux);
                break;
            case '4':
                aux = "4";
                operacao(pilha, aux);
                break;
            case '5':
                aux = "5";
                operacao(pilha, aux);
                break;
            case '6':
                aux = "6";
                operacao(pilha, aux);
                break;
            case '7':
                aux = "7";
                operacao(pilha, aux);
                break;
            case '8':
                aux = "8";
                operacao(pilha, aux);
                break;
            case '9':
                aux = "9";
                operacao(pilha, aux);
                break;
            case '-':
                aux = "-";
                operacao(pilha, aux);
                break;
            case '+':
                aux = "+";
                operacao(pilha, aux);
                break;
            case '*':
                aux = "*";
                operacao(pilha, aux);
                break;
            case '/':
                aux = "/";
                operacao(pilha, aux);
                break;
            default:
                break;
            }
            //imprimindo os passos das operacoes da pilha 
            printf("\nPilha: \n");
            ImprimirInteiro(*pilha);
        }
    }
}