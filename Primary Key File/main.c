#include <stdio.h>
#include <string.h>
#include "student.h"

#define FILE_NAME "rec.bin"

/*int getArg(char strArg[MAX_STRING])
{
    char aux = '\0';
    int i = 0;
    while (1)
    {
        aux = getchar();
        if(aux == EOF && i == 0) return ERROR_;
        if(aux == ',' || aux == ';' || aux == '\n' || aux == EOF)//Se for final do campo
        {
            strArg[i] = '\0'; //Finaliza string        
            break;
        }
        strArg[i] = aux;
        i++;
    }

    if(aux == EOF) return ALERT_;
    return SUCCESS_;
}*/

void menu(FILE* data)
{
    char strArg[MAX_STRING];

    while (scanf("%s", strArg))
    {
        if(!strcmp(strArg, "insert")) //strcmp() returns 0 if strings are equal
        {
            //lineToRecord(data);
        }

        if(!strcmp(strArg, "search"))
        {
            
        }

        if(!strcmp(strArg, "delete"))
        {
            
        }

        if(!strcmp(strArg, "exit")) return;
    }
}

int main(int argc, char const *argv[])
{
    FILE *data;
    data = fopen(FILE_NAME, "w+");

    menu(data);
    return 0;
}
