#include "Mapa.h"
#include <iostream>

Mapa::Mapa() : linhas(0), colunas(0), tabela(nullptr) {}

Mapa::~Mapa() {
    // Liberta a memória alocada para o mapa
    if (tabela) {
        for (int i = 0; i < linhas; ++i) {
            delete[] tabela[i];
        }
        delete[] tabela;
    }
}

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
}

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

