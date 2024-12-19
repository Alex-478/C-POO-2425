#include "CaravanaMilitar.h"

CaravanaMilitar::CaravanaMilitar(int id, int linha, int coluna)
    : Caravana(id, "Militar", linha, coluna) {}

void CaravanaMilitar::mostrarEstado() const {
    cout << "Caravana Militar: ";
    Caravana::mostrarEstado(); // Chama o metodo da classe base
}

void CaravanaMilitar::mover(char direcao) {
    Caravana::mover(direcao); // Movimento básico da caravana
    cout << "Caravana Militar moveu-se estrategicamente." << endl;
}