#ifndef CARAVANA_H
#define CARAVANA_H
#include <string>
#include <iostream>
#include <vector>
#include "../Mapa/Mapa.h"
#include "../Itens/Item.h"
#include <sstream>
using namespace std;


class Caravana {
protected:
    static int nID;
    int id;
    int tripulacao; // tripulantes
    int carga;      // carga em toneladas
    int agua;       // água disponível
    string tipo;
    int linha;      // Posição na linha
    int coluna;     // Posição na coluna
    bool isAutonoma;
    bool semTripulantes; // Indica se a caravana está sem tripulantes
    int instantesRestantes; // Contador de instantes antes de desaparecer
public:
    Caravana(const string &tipo, int linha, int coluna);

    virtual string mostrarEstado() const;      // Exibir estado da caravana (virtual for polymorphism)
    virtual char obterRepresentacao() const;

    virtual void afetadaPorTempestade();

    void atualizarEstadoSemTripulantes(int linhas, int colunas, const vector<Caravana *> &caravanas,
                                       const vector<Item> &itens, const Mapa &mapa);

    virtual void moverAutonomo(int mapaLinhas, int mapaColunas, const vector<Caravana*>& caravanas,
                                const vector<Item>& itens, const Mapa &mapa);
    virtual void mover(char direcao, int mapaLinhas, int mapaColunas, const Mapa &mapa);         // Mover a caravana


    void reduzirTripulacao(int quantidade);  // Reduzir tripulantes
    void aumentarTripulacao(int quantidade); // Aumentar tripulantes
    void reduzirCarga(int quantidade);       // Reduzir carga
    virtual void aumentarCarga(int quantidade);     // Aumentar carga
    void reduzirAgua(int quantidade);
    virtual void aumentarAgua(int quantidade);

    virtual void gastarAgua();

    void destruir();// Destruir caravana

    bool estaSemTripulantes();
    bool deveDesaparecer() const;

    //sets
    void definirPosicao(int linha, int coluna); // Definir nova posição
    void setEstadoAutonoma(bool estado);

    //gets
    int obterLinha() const;                  // Obter linha atual
    int obterColuna() const;                 // Obter coluna atual
    int obterTripulacao() const;             // Obter tripulação
    int obterID() const;
    bool obterEstadoAutonoma() const;

    virtual ~Caravana() {}


};



#endif //CARAVANA_H
