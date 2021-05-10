#ifndef STATIC_FH_
#define STATIC_FH_

#include "student.h"

int recordsQuantity(FILE *data);
int recoverRecord(Student *curRecord,FILE *data, int pos);
void writeRecordBin(FILE *data, Student *toWrite, int position);
int sequentialSearch(Student *toFill, FILE *data, int nUSPToSearch);
int deleteRecordLogically(FILE *data, int pos);
void printAll(FILE *data);

#endif