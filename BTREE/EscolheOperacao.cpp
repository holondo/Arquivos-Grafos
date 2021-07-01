#include "EscolheOperacao.hpp"

string escolheOperacao(string inputTotal, BTREE* btri){
  string operacao = inputTotal.substr(0,inputTotal.find_first_of(' '));
  //deleta a parte que nao vai ser necessaria
  //inputTotal.erase(0,6);
  //reparte a linha inteira para ficar com tamanho 6
  //ao comparar sabe qual operacao executar
  operacao.resize(6);
  //faz as comparacoes
  if (operacao == "insert"){
    try
    {
      insert(inputTotal, btri);
    }
    catch(string e)
    {
      cout << e;
    }
  }
  else if (operacao == "search"){
    inputTotal = inputTotal.erase(0, operacao.length() + 1);
    search(inputTotal, btri);
  }
  else if (operacao == "update") {
    update(inputTotal, btri);
  }
  //se nao estiver identificado, retorna exit
  //para quebrar o loop
  else{
    return "exit";
  } 
  //retorna a operacao para continuar o loop
  return operacao;
}
//funcao para fazer a insercao
void insert(string inputSemOperacao, BTREE* btri){
  //criando um array char para operar com strtok
  char *inputParaSerDissecado = new char [inputSemOperacao.length()+1];
  //copiamos o array que queremos mudar
  strcpy (inputParaSerDissecado, inputSemOperacao.c_str());
  //Vai processar a entrada e colocar no registro

  student* teste = processaRegistro(inputParaSerDissecado);
  btri->insertStudent(teste);
}
//funcao para fazer a busca
void search(string inputSemOperacao, BTREE* btri){
  int nUSP = stoi(inputSemOperacao);
  cout << btri->searchStudent(nUSP);
}
//funcao para fazer a atualizacao
//toma a rota de procura para daí atualizar
void update(string inputSemOperacao, BTREE* btri){
  char *inputParaSerDissecado = new char [inputSemOperacao.length()+1];
  strcpy (inputParaSerDissecado, inputSemOperacao.c_str());
  btri->updateStudent(processaRegistro(inputParaSerDissecado));
}

//
//operacoes mencionadas na main
BTREE* iniciaBTREE(){
  BTREE* btri = new BTREE("students.bin", "index.bin");
  return btri;
}

void recebeOperacao(BTREE* btri){ 
  string operacao;
  do{
    //pega a linha inteira
    getline (cin, operacao);
    //vai retornar a operacao escolhida
    operacao = escolheOperacao(operacao, btri);
    //caso a operacao seja == exit quebra o loop
  }while (operacao != "exit");
}

void abreArquivoLimpo(){
  //declara os arquivos necessarios
  FILE* arquivoEstudantes;
  FILE* arquivoIndice;
  //abre como w para zerar os aquivos
  if((arquivoEstudantes=fopen("students.bin","w"))==NULL){
    cout << "nao foi possivel abrir o arquivo students.bin para leitura"<< endl;
  }
    
  if((arquivoIndice=fopen("index.bin","w"))==NULL){
    cout << "nao foi possivel abrir o arquivo index.bin para leitura"<< endl;
  }
  //fecha os arquivos necessarios
  fclose(arquivoEstudantes);
  fclose(arquivoIndice);
}