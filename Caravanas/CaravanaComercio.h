#ifndef CARAVANACOMERCIO_H
#define CARAVANACOMERCIO_H
#include "Caravana.h"
#include <iostream>

class CaravanaComercio : public Caravana {
public:
    CaravanaComercio(int linha, int coluna);


    void mostrarEstado() const override; // Substitui mostrarEstado
    void mover(char direcao) override;   // Substitui mover
};



#endif //CARAVANACOMERCIO_H
