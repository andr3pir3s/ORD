#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

int main()
{
    int opcao, valor;
    Node *raiz = NULL;

    do{
        printf("\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opcao);

        switch(opcao){
        case 0:
            printf("Saindo!!!");
            break;
        case 1:
            printf("\tDigite o valor a ser inserido: ");
            scanf("%d", &valor);
            raiz = insert(raiz, valor);
            break;
        case 2:
            printf("\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remove_(raiz, valor);
            break;
        case 3:
            print(raiz, 1);
            break;
        default:
            printf("\nOcao invalida!!!\n");
        }

    }while(opcao != 0);

    return 0;
}