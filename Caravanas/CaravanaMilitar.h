#ifndef CARAVANAMILITAR_H
#define CARAVANAMILITAR_H
#include "Caravana.h"
#include <iostream>


class CaravanaMilitar : public Caravana{
public:
    CaravanaMilitar(int linha, int coluna);

    string mostrarEstado() const override; // Substitui mostrarEstado
    void mover(char direcao, int mapaLinhas, int mapaColunas, const Mapa &mapa) override;   // Substitui mover

    char obterRepresentacao() const override;

    void afetadaPorTempestade() override;

    void gastarAgua() override;
};



#endif //CARAVANAMILITAR_H
