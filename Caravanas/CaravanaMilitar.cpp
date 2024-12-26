#include "CaravanaMilitar.h"

CaravanaMilitar::CaravanaMilitar(int linha, int coluna)
    : Caravana("Militar", linha, coluna) {
    tripulacao = 0;
}

string CaravanaMilitar::mostrarEstado() const {
    ostringstream descricao;
    descricao << "Caravana Militar: ";
    descricao << Caravana::mostrarEstado(); // Chama o metodo da classe base
    return descricao.str(); // Retorna a descrição da caravana
}

void CaravanaMilitar::mover(char direcao, int mapaLinhas, int mapaColunas, const Mapa &mapa) {
    Caravana::mover(direcao, mapaLinhas,  mapaColunas, mapa); // Movimento básico da caravana
    //cout << "Caravana Militar moveu-se estrategicamente." << endl;
}

char CaravanaMilitar::obterRepresentacao() const {
    return '!'; // Retorna '!' para caravanas bárbaras
}

void CaravanaMilitar::afetadaPorTempestade() {
    // Sempre perde 10% da tripulação
    int perdaTripulacao = tripulacao / 10; // Perde 10% da tripulação
    reduzirTripulacao(perdaTripulacao);
    cout << "Caravana Militar " << id << " perdeu " << perdaTripulacao << " tripulantes na tempestade!" << endl;

    // 33% de chance de ser destruída
    if (rand() % 3 == 0) {
        destruir();
        cout << "Caravana Militar " << id << " foi destruída pela tempestade!" << endl;
    }
}

void CaravanaMilitar::aumentarCarga(int quantidade) {
    carga += quantidade;
    if(carga >= 5) carga = 5;
}

void CaravanaMilitar::aumentarAgua(int quantidade) {
    agua += quantidade;
    if(agua >= 400) agua = 400;
}

void CaravanaMilitar::gastarAgua() {
    if(tripulacao >= 20 ) {
        agua -= 3;
    }
    if(tripulacao <20) {
        agua--;
    }
    if(agua < 0) agua = 0;
}