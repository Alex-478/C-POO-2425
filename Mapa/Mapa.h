#ifndef MAPA_H
#define MAPA_H

#include <fstream>
#include <iostream>
#include <cstring> // Para memset
#include <string>
#include <vector>

using namespace std;

class Mapa {
    int linhas, colunas;  // Dimensões do mapa
    char** tabela;        // tabela 2D que armazena o mapa

public:
    Mapa();
    Mapa(int l, int c);

    explicit Mapa(nullptr_t null);
    // Construtur copia
    Mapa(const Mapa& other);
    // Operador de atribuição
    Mapa& operator=(const Mapa& other);


    ~Mapa();  // Destrutor para liberar a memória alocada
    void limpar();

    void exibir() const;  // Mostra o mapa no ecrã
    void definirCelula(int linha, int coluna, char valor);  // Define o valor de uma célula
    //gets
    int obterLinhas() const;  // Retorna o número de linhas
    int obterColunas() const; // Retorna o número de colunas
    char obterCelula(int linha, int coluna) const; // Retorna o valor de uma célula

    void criarTempestadeAreia(int linha, int coluna, int raio);

};



#endif //Mapa
