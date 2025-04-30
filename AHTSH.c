#include "AHTSH.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _no{
    TContato info;
    struct _no *prox;
}TNo;
TNo* TNo_createNFill(TContato*);

struct _list{
    TNo* inicio;
};

TNo* TNo_createNFill(TContato* info){
    TNo* novo = malloc(sizeof(TNo));
    if(novo){
        novo->info = *info;
        novo->prox = NULL;
    }
    return novo;
}

TAHTSH* a_create(){
    TAHTSH* nova = malloc(sizeof(TAHTSH));
    if(nova){
        nova->inicio = NULL;
    }
    return nova;
}

//aux->info.telefone;

void a_open(TAHTSH* agenda, int* totalc){
    FILE *file = fopen("agenda.csv", "r");
    if (file){
        while (fscanf(file, "%127[^,],%15s\n", agenda->inicio->info.nome, agenda->inicio->info.telefone) == 2){
        *totalc++;
        }
    }
    fclose(file);
}

bool a_register(TAHTSH* agenda, TContato* info, int* totalc, int* nsalvo){
    printf("Digite o nome: ");
        scanf(" %[^\n]", agenda->inicio->info.nome);
        printf("Digite o telefone: ");
        scanf(" %[^\n]", agenda->inicio->info.telefone);
    TNo* novo = TNo_createNFill(info);
    if(novo == NULL) return false;
    //A lista está vazia?
    if(agenda->inicio == NULL)
        agenda->inicio = novo;
    else{
        //Lista nao vazia, temos que encontrar o último elemento
        TNo* aux = agenda->inicio;
        while(aux->prox!=NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
    totalc++;
    nsalvo = 1;
    return true;
}

void a_print(TAHTSH* agenda, int* totalc){
    if (totalc == 0){
        printf("Agenda vazia!\n");
        return;
    }
    TNo* aux = agenda->inicio;
    while(aux!=NULL){
        printf("[%d]->", aux->info.nome);
        printf("[%d]->", aux->info.telefone);
        aux = aux->prox;
    }
    putchar('\n');
}

bool a_delete_end(TAHTSH* agenda){
    if(agenda->inicio == NULL)
        return false;
    TNo* aux = agenda->inicio;
    if(aux->prox == NULL){
            free(aux);
            agenda->inicio = NULL;
            return true;
        }
    //para chegar até o penultimo elemento:
    while(aux->prox->prox!=NULL){
        aux = aux->prox;
    }
    free(aux->prox);
    aux->prox = NULL;
    return true;
}

void a_save(TAHTSH* agenda, int* nsalvo, int* totalc){
    FILE *file = fopen("agenda.csv", "w");
    if (file){
        TNo* aux = agenda->inicio;
        while(aux!=NULL){
            fprintf(file, "%s,%s\n", aux->info.nome, aux->info.telefone);
            aux = aux->prox;
        }
        fclose(file);
        *nsalvo = 0;
    }
}