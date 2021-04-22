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

//Desaloca a memoria de um registro.
void close_record(RECORD *bye_record)
{   
    free(bye_record);
}

//Printa um registro formatado
void print_record(RECORD n_record)
{
    printf("nUSP: %d\nNome: %s\nCurso: %s\nNota: %.2f\n", n_record.nUSP, n_record.nome, n_record.curso, n_record.nota);
}


void terminate_string(char **str)
{

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
    close_record(cur_record);
    return ret;
}

//Retorna a quantidade de registros no arquivo (1...)
int records_quantity(FILE *data)
{
    fseek(data, 0, SEEK_END);

    return (int)( (ftell(data) / (long)( RECORD_SIZE - 1) ) );// verificar
}

void print_all(FILE *data)
{
    RECORD *n_record = new_record();
    *n_record = recover_record(data, 0);

    for (int i = 0; i < records_quantity(data); i++)
    {
        *n_record = recover_record(data, i);
        print_record(*n_record);
        if(i < records_quantity(data) - 1) putc('\n', stdout);
    }

    close_record(n_record);
}

//printa um intervalo absoluto de registros [0...]
void print_interval(FILE *data, int start, int end)
{ 
    RECORD *n_record = new_record();
    int reqQuantity = records_quantity(data) - 1;
    if(start > reqQuantity) return;

    for (int i = start; i <= end; i++)
    {
        *n_record = recover_record(data, i);
        if(i > reqQuantity || n_record->nUSP == -1) break;
        if(i != start)
            putchar('\n');
        print_record(*n_record);
    }
    close_record(n_record);
}

int print_record_byPos(FILE *data, int pos)
{
    RECORD n_record = recover_record(data, pos);
    
    printf("nUSP: %d\nNome: %s\nCurso: %s\nNota: %.2f\n", n_record.nUSP, n_record.nome, n_record.curso, n_record.nota);
    
    return 0;
}


