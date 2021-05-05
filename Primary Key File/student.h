#ifndef STUDENT_H_
#define STUDENT_H

#define MAX_STRING 50
#define RECORD_SIZE 108

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct _STUDENT Student;

Student* newRecord();
void print_record(Student n_record);
int lineToRecord(Student *n_record);

#endif