#ifndef CARAVANASECRETA_H
#define CARAVANASECRETA_H
#include "Caravana.h"
#include <iostream>

using namespace std;

class CaravanaSecreta : public Caravana {
public:
    CaravanaSecreta(int linha, int coluna);

    string mostrarEstado() const override; // Substitui mostrarEstado
    void mover(char direcao, int mapaLinhas, int mapaColunas, const Mapa &mapa) override;   // Substitui mover
};



#endif //CARAVANASECRETA_H
