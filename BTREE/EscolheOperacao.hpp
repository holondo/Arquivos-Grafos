#ifndef ESCOLHE_OPERACAO_CLASS
#define ESCOLHE_OPERACAO_CLASS
#include <iostream>
#include <fstream>
#include <string>

#include "TrataInput.hpp"
#include "BTREE.hpp"

using namespace std;

void abreArquivoLimpo();
BTREE* iniciaBTREE();
void recebeOperacao(BTREE* btri);
void abreLimpando(FILE* arquivoEstudantes,FILE* arquivoIndice);

string escolheOperacao(string operacao, BTREE* btri);
void insert(string inputTotal, BTREE* btri);
void search(string inputTotal, BTREE* btri);
void update(string inputTotal, BTREE* btri);
#endif