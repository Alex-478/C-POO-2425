#include "Caravana.h"
#include <iostream>
int Caravana::nID = 0;
Caravana::Caravana(const string& tipo, int linha, int coluna)
    : id(++nID), tipo(tipo), linha(linha), coluna(coluna), tripulacao(20), carga(0), agua(100) {}

void Caravana::mostrarEstado() const {
    cout << "ID da Caravana: " << id
    << ", Tipo: " << tipo
    << ", Tripulantes: " << tripulacao
    << ", Carga: " << carga
    << ", Agua: " << agua
    << ", Posicao: (" << linha << ", " << coluna << ")"
    << endl;
}

void Caravana::mover(char direcao) {
    if (direcao == 'D') { linha++; }
    else if (direcao == 'B') { linha--; }
    else if (direcao == 'C') { coluna++; }
    else if (direcao == 'E') { coluna--; }
    cout << "Caravana " << id << " moveu para " << direcao
    << " na posicao (" << linha << ", " << coluna << ")" << endl;
}

void Caravana::definirPosicao(int novaLinha, int novaColuna) {
    this->linha = novaLinha;
    this->coluna = novaColuna;
}

int Caravana::obterLinha() const { return linha; }
int Caravana::obterColuna() const { return coluna; }
int Caravana::obterTripulacao() const { return tripulacao; }
void Caravana::destruir() {
    tripulacao = 0;
    carga = 0;
    agua = 0;
    cout << "Caravana destruída!" << endl;
}

void Caravana::reduzirTripulacao(int quantidade) {
    tripulacao -= quantidade;
    if (tripulacao < 0) tripulacao = 0;
}

void Caravana::aumentarTripulacao(int quantidade) { tripulacao += quantidade; }

int Caravana::obterID() const { return id;}

char Caravana::obterRepresentacao() const {
    return id + '0'; // Por padrão, retorna o ID
}
