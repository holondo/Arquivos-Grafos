#include "record.h"

struct record
{
    int nUSP;
    char nome[MAX_STRING];
    char curso[MAX_STRING];
    float nota;
};


//Retorna um ponteiro para um novo registro vazio
RECORD* new_record(){
    RECORD *n_record;
    n_record = malloc(sizeof(RECORD));

    n_record->nUSP = -1;
    n_record->nota = -1;
    strcpy(n_record->nome, "\0");
    strcpy(n_record->curso, "\0");

    return n_record;
}

//Desaloca a memoria de um registro.
void close_record(RECORD *bye_record)
{   
    free(bye_record);
}

//Printa um registro formatado
void print_record(RECORD n_record)
{
    printf("nUSP: %d\nNome: %s\nCurso: %s\nNota: %.2f\n", n_record.nUSP, n_record.nome, n_record.curso, n_record.nota);
}

/*void terminate_string(char **str)
{

}*/

//Recupera um registro com posição pos especifica [0...]
RECORD recover_record(FILE *data, int pos)
{
    RECORD *cur_record = new_record();
    if(pos <= (records_quantity(data) - 1))
    {

        fseek(data, pos * RECORD_SIZE, SEEK_SET);

        fread(&cur_record->nUSP, sizeof(int), 1, data);
        fread(&cur_record->nome, MAX_STRING, 1, data);
        fread(&cur_record->curso, MAX_STRING, 1, data);
        fread(&cur_record->nota, sizeof(float), 1, data);
    }
    RECORD ret = *cur_record;
    close_record(cur_record);
    return ret;
}

//Retorna a quantidade de registros no arquivo (1...)
int records_quantity(FILE *data)
{
    fseek(data, 0, SEEK_END);

    return (int)( (ftell(data) / (long)( RECORD_SIZE ) ) );// verificar
}

//printa todos os registros do arquivo
void print_all(FILE *data)
{
    RECORD *n_record = new_record();
    *n_record = recover_record(data, 0);

    for (int i = 0; i < records_quantity(data); i++)
    {
        *n_record = recover_record(data, i);
        print_record(*n_record);
        if(i < records_quantity(data) - 1) putc('\n', stdout);
    }

    close_record(n_record);
}

//printa um intervalo absoluto de registros [0...]
void print_interval(FILE *data, int start, int end)
{ 
    RECORD *n_record = new_record();
    int reqQuantity = records_quantity(data) - 1;
    if(start > reqQuantity) return;

    for (int i = start; i <= end; i++)
    {
        *n_record = recover_record(data, i);
        if(i > reqQuantity || n_record->nUSP == -1) break;
        if(i != start)
            putchar('\n');
        print_record(*n_record);
    }
    close_record(n_record);
}

//printa um registro com base na sua posição absoluta [0...]
int print_record_byPos(FILE *data, int pos)
{
    RECORD n_record = recover_record(data, pos);
    
    printf("nUSP: %d\nNome: %s\nCurso: %s\nNota: %.2f\n", n_record.nUSP, n_record.nome, n_record.curso, n_record.nota);
    
    return 0;
}

/*Le uma linha do CSV e a tranforma em um REGISTRO.
    1 se concluido. 0 se EOF*/
int lineToRecord(RECORD *n_record)//TODO: Tudo
{
    int i = 0, j = 0;
    char aux = '!'; 
    char str_Record[4][MAX_STRING];//Strings de informações obtidas do registro
    RECORD r_aux;

    while (1)
    {
        aux = getchar();
        if(aux == EOF && i == 0) return 0;
        if(aux == ',' || aux == ';' || aux == '\n' || aux == EOF)//Se for final do campo
        {
            str_Record[i][j] = '\0'; //Finaliza string
            j = 0;
            i++; //Proximo campo
            if(aux == EOF)break;
            if(aux == '\n') break;            
            continue;
        }
        str_Record[i][j] = aux;
        j++;
    }

    //Salva-se no registro valores numericos
    r_aux.nUSP = atoi(str_Record[0]);
    r_aux.nota = atoi(str_Record[3]);

    //Salva-se no registro o texto
    strcpy(r_aux.nome, str_Record[1]);
    strcpy(r_aux.curso, str_Record[2]);

    *n_record = r_aux;
    if(aux == EOF)return 0;
    return 1;
}

//Escreve um registro em certa posição dentro arquivo binário
void write_record(FILE *data, RECORD toWrite, int position)
{
    if(position > (records_quantity(data))) position = records_quantity(data);

    fseek(data, position * RECORD_SIZE, SEEK_SET);

    fwrite(&toWrite.nUSP, sizeof(int), 1, data);
    fwrite(&toWrite.nome, MAX_STRING, 1, data);
    fwrite(&toWrite.curso, MAX_STRING, 1, data);
    fwrite(&toWrite.nota, sizeof(float), 1, data);
}

//Lida com o CSV vindo do stdin lendo e escrevendo registros no arq. binario.
void csv2bin(FILE *data)
{
    RECORD *n_record = new_record();
    int pos = records_quantity(data);
    int aux;
    while (1)
    {
        aux = lineToRecord(n_record);

        write_record(data, *n_record, pos);
        fflush(NULL);
        pos++;
        
        if(!aux) break;
    }

    close_record(n_record);
}