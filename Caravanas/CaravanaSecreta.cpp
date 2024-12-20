#include "CaravanaSecreta.h"

CaravanaSecreta::CaravanaSecreta(int linha, int coluna)
    : Caravana("Secreta", linha, coluna) {}

void CaravanaSecreta::mostrarEstado() const {
    cout << "Caravana Secreta: ";
    Caravana::mostrarEstado(); // Chama o metodo da classe base
    cout << "A caravana possui caracteristicas desconhecidas." << endl;
}

void CaravanaSecreta::mover(char direcao) {
    // Implementação de movimento especial da Caravana Secreta
    Caravana::mover(direcao);
    cout << "Caravana Secreta moveu-se de maneira furtiva." << endl;
}