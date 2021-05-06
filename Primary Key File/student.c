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

//Printa um registro formatado
void printRecord(Student *nRecord)
{
    printf("nUSP: %d\nNome: %s\nCurso: %s\nNota: %.2f\n", nRecord->nUSP, nRecord->nome, nRecord->curso, nRecord->nota);
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

/*Le uma linha do CSV e a tranforma em um REGISTRO.
    1 se concluido. 0 se EOF*/
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