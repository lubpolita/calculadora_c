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
    char expressao[50];
    int opcao = -1;

    while (opcao != 2)
    {

        printf("\nDigite uma expressao na forma infixa: ");
#ifdef OS_Windows
        fflush(stdin);
#else
        __fpurge(stdin); //limpa o buffer
#endif
        scanf("%s", expressao);

        //posfixa
        final = infParaPos(&pilha, expressao);
        printf("\nForma polonesa: %s\n", final);

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

        if (opcao == 1)
        {
            char *clear = "c";
            operacao(&pilha, clear);
        }
        else if (opcao != 2)
        {
            printf("\nAtencao! Digite uma opcao valida!.\n");
        }
        else
        {
            printf("\nSaindo...\n");
        }
    }
    Liberar(&pilha);    //liberando pilha da memoria

    return 0;
}
