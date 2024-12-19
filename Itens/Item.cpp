#include "Item.h"
Item::Item(int linha, int coluna, TipoItem tipo, int duracao)
    : linha(linha), coluna(coluna), tipo(tipo), duracao(duracao) {}

void Item::reduzirDuracao() {
    if (duracao > 0) {
        --duracao;
    }
}

bool Item::expirado() const { return duracao <= 0;}
TipoItem Item::obterTipo() const { return tipo;} // Retorna diretamente o tipo do item
int Item::obterLinha() const { return linha;}
int Item::obterColuna() const { return coluna;}