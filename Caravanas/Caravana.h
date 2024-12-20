#ifndef CARAVANA_H
#define CARAVANA_H
#include <string>
#include <iostream>
using namespace std;


class Caravana {
    static int nID;
    int id;
    int tripulacao; // tripulantes
    int carga;      // carga em toneladas
    int agua;       // água disponível
    string tipo;
    int linha;      // Posição na linha
    int coluna;     // Posição na coluna

public:
    Caravana(const string &tipo, int linha, int coluna);

    virtual void mostrarEstado() const;      // Exibir estado da caravana (virtual for polymorphism)
    virtual void mover(char direcao);        // Mover a caravana
    virtual char obterRepresentacao() const;

    //sets
    void reduzirTripulacao(int quantidade);  // Reduzir tripulantes
    void aumentarTripulacao(int quantidade); // Aumentar tripulantes
    void destruir();                         // Destruir caravana
    void definirPosicao(int linha, int coluna); // Definir nova posição
    //gets
    int obterLinha() const;                  // Obter linha atual
    int obterColuna() const;                 // Obter coluna atual
    int obterTripulacao() const;             // Obter tripulação
    int obterID() const;

    virtual ~Caravana() {}
};



#endif //CARAVANA_H
