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

//Recupera um registro com posição pos especifica (0...)
RECORD recover_record(FILE *data, int pos)
{
    RECORD *cur_record = new_record();
    if(pos <= (records_quantity(data) - 1))
    {

        fseek(data, pos * RECORD_SIZE, SEEK_SET);

        fread(&cur_record->nUSP, sizeof(int), 1, data);
        fread(&cur_record->nome, MAX_STRING, 1, data);
        fread(&cur_record->curso, MAX_STRING, 1, data);
        fread(&cur_record->nota, sizeof(float), 1, data);
    }
    RECORD ret = *cur_record;
    free(cur_record);
    return ret;
}

//Retorna a quantidade de registros no arquivo (1...)
int records_quantity(FILE *data)
{
    fseek(data, 0, SEEK_END);

    return (ftell(data) / ( RECORD_SIZE - 1) );// verificar
}

void print_all(FILE *data)
{
    RECORD *n_record = new_record();
    *n_record = recover_record(data, 0 );

    for (int i = 0; i < records_quantity(data); i++)
    {
        *n_record = recover_record(data, i);
        //print_record()
    }    
}

void print_interval(FILE *data, int start, int end)
{ 
    RECORD *n_record = new_record();

    for (int i = start; i <= end; i++)
    {
        *n_record = recover_record(data, i);
        //print_record
    }

}



