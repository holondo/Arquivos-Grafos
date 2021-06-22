#include <string>
using namespace std;

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

        void setNUSP(int nUSP);
        void setNome(string nome);
        void setSobrenome(string nome);
        void setCurso(string curso);
        void setNota(float nota);

        int getNUSP();
        string getNome();
        string getSobrenome();
        string getCurso();
        float getNota();

        string toString();
};