#include "AHTSH.h"
#include <stdlib.h>
#include <stdio.h>

void main(){
    int totalc = 0, nsalvo = 0, info;

    TAHTSH* agenda = a_create();

    int menu;
    do{
        puts("Menu:\n1- Cadastro de novo contato\n2- Imprimir agenda em tela\n3- Deletar um contato\n4- Salvar em arquivo\n5- Sair\nEscolha uma opcao:");
        scanf("%d", &menu);

        switch (menu){
            case 1:
                a_register(agenda, info, &totalc, &nsalvo);
                break;
            case 2:
                a_print(agenda);
                break;
            case 3:
                a_delete_end(agenda);
                break;
            case 4:
                a_save(agenda);
                printf("Agenda salva\n");
                break;
            case 5:
                if (nsalvo) {
                    a_save(agenda);
                    printf("Agenda salva antes de sair\n");
                }
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente\n");
        }
    }while (menu != 5);

    return 0;
}