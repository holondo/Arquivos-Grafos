#ifndef STUDENT_CLASS
#define STUDENT_CLASS
#include <string>
#include <cstring>
using namespace std;
#include <iostream>
#include <fstream>
#include "Node.h"

#define MAX_STRING 50
#define STUDENT_SIZE 162

class student
{
    private:
        int nUSP;
        string nome;
        string sobrenome;
        string curso;
        float nota;

    public:
        student(int nUSP, string nome, string sobrenome, string curso, float nota);

        bool CreateFile();
        void ReadInFile(long RRN);
        Node* WriteInFile();
        Node* UpdateInFile(Node* AttNode);
        void justWrite(FILE* arq);
        void transformToCharArray(FILE *arq);
        void setNUSP(int nUSP);
        void setNome(string nome);
        void setSobrenome(string sobrenome);
        void setCurso(string curso);
        void setNota(float nota);

        int getNUSP();
        string getNome();
        string getSobrenome();
        string getCurso();
        float getNota();

        string toString();
};
#endif