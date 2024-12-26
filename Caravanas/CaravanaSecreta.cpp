#include "CaravanaSecreta.h"

CaravanaSecreta::CaravanaSecreta(int linha, int coluna)
    : Caravana("Secreta", linha, coluna) {}

string CaravanaSecreta::mostrarEstado() const {
    ostringstream descricao;
    descricao << "Caravana Secreta: ";
    descricao << Caravana::mostrarEstado(); // Chama o metodo da classe base
    descricao << "A caravana possui caracteristicas desconhecidas." << endl;
    return descricao.str(); // Retorna a descrição da caravana
}

void CaravanaSecreta::mover(char direcao, int mapaLinhas, int mapaColunas, const Mapa &mapa) {
    // Implementação de movimento especial da Caravana Secreta
    Caravana::mover(direcao, mapaLinhas, mapaColunas, mapa);
    cout << "Caravana Secreta moveu-se de maneira furtiva." << endl;
}