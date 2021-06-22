#include "student.h"

struct _STUDENT
{
    int nUSP;
    char nome[MAX_STRING];
    char sobrenome[MAX_STRING];
    char curso[MAX_STRING];
    float nota;
};

//Retorns a pointer to a new allocated and inicialized record.
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

//Frees a record's allocated memory 
void closeRecord(Student *bye_record)
{   
    free(bye_record);
}

//Prints a formatted record
void printRecord(Student *nRecord)
{
    if(nRecord->nUSP == -1) return; 
    printf("-------------------------------\nUSP number: %d\nName: %s\nSurname: %s\nCourse: %s\nTest grade: %.2f\n-------------------------------\n"
    , nRecord->nUSP, nRecord->nome, nRecord->sobrenome, nRecord->curso, nRecord->nota);
}

//--------------------Getters area--------------------

//Returns nUSP from a record
int getnUSP(Student *thisRec)
{
    return thisRec->nUSP;
}

int getName(char nome[MAX_STRING], Student *thisRec)
{
    strcpy(nome, thisRec->nome);
}

int getSurname(char sobrenome[MAX_STRING], Student *thisRec)
{
    strcpy(sobrenome, thisRec->sobrenome);
    return SUCCESS_;
}

int getCourse(char curso[MAX_STRING], Student *thisRec)
{
    strcpy(curso, thisRec->curso);
    return SUCCESS_;
}

int getGrade(Student *thisRec)
{
    return thisRec->nota;
}

//--------------------Setters area--------------------

int setnUSP(Student *thisRec, int nUSP)
{
    thisRec->nUSP = nUSP;
    return SUCCESS_;
}

int setName(Student *thisRec, char nome[MAX_STRING])
{
    strcpy(thisRec->nome, nome);
    return SUCCESS_;
}

int setSurname(Student *thisRec, char sobrenome[MAX_STRING])
{
    strcpy(thisRec->sobrenome, sobrenome);
    return SUCCESS_;
}

int setCourse(Student *thisRec, char curso[MAX_STRING])
{
    strcpy(thisRec->curso, curso);
    return SUCCESS_;
}

int setGrade(Student *thisRec, int nota)
{
    thisRec->nota = nota;
    return SUCCESS_;
}

/*Reads a CSV formatted line and turns it into a Student struct
    1 if concluded. 0 if EOF*/
int lineToRecord(Student *nRecord)
{
    int i = 0, j = 0;
    char aux = '!'; 
    char strRecord[5][MAX_STRING];//Strings de informações obtidas do registro
    Student auxRecord;

    while (1)
    {
        aux = getchar();
        if(aux == EOF && i == 0) return ERROR_;
        if(aux == ',' || aux == ';' || aux == '\n' || aux == EOF)//Se for final do campo
        {
            strRecord[i][j] = '\0'; //Finaliza string
            j = 0;
            i++; //Proximo campo
            if(aux == EOF)break;
            if(aux == '\n') break;            
            continue;
        }
        strRecord[i][j] = aux;
        j++;
    }

    strcpy(auxRecord.curso, strRecord[2]);
    //Salva-se no registro valores numericos
    auxRecord.nUSP = atoi(strRecord[0]);
    auxRecord.nota = atoi(strRecord[4]);

    //Salva-se no registro o texto
    strcpy(auxRecord.nome, strRecord[1]);
    strcpy(auxRecord.sobrenome, strRecord[2]);
    strcpy(auxRecord.curso, strRecord[3]);

    *nRecord = auxRecord;
    if(aux == EOF)return ALERT_;
    return SUCCESS_;
}