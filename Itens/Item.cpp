#include "Item.h"
Item::Item(int linha, int coluna, int duracao)
    : linha(linha), coluna(coluna), tipo(TipoItem::CaixaPandora), duracao(duracao), descartavel(false) {
    tipo = gerarTipoAleatorio();
}

void Item::reduzirDuracao() {
    if (duracao > 0) {
        --duracao;
    }
}

bool Item::expirado() const { return duracao <= 0;}
TipoItem Item::obterTipo() const { return tipo;} // Retorna diretamente o tipo do
string Item::tipoItemParaString() const {
    switch (tipo) {
        case TipoItem::CaixaPandora:
            return "Caixa de Pandora";
        case TipoItem::ArcaTesouro:
            return "Arca de Tesouro";
        case TipoItem::Jaula:
            return "Jaula";
        case TipoItem::Mina:
            return "Mina";
        case TipoItem::Surpresa:
            return "Surpresa";
        default:
            return "Desconhecido";
    }
}
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

bool Item::estadoDescartavel() const {
    return descartavel;
}
void Item::setDescartavel(bool descartavel) {
    this->descartavel = descartavel;
}


string Item::mostrarEstado() const {
    ostringstream estado;
    estado << "Item do tipo " << tipoItemParaString()
           << " na posicao (" << linha << ", " << coluna << ")" << endl;
    return estado.str();
}
