#ifndef CARAVANABARBARA_H
#define CARAVANABARBARA_H
#include "Caravana.h"
#include <iostream>
using namespace std;

class CaravanaBarbara final : public Caravana {
public:
    CaravanaBarbara(int linha, int coluna);

    void afetadaPorTempestade();
    string mostrarEstado() const override;

    char obterRepresentacao() const override;
};



#endif //CARAVANABARBARA_H
