#include "student.h"

struct _STUDENT
{
    int nUSP;
    char nome[MAX_STRING];
    char sobrenome[MAX_STRING];
    char curso[MAX_STRING];
    float nota;
};

//Retorna um ponteiro para um novo registro vazio
Student* newRecord(){
    Student *newStudent;
    newStudent = malloc(sizeof(Student));

    newStudent->nUSP = -1;
    newStudent->nota = -1;
    strcpy(newStudent->nome, "\0");
    strcpy(newStudent->sobrenome, "\0");
    strcpy(newStudent->curso, "\0");

    return newStudent;
}

//Desaloca a memoria de um registro.
void closeRecord(Student *bye_record)
{   
    free(bye_record);
}