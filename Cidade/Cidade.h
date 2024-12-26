#ifndef CIDADE_H
#define CIDADE_H
#include <string>
#include <vector>
#include "../Caravanas/Caravana.h"
using namespace std;

class Cidade {
    char id; // Identificador único da cidade (ex: 'a', 'b', etc.)
    int linha, coluna; // Posição da cidade no mapa
    vector<Caravana*> caravanas; // Caravanas presentes na cidade

public:
    Cidade(char id, int linha, int coluna);

    // Métodos de acesso
    char obterID() const;
    int obterLinha() const;
    int obterColuna() const;

    // Manipulação de caravanas
    void adicionarCaravana(Caravana* caravana);
    void removerCaravana(Caravana* caravana);
    const vector<Caravana*>& obterCaravanas() const;

    // Exibir informações da cidade
    void exibirConteudo() const;
};



#endif //CIDADE_H
