#ifndef CARAVANA_H
#define CARAVANA_H
#include <string>
using namespace std;


class Caravana {
    int id;
    int tripulacao; // tripulantes
    int carga;      // carga em toneladas
    int agua;       // água disponível
    string tipo;
    int linha;      // Posição na linha
    int coluna;     // Posição na coluna

public:
    Caravana(int id, const std::string& tipo, int linha, int coluna);
    virtual void mostrarEstado() const;      // Exibir estado da caravana (virtual for polymorphism)
    virtual void mover(char direcao);        // Mover a caravana

    //sets
    void reduzirTripulacao(int quantidade);  // Reduzir tripulantes
    void aumentarTripulacao(int quantidade); // Aumentar tripulantes
    void destruir();                         // Destruir caravana
    void definirPosicao(int linha, int coluna); // Definir nova posição
    //gets
    int obterLinha() const;                  // Obter linha atual
    int obterColuna() const;                 // Obter coluna atual
    int obterTripulacao() const;             // Obter tripulação

    virtual ~Caravana() {}
};



#endif //CARAVANA_H
