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

/*
void Mapa::carregarDeArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo do mapa: " << nomeArquivo << endl;
        return;
    }

    arquivo >> linhas >> colunas;
    cout << "linhas: " << linhas << endl;
    cout << "colunas: " << colunas << endl;

    // Aloca memória para a grelha
    tabela = new char*[linhas];
    for (int i = 0; i < linhas; ++i) {
        tabela[i] = new char[colunas];
        memset(tabela[i], '.', colunas);  // Inicializa com valor padrão '.'
    }

    // Carrega os dados do arquivo para a grelha
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            arquivo >> tabela[i][j];
        }
    }

    //Lê os parâmetros configuráveis do ficheiro
    string parametro;
    while (arquivo >> parametro) {
        if (parametro == "moedas") {
            arquivo >> moedas;
        } else if (parametro == "instantes_entre_novos_itens") {
            arquivo >> instantesEntreNovosItens;
        } else if (parametro == "duração_item") {
            arquivo >> duracaoItem;
        } else if (parametro == "max_itens") {
            arquivo >> maxItens;
        } else if (parametro == "preço_venda_mercadoria") {
            arquivo >> precoVendaMercadoria;
        } else if (parametro == "preço_compra_mercadoria") {
            arquivo >> precoCompraMercadoria;
        } else if (parametro == "preço_caravana") {
            arquivo >> precoCaravana;
        } else if (parametro == "instantes_entre_novos_barbaros") {
            arquivo >> instantesEntreNovosBarbaros;
        } else if (parametro == "duração_barbaros") {
            arquivo >> duracaoBarbaros;
        }
    }

    arquivo.close();
}*/

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

void Mapa::atualizarCaravanas(const vector<Caravana*>& caravanas) {
    for (const Caravana* caravana : caravanas) {
            char aux = caravana->obterRepresentacao();
            definirCelula(caravana->obterLinha(), caravana->obterColuna(), aux);
    }
}

void Mapa::atualizarItens(const vector<Item>& itens) {
    for (const Item& item : itens) {
        definirCelula(item.obterLinha(), item.obterColuna(), '*');
    }
}
