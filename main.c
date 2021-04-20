#include <stdio.h>
#include <stdlib.h>
#include "record.h"



int main(int argc, char const *argv[])
{
    char fname[100];
    int opt = 0;

    //Ler o nome do arquivo e a operação
    scanf("%s %d", fname, &opt);

    FILE *data = NULL;
    if ( data = fopen(fname, "r+") == NULL)
        puts("Error while opening file.");

    switch (opt)
    {
    case 1:
        /* code */
        break;
    
    default:
        break;
    }
    return 0;
}