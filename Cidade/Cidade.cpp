#include "Cidade.h"
Cidade::Cidade(char id, int linha, int coluna)
    : id(id), linha(linha), coluna(coluna) {}

// Métodos de acesso
char Cidade::obterID() const { return id;}

int Cidade::obterLinha() const { return linha;}

int Cidade::obterColuna() const { return coluna;}

// Adiciona uma caravana à cidade
void Cidade::adicionarCaravana(Caravana* caravana) {
    caravanas.push_back(caravana);
}

// Remove uma caravana da cidade
void Cidade::removerCaravana(Caravana* caravana) {
    caravanas.erase(
        //remove(caravanas.begin(), caravanas.end(), caravana),
        caravanas.end()
    );
}

// Retorna a lista de caravanas na cidade
const vector<Caravana*>& Cidade::obterCaravanas() const {
    return caravanas;
}

// Exibe as informações da cidade
string Cidade::exibirConteudo() const {
    ostringstream descricao;
    descricao << "Cidade " << id << " na posicao (" << linha << ", " << coluna << "):\n";
    if (caravanas.empty()) {
        descricao << "  Sem caravanas presentes.\n";
    } else {
        descricao << "  Caravanas presentes:\n";
        for (const auto* caravana : caravanas) {
            descricao << "    - ID: " << caravana->obterID() << "\n";
        }
    }
    return descricao.str();
}

void Cidade::interagirComCaravana(Caravana& caravana) {
    std::cout << "Bem-vindo à cidade " << id << "!" << std::endl;
    // Exemplo: interagir com recursos ou realizar comércio
}