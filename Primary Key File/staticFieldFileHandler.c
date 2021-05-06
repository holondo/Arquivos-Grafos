#include "staticFieldFileHandler.h"

//Retorna a quantidade de registros no arquivo (1...)
int records_quantity(FILE *data)
{
    fseek(data, 0, SEEK_END);

    return (int)( (ftell(data) / (long)( RECORD_SIZE ) ) );// verificar
}

//Escreve um registro em certa posição dentro arquivo binário
void writeRecordBin(FILE *data, Student *toWrite, int position)
{
    if(position > (records_quantity(data))) position = records_quantity(data);

    fseek(data, position * RECORD_SIZE, SEEK_SET);

    int nUSP = getnUSP(toWrite), nota = getGrade(toWrite);
    char nome[MAX_STRING], curso[MAX_STRING], sobrenome[MAX_STRING];
    getName(nome, toWrite);
    getSurname(sobrenome, toWrite);
    getCourse(curso, toWrite);
    fwrite(&nUSP, sizeof(int), 1, data);
    fwrite(&nome, MAX_STRING, 1, data);
    fwrite(&curso, MAX_STRING, 1, data);
    fwrite(&nota, sizeof(float), 1, data);
}

int sequentialSearch(Student *toFill, FILE *data, int nUSPToSearch)
{
    
}