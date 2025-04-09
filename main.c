#include <stdio.h>
#include <stdlib.h>

struct Contato{
    char nome[128], telefone[15];
};

typedef struct Contato TContato;

TContato *dados;
int totalc = 0, nsalvo = 0;

void abriragnd(){
    FILE *file = fopen("agenda.csv", "r");
    if (file){
        dados = (TContato *)malloc(50 * sizeof(TContato));
        if (dados == NULL){
            printf("Erro ao alocar memoria!\n");
            return;
        }else{
            while (fscanf(file, "%127[^,],%15s\n", dados[totalc].nome, dados[totalc].telefone) == 2){
            totalc++;
            }
        }
        fclose(file);
    }
}

void cadast(){
    if (totalc >= 50){
        printf("Agenda cheia!\n");
        return;
    }
    printf("Digite o nome: ");
    scanf(" %[^\n]", dados[totalc].nome);
    printf("Digite o telefone: ");
    scanf(" %[^\n]", dados[totalc].telefone);
    totalc++;
    nsalvo = 1;
}

void imprim(){
    if (totalc == 0){
        printf("Agenda vazia!\n");
        return;
    }
    for (int i = 0; i < totalc; i++){
        printf("%d: %s, %s\n", i + 1, dados[i].nome, dados[i].telefone);
    }
}

void delet(){
    int indice;
    printf("Digite o numero do contato a ser deletado: ");
    scanf("%d", &indice);
    if (indice < 1 || indice > totalc){
        printf("Contato invalido!\n");
        return;
    }
    int i = indice - 1;
    while (i < totalc - 1){
        dados[i] = dados[i + 1];
        i++;
    }
    totalc--;
    nsalvo = 1;
}

void salvaragnd(){
    FILE *file = fopen("agenda.csv", "w");
    if (file){
        for (int i = 0; i < totalc; i++){
            fprintf(file, "%s,%s\n", dados[i].nome, dados[i].telefone);
        }
        fclose(file);
        nsalvo = 0;
    }
}

int main(){
    abriragnd();

    int menu;
    do{
        puts("Menu:\n1- Cadastro de novo contato\n2- Imprimir agenda em tela\n3- Deletar um contato\n4- Salvar em arquivo\n5- Sair\nEscolha uma opcao:");
        scanf("%d", &menu);

        switch (menu){
            case 1:
                cadast();
                break;
            case 2:
                imprim();
                break;
            case 3:
                delet();
                break;
            case 4:
                salvaragnd();
                printf("Agenda salva\n");
                break;
            case 5:
                if (nsalvo) {
                    salvaragnd();
                    printf("Agenda salva antes de sair\n");
                }
                printf("Saindo\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente\n");
        }
    }while (menu != 5);

    free(dados);
    return 0;
}