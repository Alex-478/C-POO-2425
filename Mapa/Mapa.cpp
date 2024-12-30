#include "Mapa.h"
#include <iostream>

Mapa::Mapa() : linhas(0), colunas(0), tabela(nullptr) {}
Mapa::Mapa(int l, int c) : linhas(l), colunas(c){
    tabela = new char*[linhas];
    for (int i = 0; i < linhas; ++i) {
        tabela[i] = new char[colunas];
        memset(tabela[i], '.', colunas);  // Inicializa com valor padrão '.'
    }
}

// Construstor copia
Mapa::Mapa(const Mapa& other) : linhas(other.linhas), colunas(other.colunas) {
    tabela = new char*[linhas];
    for (int i = 0; i < linhas; ++i) {
        tabela[i] = new char[colunas];
        memcpy(tabela[i], other.tabela[i], colunas);
    }
}

Mapa & Mapa::operator=(const Mapa &other) {
    if (this != &other) {
        // Deleta os dados antigos
        for (int i = 0; i < linhas; ++i) {
            delete[] tabela[i];
        }
        delete[] tabela;

        // Copia os novos dados
        linhas = other.linhas;
        colunas = other.colunas;
        tabela = new char*[linhas];
        for (int i = 0; i < linhas; ++i) {
            tabela[i] = new char[colunas];
            memcpy(tabela[i], other.tabela[i], colunas);
        }
    }
    return *this;
}

Mapa::~Mapa() {
    // Liberta a memória alocada para o mapa
    if (tabela) {
        for (int i = 0; i < linhas; ++i) {
            delete[] tabela[i];
        }
        delete[] tabela;
    }
}

void Mapa::limpar() {
    for (int r = 0; r < linhas; ++r) {
        for (int c = 0; c < colunas; ++c) {
            tabela[r][c] = '.';  // Define cada célula como 'vazia'
        }
    }
}


void Mapa::exibir() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cout << tabela[i][j] << ' ';
        }
        cout << endl;
    }
}

char Mapa::obterCelula(int linha, int coluna) const {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        return tabela[linha][coluna];
    }
    return '.'; // Valor padrão para posições fora dos limites
}

void Mapa::definirCelula(int linha, int coluna, char valor) {
    if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) {
        tabela[linha][coluna] = valor;
    }
}

int Mapa::obterLinhas() const { return linhas;}
int Mapa::obterColunas() const { return colunas;}

void Mapa::criarTempestadeAreia(int linha, int coluna, int raio) {
    int auxColuna;
    int auxLinha;
    for (int i = linha - raio; i <= linha + raio; ++i) {
        for (int j = coluna - raio; j <= coluna + raio; ++j) {
            if (i >= 0 && i < linhas && j >= 0 && j < colunas) {
                auxLinha = (i + linhas) % linhas; // Considera mapa esférico
                auxColuna = (j + colunas) % colunas; // Considera mapa esférico
            }
        }
    }
    // Representa a tempestade no mapa, ignorando montanhas
    if (obterCelula(auxLinha, auxColuna) != '+') {
        definirCelula(auxLinha, auxColuna, 'T');
    }


}
