#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdio_ext.h>
#include "calculadora.h"

/*para que seja possivel diferenciar os SO*/
#ifdef __unix__
#include <unistd.h>
#include <stdlib.h>

#elif defined(_WIN32) || defined(WIN32)
#define OS_Windows
#include <windows.h>

#endif

//main
int main()
{
    TPilha pilha;
    FPVazia(&pilha);
    //char expressao[50] = "(90/((20*(15-13))+5))";
    char *final;
    char expressao[100];
    int opcao = -1;

    //laco para repetir a calculadora 
    while (opcao != 2)
    {
        //entrada de dados
        printf("\nDigite uma expressao na forma infixa: ");
        #ifdef OS_Windows
            fflush(stdin);
        #else
            __fpurge(stdin); //limpa o buffer
        #endif
        scanf("%s", expressao);

        //chamada para posfixa
        final = infParaPos(&pilha, expressao);
        printf("\nForma polonesa: %s\n", final); //saida de dados 

        //calculadora
        printf("\nCalculando a expressao utilizando pilha: \n"); 
        calculadora(&pilha, final);

        printf("\nDeseja fazer outra operacao?\n");
        printf("1 - Sim \n");
        printf("2 - Nao\n ");
        #ifdef OS_Windows
            fflush(stdin);
        #else
            __fpurge(stdin); //limpa o buffer
        #endif
        scanf("%d", &opcao);

        if (opcao == 1) //reinicia a calculadora, ou seja, reseta ela com o clear
        {   
            #ifdef OS_Windows
                system("cls");
            #else
                system("clear");
            #endif
            char *clear = "c";
            operacao(&pilha, clear);
        }
        else if (opcao != 2)
        {
            printf("\nAtencao! Digite uma opcao valida!.\n"); //caso o usuario digite algo diferente de 1 e 2
        }
        else
        {
            printf("\nSaindo...\n"); //sair
        }
    }
    Liberar(&pilha);    //excluindo pilha da memoria

    return 0;
}
