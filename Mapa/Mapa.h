#ifndef MAPA_H
#define MAPA_H
#include <fstream>
#include <iostream>
#include <cstring> // Para memset
#include <string>
#include <vector>
#include "../Caravanas/Caravana.h"
#include "../Caravanas/CaravanaComercio.h"
#include "../Caravanas/CaravanaMilitar.h"
#include "../Caravanas/CaravanaSecreta.h"
#include "../Itens/Item.h"

using namespace std;

class Mapa {
    int linhas, colunas;  // Dimensões do mapa
    char** tabela;        // tabela 2D que armazena o mapa



public:
    Mapa();
    Mapa(int l, int c);

    explicit Mapa(nullptr_t null);
    // Copy constructor
    Mapa(const Mapa& other);
    // Assignment operator
    Mapa& operator=(const Mapa& other);


    ~Mapa();  // Destrutor para liberar a memória alocada
    void limpar();
    //void carregarDeArquivo(const std::string& nomeArquivo); // Carrega o mapa de um ficheiro
    void exibir() const;  // Mostra o mapa no ecrã
    void definirCelula(int linha, int coluna, char valor);  // Define o valor de uma célula
    //gets
    int obterLinhas() const;  // Retorna o número de linhas
    int obterColunas() const; // Retorna o número de colunas
    char obterCelula(int linha, int coluna) const; // Retorna o valor de uma célula

    void atualizarCaravanas(const vector<Caravana *> &caravanas);
    void atualizarItens(const vector<Item> &itens);

};



#endif //Mapa
