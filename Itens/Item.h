#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
enum class TipoItem { CaixaPandora, ArcaTesouro, Jaula, Mina, Surpresa }; // Enum para os tipos de item

class Item {
    int linha, coluna;      // Posição no mapa
    TipoItem tipo;          // Tipo do item
    int duracao;            // Duração do item no mapa
    bool descartavel;       // Indica se o item pode ser descartado
public:
    //Item(int linha, int coluna, TipoItem tipo, int duracao); // Construtor
    Item(int linha, int coluna, int duracao);

    void reduzirDuracao();                // Reduz a duração do item
    bool expirado() const;                // Verifica se o item expirou
    //gets
    TipoItem obterTipo() const;           // Retorna o tipo do item
    string tipoItemParaString() const;

    int obterLinha() const;               // Retorna a linha
    int obterColuna() const;              // Retorna a coluna
    void afetadoPorTempestade();

    TipoItem gerarTipoAleatorio();

    bool estadoDescartavel() const;

    void setDescartavel(bool descartavel);

    string mostrarEstado() const;

    //void aplicarEfeito(Caravana &caravana);
};



#endif //ITEM_H
