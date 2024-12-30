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
    int maxTripulacao;
    int carga;      // carga em toneladas
    int maxCarga;
    int agua;       // água disponível
    int maxAgua;
    string tipo;
    int linha;      // Posição na linha
    int coluna;     // Posição na coluna
    bool isAutonoma;
    bool semTripulantes; // Indica se a caravana está sem tripulantes
    int instantesRestantes; // Contador de instantes antes de desaparecer
    bool emCidade; // Indica se a caravana já está em uma cidade
    bool modoDetalhado;
    bool isBarbara;
    int duracao;
public:
    Caravana(const string &tipo, int linha, int coluna);

    virtual string mostrarEstado() const;      // Exibir estado da caravana (virtual for polymorphism)
    bool estadoBarbara() const;

    virtual char obterRepresentacao() const;

    virtual void afetadaPorTempestade();

    void atualizarEstadoSemTripulantes(int linhas, int colunas, const vector<Caravana *> &caravanas,
                                       const vector<Item *> &itens, const Mapa &mapa);

    void logDetalhado(const std::string &mensagem);

    void setModoDetalhado(bool estado);

    bool obterModoDetalhado() const;

    int calcularPoderCombate();

    int obterMaxTripulacao() const;

    virtual void moverAutonomo(int mapaLinhas, int mapaColunas, const vector<Caravana *> &caravanas,
                               const vector<Item *> &itens, const Mapa &mapa);
    virtual void mover(char direcao, int mapaLinhas, int mapaColunas, const Mapa &mapa);         // Mover a caravana

    bool estaEmCidade() const;  //cidade
    void definirEmCidade(bool estado);

    void reduzirTripulacao(int quantidade);  // Reduzir tripulantes
    void aumentarTripulacao(int quantidade); // Aumentar tripulantes
    void reduzirCarga(int quantidade);       // Reduzir carga
    void aumentarCarga(int quantidade);     // Aumentar carga
    void reduzirAgua(int quantidade);
    void aumentarAgua(int quantidade);

    virtual void gastarAgua();

    void abastecerAgua();

    void destruir();// Destruir caravana

    bool estaSemTripulantes();
    bool deveDesaparecer() const;

    //sets
    void definirPosicao(int linha, int coluna); // Definir nova posição
    void setEstadoAutonoma(bool estado);

    int obterCarga() const;
    int obterCargaMaxima() const;

    //gets
    int obterLinha() const;                  // Obter linha atual
    int obterColuna() const;                 // Obter coluna atual
    int obterTripulacao() const;             // Obter tripulação
    int obterID() const;
    bool obterEstadoAutonoma() const;

    virtual ~Caravana() {}


};



#endif //CARAVANA_H
