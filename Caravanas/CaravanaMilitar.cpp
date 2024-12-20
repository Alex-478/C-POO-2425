#include "CaravanaMilitar.h"

CaravanaMilitar::CaravanaMilitar(int linha, int coluna)
    : Caravana("Militar", linha, coluna) {}

void CaravanaMilitar::mostrarEstado() const {
    cout << "Caravana Militar: ";
    Caravana::mostrarEstado(); // Chama o metodo da classe base
}

void CaravanaMilitar::mover(char direcao) {
    Caravana::mover(direcao); // Movimento básico da caravana
    cout << "Caravana Militar moveu-se estrategicamente." << endl;
}

char CaravanaMilitar::obterRepresentacao() const {
    return '!'; // Retorna '!' para caravanas bárbaras
}