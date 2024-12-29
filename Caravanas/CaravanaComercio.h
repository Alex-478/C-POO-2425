#ifndef CARAVANACOMERCIO_H
#define CARAVANACOMERCIO_H
#include "Caravana.h"


#include <iostream>

class CaravanaComercio : public Caravana {
public:
    CaravanaComercio(int linha, int coluna);

    string mostrarEstado() const override; // Substitui mostrarEstado
    void mover(char direcao, int mapaLinhas, int mapaColunas, const Mapa &mapa) override;   // Substitui mover
    void moverAutonomo(int mapaLinhas, int mapaColunas, const vector<Caravana *> &caravanas, const vector<Item *> &itens, const Mapa &mapa) override;

    void afetadaPorTempestade() override;


    void gastarAgua() override;
};



#endif //CARAVANACOMERCIO_H
