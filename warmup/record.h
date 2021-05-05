#ifndef RECORD_H_
#define RECORD_H

#define MAX_STRING 50
#define RECORD_SIZE 108

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct record RECORD;

RECORD* new_record();
RECORD recover_record(FILE *data, int pos);
int records_quantity(FILE *data);
void print_all(FILE *data);
void print_interval(FILE *data, int start, int end);
void print_record(RECORD n_record);
int print_record_byPos(FILE *data, int pos);
int lineToRecord(RECORD *n_record);
void csv2bin(FILE *data);

#endif