#include "Simulador.h"
#include "../Caravanas/CaravanaComercio.h"
#include "../Caravanas/CaravanaMilitar.h"
#include "../Caravanas/CaravanaSecreta.h"
#include <iostream>
//#include <cstdlib>
#include <ctime>
#include <cstring> // Para memset

Simulador::Simulador(int l, int c)
    : linhas(l), colunas(c), buffer2(linhas, colunas), moedas(1000), instantes(0) {
    // Aloca memória para o buffer
    buffer = new char *[linhas];
    for (int i = 0; i < linhas; ++i) {
        buffer[i] = new char[colunas];
    }
    limparBuffer();

    srand(time(nullptr)); // Semente para aleatoriedade
}

Simulador::~Simulador() {
    // Liberta memória do buffer
    for (int i = 0; i < linhas; ++i) {
        delete[] buffer[i];
    }
    delete[] buffer;

    // Liberta memória das caravanas
    for (Caravana* caravana : caravanas) {
        delete caravana;
    }
}

void Simulador::limparBuffer() {
    for (int i = 0; i < linhas; ++i) {
        memset(buffer[i], ' ', colunas); // Preenche o buffer com '.'
    }
}

void Simulador::atualizarMapa() {

    for (const Caravana* caravana : caravanas) {
        //buffer[caravana->obterLinha()][caravana->obterColuna()] = 'C';
        mapa.definirCelula(caravana->obterLinha(),caravana->obterColuna(),'C');
    }

    // Adiciona itens ao buffer
    for (const Item& item : itens) {
        //buffer[item.obterLinha()][item.obterColuna()] = '*';
        mapa.definirCelula(item.obterLinha(),item.obterColuna(),'*');
    }


    //limparBuffer();
    // Adiciona o mapa ao buffer
    /*for (int l = 0; l < mapa.obterLinhas(); ++l) {
        for (int c = 0; c < mapa.obterColunas(); ++c) {
            buffer[l][c] = mapa.obterCelula(l, c);
        }
    }*/

    /*
    // Adiciona caravanas ao buffer
    for (const Caravana* caravana : caravanas) {
        buffer[caravana->obterLinha()][caravana->obterColuna()] = 'C';
    }

    // Adiciona itens ao buffer
    for (const Item& item : itens) {
        buffer[item.obterLinha()][item.obterColuna()] = '*';
    }
    */
}

void Simulador::carregarConfiguracao(const string& nomeArquivo) {
    cout << "Carregando configuração do arquivo: " << nomeArquivo << endl;
    mapa.carregarDeArquivo(nomeArquivo);
    inicializarBuffer();
    // Exemplo de criação inicial de caravanas
    caravanas.push_back(new CaravanaComercio(1, 0, 0));
    caravanas.push_back(new CaravanaMilitar(2, 1, 1));
    caravanas.push_back(new CaravanaSecreta(3, 2, 2));
}

void Simulador::executar() {
    string comando;
    while (true) {
        // Inicialização correta
        //atualizarBuffer();
        atualizarMapa();


        limparBuffer();
        buffer2.limpar();
        buffer2.atualizarBuffer(mapa);
        buffer2.mostrar();

        // Exibe o buffer no ecrã
        /*for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                cout << buffer[i][j] << " ";
            }
            cout << endl;
        }*/

        // Exibe estado das caravanas
        for (const Caravana* caravana : caravanas) {
            caravana->mostrarEstado();
        }

        cout << "Moedas: " << moedas << " | Instantes: " << instantes << endl;
        cout << "Digite um comando: ";
        getline(cin, comando);

        if (comando == "sair") {
            cout << "Terminar simulação." << endl;
            break;
        } else if (comando == "gerar_itens") {
            gerarItens();
        } else if (comando.substr(0, 4) == "move") {
            int idCaravana = stoi(comando.substr(5, 1));
            string direcao = comando.substr(7);
            moverCaravana(idCaravana, direcao);
        }

        ++instantes; // Avança o tempo
    }
}

void Simulador::gerarItens() {
    if (itens.size() >= 5) return;

    int linha = rand() % mapa.obterLinhas();
    int coluna = rand() % mapa.obterColunas();

    if (mapa.obterCelula(linha, coluna) == '.') {
        itens.emplace_back(linha, coluna, TipoItem::ArcaTesouro, 20);
        mapa.definirCelula(linha, coluna, '*');
    }
}

void Simulador::moverCaravana(int idCaravana, const string& direcao) {
    Caravana* caravana = caravanas[idCaravana - 1];
    int linhaAtual = caravana->obterLinha();
    int colunaAtual = caravana->obterColuna();

    mapa.definirCelula(linhaAtual, colunaAtual, '.'); // Limpa posição antiga

    caravana->mover(direcao[0]);

    mapa.definirCelula(caravana->obterLinha(), caravana->obterColuna(), 'C'); // Atualiza posição
}

bool Simulador::adjacente(int l1, int c1, int l2, int c2) const {
    return (abs(l1 - l2) <= 1 && abs(c1 - c2) <= 1);
}

void Simulador::criarTempestadeAreia(int linha, int coluna, int raio) {
    for (int i = linha - raio; i <= linha + raio; ++i) {
        for (int j = coluna - raio; j <= coluna + raio; ++j) {
            if (i >= 0 && i < mapa.obterLinhas() && j >= 0 && j < mapa.obterColunas()) {
                mapa.definirCelula(i, j, 'T'); // Representa uma tempestade de areia
            }
        }
    }
}

void Simulador::inicializarBuffer() {
    linhas = mapa.obterLinhas();
    colunas = mapa.obterColunas();
    buffer2 = Buffer(linhas, colunas);
}
