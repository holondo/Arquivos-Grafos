#include "record.h"

struct record
{
    int nUSP;
    char nome[MAX_STRING];
    char curso[MAX_STRING];
    float nota;
};


//Retorna um ponteiro para um novo registro vazio
RECORD* new_record(){
    RECORD *n_record;
    n_record = malloc(sizeof(RECORD));

    n_record->nUSP = -1;
    n_record->nota = -1;
    strcpy(n_record->nome, "\0");
    strcpy(n_record->curso, "\0");

    return n_record;
}





