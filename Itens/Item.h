#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;
enum class TipoItem { CaixaPandora, ArcaTesouro, Jaula, Mina, Surpresa }; // Enum para os tipos de item

class Item {
    int linha, coluna;      // Posição no mapa
    TipoItem tipo;          // Tipo do item
    int duracao;            // Duração do item no mapa

public:
    Item(int linha, int coluna, TipoItem tipo, int duracao); // Construtor
    void reduzirDuracao();                // Reduz a duração do item
    bool expirado() const;                // Verifica se o item expirou
    //gets
    TipoItem obterTipo() const;           // Retorna o tipo do item
    int obterLinha() const;               // Retorna a linha
    int obterColuna() const;              // Retorna a coluna
    void afetadoPorTempestade();
};



#endif //ITEM_H
