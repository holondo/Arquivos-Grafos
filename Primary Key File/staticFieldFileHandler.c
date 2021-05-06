#include "staticFieldFileHandler.h"

//Escreve um registro em certa posição dentro arquivo binário
void writeRecordBin(FILE *data, Student *toWrite, int position)
{
    //if(position > (records_quantity(data))) position = records_quantity(data);

    fseek(data, position * RECORD_SIZE, SEEK_SET);

    int nUSP = getnUSP(toWrite), nota = getGrade(toWrite);
    char nome[MAX_STRING], curso[MAX_STRING], sobrenome[MAX_STRING];
    getName(nome, toWrite);
    getSurname(sobrenome, toWrite);
    getCourse(curso, toWrite);
    /*fwrite(&toWrite.nUSP, sizeof(int), 1, data);
    fwrite(&toWrite.nome, MAX_STRING, 1, data);
    fwrite(&toWrite.curso, MAX_STRING, 1, data);
    fwrite(&toWrite.nota, sizeof(float), 1, data);*/
}