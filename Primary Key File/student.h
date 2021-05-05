#ifndef STUDENT_H_
#define STUDENT_H

#define MAX_STRING 50
#define RECORD_SIZE 108

//Function not successful
#define ERROR_ 0;

//Function successful
#define SUCCESS_ 1;

//Function alert for next iterations
#define ALERT_ -1;

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct _STUDENT Student;

Student* newRecord();
void print_record(Student n_record);
int lineToRecord(Student *n_record);

#endif