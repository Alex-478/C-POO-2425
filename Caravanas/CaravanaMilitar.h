#ifndef CARAVANAMILITAR_H
#define CARAVANAMILITAR_H
#include "Caravana.h"
#include <iostream>


class CaravanaMilitar : public Caravana{
public:
    CaravanaMilitar(int linha, int coluna);
    void mostrarEstado() const override; // Substitui mostrarEstado
    void mover(char direcao) override;   // Substitui mover
    char obterRepresentacao() const override;
};



#endif //CARAVANAMILITAR_H
