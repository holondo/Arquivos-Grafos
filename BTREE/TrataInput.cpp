#include "TrataInput.hpp"
//divide as entradas
student* processaRegistro(char *inputParaSerDissecado) {
  char *operador = strtok(inputParaSerDissecado, " ");
  if(operador == NULL){
    return NULL;
  } 
    
  //pega a entrada e retira o nUSP como string
  char *nUSPString = strtok(NULL, ",");
  if (nUSPString == NULL){ 
    return NULL;
  }
  int nUSP = atoi(nUSPString);

  //pega a entrada e retira o Nome como string
  char *nomeChar = strtok(NULL, ",");
  if (nomeChar == NULL){
    return NULL;
  }
  //tira aspas e volta string
  string nome = tiraAspas(nomeChar);

  //pega a entrada e retira o sobrenome como string
  char *sobreNomeChar = strtok(NULL, ",");
  if (sobreNomeChar == NULL){
    return NULL;
  }
  //tira aspas e volta string
  string sobreNome = tiraAspas(sobreNomeChar);

  //pega a entrada e retira o Curso como string
  char *cursoChar = strtok(NULL, ",");
  if (cursoChar == NULL){
    return NULL;
  }
  //tira aspas e volta string
  string curso = tiraAspas(cursoChar);

  //pega a entrada e retira a Nota como string
  char *notaString = strtok(NULL, ",");
  if (notaString == NULL){
    return NULL;
  } 
  //transforma a nota em float
  float nota = atof(notaString);
  student* Student = new student(nUSP, nome, sobreNome, curso, nota);
  return Student;
}

//tira as aspas dos input e volta para string
string tiraAspas(char* str){
  //transforma em string
  string operador = str;
  //apaga primeira aspas
  operador.erase(0, 1);
  //apaga aspas de fechamento
  operador.erase(operador.length() -1, 1);
  //retorna a string
  return operador;
}