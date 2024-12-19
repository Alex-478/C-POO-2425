#include "CaravanaComercio.h"

CaravanaComercio::CaravanaComercio(int id, int linha, int coluna)
    : Caravana(id, "Comercio", linha, coluna) {}

void CaravanaComercio::mostrarEstado() const {
    cout << "Caravana de Comercio: ";
    Caravana::mostrarEstado(); // Chama o metodo da classe base
}

void CaravanaComercio::mover(char direcao) {
    // Caravana de comércio pode se mover até 2 posições em um turno
    Caravana::mover(direcao);
    cout << "Caravana de Comercio moveu-se com foco no transporte." << endl;
}