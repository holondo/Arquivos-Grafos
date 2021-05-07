#ifndef STUDENT_H_
#define STUDENT_H

#define DEBUG_ 1;

#define MAX_STRING 50
#define RECORD_SIZE 158

//Function not successful
#define ERROR_ 0;

//Function successful
#define SUCCESS_ 1;

//Function alert for next iterations
#define ALERT_ -1;

#define REMOVED_ -1 ;

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct _STUDENT Student;

Student* newRecord();
void closeRecord(Student *bye_record);
int lineToRecord(Student *nRecord);
void printRecord(Student *nRecord);

int getnUSP(Student *thisRec);
int getName(char nome[MAX_STRING], Student *thisRec);
int getSurname(char sobrenome[MAX_STRING], Student *thisRec);
int getCourse(char curso[MAX_STRING], Student *thisRec);
int getGrade(Student *thisRec);

int setnUSP(Student *thisRec, int nUSP);
int setName(Student *thisRec, char nome[MAX_STRING]);
int setSurname(Student *thisRec, char sobrenome[MAX_STRING]);
int setCourse(Student *thisRec, char curso[MAX_STRING]);
int setGrade(Student *thisRec, int nota);

#endif