#include "student.h"

student::student(int nUSP, string nome, string sobrenome, string curso, float nota)
{
    this->setNUSP(nUSP);
    this->setNome(nome);
    this->setSobrenome(sobrenome);
    this->setCurso(curso);
    this->setNota(nota);
}

//File area
bool student::CreateFile(){
  
  FILE* TestArchive;
  if((TestArchive=fopen("students.bin","ab+"))==NULL){
    return false;

  }
  fclose(TestArchive);
  return true;
}

void student::ReadInFile(long RRN){
    FILE* arq;
    if(!CreateFile()){
      return;
    }
    if((arq=fopen("students.bin","rb+"))==NULL){
      cout << "nao foi possivel abrir o arquivo students.bin para leitura"<< endl;
      return;
    }
    fseek(arq,RRN,SEEK_SET);
    transformToCharArray(arq);

    fclose(arq);
}

Node* student::WriteInFile(){
    FILE* arq;
    long RRN;
    char CopyString[50];
    if(!CreateFile()){
      return NULL;
    }
    if((arq=fopen("students.bin","rb+"))==NULL){
      cout << "nao foi possivel abrir o arquivo students.bin para a escrita"<< endl;
      return NULL;
    }
    
    fseek(arq,0,SEEK_END);
    RRN=ftell(arq)/STUDENT_SIZE;//dando erro
    justWrite(arq);
    Node* CurrentNode = new Node(this->nUSP,RRN);
    fclose(arq);
    return CurrentNode;
}

Node* student::UpdateInFile(Node* AttNode){
    FILE* arq;
    if(!CreateFile()){
      return NULL;
    }
    if((arq=fopen("students.bin","rb+"))==NULL){
      cout << "nao foi possivel abrir o arquivo students.bin para a atualizacao"<< endl;
      return NULL;
    }
    fseek(arq,AttNode->getRRN() * STUDENT_SIZE,SEEK_SET);
    justWrite(arq);
    fclose(arq);
    AttNode->setKey(this->nUSP);
    return AttNode;
}

void student::justWrite(FILE* arq){
  char CopyString[50];
  fwrite(&this->nUSP,sizeof(int),1,arq);
  strcpy(CopyString,this->nome.c_str());
  fwrite(CopyString,MAX_STRING,1,arq);
  strcpy(CopyString,this->sobrenome.c_str());
  fwrite(CopyString,MAX_STRING,1,arq);
  strcpy(CopyString,this->curso.c_str());
  fwrite(CopyString,MAX_STRING,1,arq);
  fwrite(&this->nota,sizeof(float),1,arq);
}

void student::transformToCharArray(FILE* arq){
  char CopyString[50];
  fread(&nUSP,sizeof(int),1,arq);
  fread(CopyString,50,1,arq);
  nome.clear();

  for(long unsigned int i=0;i<strlen(CopyString);i++){
    nome+=CopyString[i];
  }

  fread(CopyString,50,1,arq);
  sobrenome.clear();
  for(long unsigned int i=0;i<strlen(CopyString);i++){
    sobrenome+=CopyString[i];
  }

  strcpy(CopyString,curso.c_str());
  curso.clear();
  for(long unsigned int i=0;i<strlen(CopyString);i++){
    curso+=CopyString[i];
  }
  fread(CopyString,50,1,arq);

  fread(&nota,sizeof(float),1,arq);
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
void student::setSobrenome(string sobrenome)
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

string student::FormatNota(){
  float Novanota = this->getNota()*100;
  int Unidade = (int) Novanota;
  int Decimais = Unidade%100;
  Unidade =Unidade/100;
  string UnidadeDecimais = to_string(Unidade)+"."+ to_string(Decimais);
  return UnidadeDecimais;
}

string student::toString()
{
    string toReturn = "−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n";
    toReturn += "nUSP: " + to_string(this->getNUSP()) + '\n';
    toReturn += "Nome: " + this->getNome() + '\n';
    toReturn += "Sobrenome: " + this->getSobrenome() + '\n';
    toReturn += "Curso: " + this->getCurso() + '\n';
    toReturn += "Nota: " + this->FormatNota() + '\n'; //toDo: como acertar o ponto flutuante
    toReturn += "−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n";
    return toReturn;
}