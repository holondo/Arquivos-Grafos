#include "EscolheOperacao.hpp"

int main(){
  BTREE * btri = new BTREE("students.bin", "index.bin");
  student* a = new student(1,"a","a", "a", 9);

  // for(int i = 0; i < MAXKEYS * 3; i ++)
  // {
  //   a->setNUSP(i);
  //   btri->insertStudent(a);
  // }
  recebeOperacao(btri);
  btri->close();
}
