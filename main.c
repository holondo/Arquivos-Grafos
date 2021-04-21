#include <stdio.h>
#include <stdlib.h>
#include "record.h"

void menu(int opt, FILE *data)
{
    switch (opt)
    {
    case 1:
        print_all(data);
        break;
    
    case 2:
        print_interval(data, 0, (records_quantity(data) / 2));
        break;

    case 3:
        print_interval(data, (records_quantity(data) / 2), (records_quantity(data) - 1));
        break;

    case 4:
        int start, end;
        scanf("%d %d", &start, &end);
        print_interval(data, start, end);
        break;

    case 5:
        int pos;
        scanf("%d", &pos);
        //print_record(recover_record(data, pos));
    
    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    char fname[100];
    int opt = 0;

    //Ler o nome do arquivo e a operação
    scanf("%s %d", fname, &opt);

    FILE *data = NULL;
    if ( data = fopen(fname, "r+") == NULL)
        puts("Error while opening file.");

    
    return 0;
}