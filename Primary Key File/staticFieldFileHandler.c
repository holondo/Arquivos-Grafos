#include "staticFieldFileHandler.h"

//Retorns the number of records in the file. [1...]
int recordsQuantity(FILE *data)
{
    fseek(data, 0, SEEK_END);

    return (int)( (ftell(data) / (long)( RECORD_SIZE ) ) );// verificar
}

//Recovers a record with a specific position [0...]
int recoverRecord(Student *curRecord,FILE *data, int pos)
{
    int nUSP, nota;
    char nome[MAX_STRING], sobrenome[MAX_STRING], curso[MAX_STRING];
    if(pos <= (recordsQuantity(data) - 1))
    {

        fseek(data, pos * RECORD_SIZE, SEEK_SET);

        fread(&nUSP, sizeof(int), 1, data);
        fread(&nome, MAX_STRING, 1, data);
        fread(&sobrenome, MAX_STRING, 1, data);
        fread(&curso, MAX_STRING, 1, data);
        fread(&nota, sizeof(float), 1, data);

        setnUSP(curRecord, nUSP);
        setName(curRecord, nome);
        setSurname(curRecord, sobrenome);
        setCourse(curRecord, curso);
        setGrade(curRecord, nota);
        
        return SUCCESS_;
    }
    else return ERROR_;
}

//Writes the record in a specific position in the file
void writeRecordBin(FILE *data, Student *toWrite, int position)
{
    if(position > (recordsQuantity(data))) position = recordsQuantity(data);
    fseek(data, position * RECORD_SIZE, SEEK_SET);

    int nUSP = getnUSP(toWrite), nota = getGrade(toWrite);
    char nome[MAX_STRING], curso[MAX_STRING], sobrenome[MAX_STRING];
    getName(nome, toWrite);
    getSurname(sobrenome, toWrite);
    getCourse(curso, toWrite);
    fwrite(&nUSP, sizeof(int), 1, data);
    fwrite(&nome, MAX_STRING, 1, data);
    fwrite(&sobrenome, MAX_STRING, 1, data);
    fwrite(&curso, MAX_STRING, 1, data);
    fwrite(&nota, sizeof(float), 1, data);
    fflush(NULL);
}

/*Searches sequentially for a specific nUSP and recovers its information into a given Structure
[RETURN]:
-1 if record not found.
(int)position of found record in file [0...]*/
int sequentialSearch(Student *toFill, FILE *data, int nUSPToSearch)
{
    int verifier, lastRecord = recordsQuantity(data), counter = 0;
    while(1)
    {
        if(counter > lastRecord) return ALERT_;

        fseek(data, counter * RECORD_SIZE, SEEK_SET);
        fread(&verifier, sizeof(int), 1, data);

        if(verifier == nUSPToSearch) break;

        counter++;
    }
    
    recoverRecord(toFill, data, counter);

    return counter;    
}

int deleteRecordLogically(FILE *data, int pos)
{
    int setter = -1;
    if(data == NULL || pos > recordsQuantity(data)) return ERROR_;

    fseek(data, pos * RECORD_SIZE, SEEK_SET);
    fwrite(&setter, sizeof(int), 1, data);
    return SUCCESS_;
}

//printa todos os registros do arquivo
void printAll(FILE *data)
{
    Student *n_record = newRecord();

    for (int i = 0; i < recordsQuantity(data); i++)
    {
        recoverRecord(n_record, data, i);
        printRecord(n_record);
        if(i < recordsQuantity(data) - 1) putc('\n', stdout);
    }

    closeRecord(n_record);
}