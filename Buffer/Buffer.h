//
// Created by alexa on 17/12/2024.
//

#ifndef BUFFER_H
#define BUFFER_H
#include <iostream>
#include <memory>
#include <vector>
#include "../Caravanas/Caravana.h"
#include "../Mapa/mapa.h"

using namespace std;  // Adiciona caravanas ao buffer


class Buffer {
    int linhas, colunas;
    unique_ptr<char[]> buffer;

public:
    Buffer(int rows, int cols);
    void limpar();

    void atualizarBuffer(const Mapa& mapa);

   // void atualizarMapa(const vector<vector<char>> &mapGrid, Mapa mapa);
    void atualizarCaravanas(const vector<Caravana*>& caravans);
    void mostrar() const;
};



#endif //BUFFER_H
