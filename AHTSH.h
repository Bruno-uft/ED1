#ifndef TAHTSH_H
#define TAHTSH_H
#include<stdbool.h>

typedef struct{
    char nome[128], telefone[15];
}TContato;

typedef struct _list TAHTSH;

TAHTSH* a_create();

void a_open(TAHTSH*, int*);

bool a_register(TAHTSH*, TContato*, int*, int*); 

void a_print(TAHTSH*);

bool a_delete_end(TAHTSH*);

void a_save(TAHTSH*);

#endif