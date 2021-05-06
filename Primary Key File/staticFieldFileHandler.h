#ifndef STATIC_FH_
#define STATIC_FH_

#include "student.h"

void writeRecordBin(FILE *data, Student *toWrite, int position);
int records_quantity(FILE *data);

#endif