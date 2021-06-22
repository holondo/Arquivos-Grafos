#include "student.h"

student::student(int nUSP, string nome, string sobrenome, string curso, float nota)
{
    setNUSP(nUSP);
    setNome(nome);
    setSobrenome(sobrenome);
    setCurso(curso);
    setNota(nota);
}

//Setters area
void student::setNUSP(int nUSP)
{
    this->nUSP = nUSP;
}
void student::setNome(string nome)
{
    this->nome = nome;
}
void student::setSobrenome(string nome)
{
    this->sobrenome = sobrenome;
}
void student::setCurso(string curso)
{
    this->curso = curso;
}
void student::setNota(float nota)
{
    this->nota = nota;
}

//Getters area
int student::getNUSP()
{
    return this->nUSP;
}
string student::getNome()
{
    return this->nome;
}
string student::getSobrenome()
{
    return this->sobrenome;
}
string student::getCurso()
{
    return this->curso;
}
float student::getNota()
{
    return this->nota;
}

string student::toString()
{
    string toReturn = "−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n";
    toReturn += "nUSP: " + to_string(this->getNUSP()) + '\n';
    toReturn += "Nome: " + this->getNome() + '\n';
    toReturn += "Sobrenome: " + this->getSobrenome() + '\n';
    toReturn += "Curso: " + this->getCurso() + '\n';
    toReturn += "Nota: " + to_string(this->getNota()) + '\n'; //toDo: como acertar o ponto flutuante
    toReturn += "−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n";
    return toReturn;
}