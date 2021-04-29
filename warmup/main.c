#include <stdio.h>
#include <stdlib.h>
#include "record.h"

//menu para selecao de funcao no programa
void menu(int opt, FILE *data)
{
    int start, end, pos;
    switch (opt)
    {
    case 1:
        print_all(data);
        break;
    
    case 2:
        print_interval(data, 0, (records_quantity(data) / 2) -1);
        break;

    case 3:
        print_interval(data, (records_quantity(data) / 2) , (records_quantity(data) - 1));
        break;

    case 4:
        
        scanf("%d %d", &start, &end);
        print_interval(data, start-1, end-1);//-1 pq a função usa posições absolutas
        break;

    case 5:
        scanf("%d", &pos);
        print_record_byPos(data, pos-1);//-1 pq a função usa posições absolutas
        break;
    
    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    /*char fname[100];//file name
    int opt = 0;

    //Ler o nome do arquivo e a operação
    scanf("%s %d", fname, &opt);

    FILE *data = NULL;
    if ( (data = fopen(fname, "r+") ) == NULL)//se não existir arq. com o nome ou arq. com problema
        puts("Error while opening file.");

    menu(opt, data);*/

    RECORD* aux = new_record();
    lineToRecord(aux);
    //fclose(data);    
    return 0;
}