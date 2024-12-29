#include "Item.h"
Item::Item(int linha, int coluna, int duracao)
    : linha(linha), coluna(coluna), tipo(TipoItem::CaixaPandora), duracao(duracao) {
    tipo = gerarTipoAleatorio();
}

void Item::reduzirDuracao() {
    if (duracao > 0) {
        --duracao;
    }
}

bool Item::expirado() const { return duracao <= 0;}
TipoItem Item::obterTipo() const { return tipo;} // Retorna diretamente o tipo do item
int Item::obterLinha() const { return linha;}
int Item::obterColuna() const { return coluna;}

void Item::afetadoPorTempestade() {
    // Exemplo: O item desaparece durante a tempestade
    duracao = 0; // Define a duração como 0 para expirar imediatamente
    cout << "Item na posição (" << linha << ", " << coluna << ") foi perdido na tempestade!" << endl;
}
// Metodo para gerar um tipo aleatório
TipoItem Item::gerarTipoAleatorio() {
    int numeroAleatorio = rand() % 5; // Gera número entre 0 e 4
    return static_cast<TipoItem>(numeroAleatorio); // Converte para TipoItem
}