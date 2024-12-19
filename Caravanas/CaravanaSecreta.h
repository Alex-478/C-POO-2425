#ifndef CARAVANASECRETA_H
#define CARAVANASECRETA_H
#include "Caravana.h"
#include <iostream>

using namespace std;

class CaravanaSecreta : public Caravana {
public:
    CaravanaSecreta(int id, int linha, int coluna);
    void mostrarEstado() const override; // Substitui mostrarEstado
    void mover(char direcao) override;   // Substitui mover
};



#endif //CARAVANASECRETA_H
