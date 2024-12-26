#include "Caravana.h"
#include <iostream>
int Caravana::nID = 0;
Caravana::Caravana(const string& tipo, int linha, int coluna)
    : id(++nID), tipo(tipo), linha(linha), coluna(coluna), tripulacao(20), carga(0), agua(100), isAutonoma(true), semTripulantes(false) ,instantesRestantes(5) {}

string Caravana::mostrarEstado() const {
    ostringstream descricao;
    descricao << "ID da Caravana: " << id
            << ", Tipo: " << tipo
            << ", Tripulantes: " << tripulacao
            << ", Carga: " << carga
            << ", Agua: " << agua
            << ", Posicao: (" << linha << ", " << coluna << ")" << endl;
    return descricao.str(); // Retorna a descrição da caravana
}

void Caravana::moverAutonomo(int mapaLinhas, int mapaColunas, const vector<Caravana*>& caravanas, const vector<Item>& itens, const Mapa &mapa) {
    if (isAutonoma) {
        int direcao = rand() % 4;
        switch (direcao) {
            case 0: // Cima
                mover('C', mapaLinhas, mapaColunas, mapa);
            break;
            case 1: // Baixo
                mover('B', mapaLinhas, mapaColunas, mapa);
            break;
            case 2: // Esquerda
                mover('E', mapaLinhas, mapaColunas, mapa);
            break;
            case 3: // Direita
                mover('D', mapaLinhas, mapaColunas, mapa);
            break;
            default:
                break;
        }
    }
}
void Caravana::mover(char direcao, int mapaLinhas, int mapaColunas, const Mapa& mapa) {
    // Coordenadas temporárias para o destino
    int novaLinha = linha;
    int novaColuna = coluna;

    // Determina as coordenadas do destino com base na direção
    switch (direcao) {
        case 'C': // Cima
            novaLinha = (linha - 1 + mapaLinhas) % mapaLinhas;
        break;
        case 'B': // Baixo
            novaLinha = (linha + 1) % mapaLinhas;
        break;
        case 'E': // Esquerda
            novaColuna = (coluna - 1 + mapaColunas) % mapaColunas;
        break;
        case 'D': // Direita
            novaColuna = (coluna + 1) % mapaColunas;
        break;
        default:
            cout << "Direcao invalida!" << endl;
        return;
    }

    // Verifica se a célula de destino é uma montanha
    if (mapa.obterCelula(novaLinha, novaColuna) == '+') {
        cout << "Caravana " << id << " não pode mover para uma montanha!" << endl;
        return;
    }

    // Atualiza as coordenadas se o destino for válido
    linha = novaLinha;
    coluna = novaColuna;
    //Debug
    cout << "Caravana " << id << " moveu para " << direcao
         << " na posicao (" << linha << ", " << coluna << ")" << endl;
}

//Set posiçao
void Caravana::definirPosicao(int novaLinha, int novaColuna) {
    this->linha = novaLinha;
    this->coluna = novaColuna;
}
void Caravana::setEstadoAutonoma(bool estado) {
    //cout <<"TESTE: "<< (estado ?"True": "False") << endl;
    isAutonoma = estado;
}

//gets
bool Caravana::obterEstadoAutonoma() const {return isAutonoma;}
int Caravana::obterLinha() const { return linha; }
int Caravana::obterColuna() const { return coluna; }
int Caravana::obterTripulacao() const { return tripulacao; }
void Caravana::destruir() {
    tripulacao = 0;
    carga = 0;
    agua = 0;
    cout << "Caravana destruída!" << endl;
}


bool Caravana::estaSemTripulantes() {
    if(tripulacao > 0) semTripulantes = false;
    if(tripulacao <= 0) semTripulantes = true;
    return semTripulantes;
}

bool Caravana::deveDesaparecer() const {
    return instantesRestantes <= 0;
}

void Caravana::reduzirTripulacao(int quantidade) {
    tripulacao -= quantidade;
    if (tripulacao < 0) tripulacao = 0;
}

void Caravana::aumentarTripulacao(int quantidade) {
    tripulacao += quantidade;
    if(tripulacao >= 40) tripulacao = 40;
}

void Caravana::reduzirCarga(int quantidade) {
    carga -= quantidade;
    if (carga < 0) carga = 0;
}
void Caravana::aumentarCarga(int quantidade) {
    carga += quantidade;
    if(carga >= 40) carga = 40;
}
void Caravana::reduzirAgua(int quantidade) {
    agua -= quantidade;
    if (agua < 0) agua = 0;
}
void Caravana::aumentarAgua(int quantidade) {
    agua += quantidade;
}
void Caravana::gastarAgua() {
    agua--;
    cout << "Caravana " << id << " gastou 1 unidade de água." << endl;
    if (agua < 0) agua = 0;

}

int Caravana::obterID() const { return id;}

char Caravana::obterRepresentacao() const {
    return id + '0'; // Por padrão, retorna o ID
}

void Caravana::afetadaPorTempestade() {
    // Exemplo: Reduz a tripulação ou destrói a caravana
    if (rand() % 2 == 0 && carga > 20 ) {
        // 50% de chance de destruição se a carga for maior que 20(metade)
        destruir();
        cout << "Caravana " << id << " foi destruída pela tempestade!" << endl;
    }
    if(rand() % 4 == 0 && carga > 10) {
        // 25% de chance de destruição se a carga for maior que 10
        destruir();
        cout << "Caravana " << id << " foi destruída pela tempestade!" << endl;
    } else {
        int perdaTripulacao = tripulacao / 4; // Perde 25% da tripulação
        reduzirTripulacao(perdaTripulacao);
        cout << "Caravana " << id << " perdeu " << perdaTripulacao << " tripulantes na tempestade!" << endl;
    }
}

void Caravana::atualizarEstadoSemTripulantes(int linhas, int colunas, const vector<Caravana*>& caravanas, const vector<Item>& itens, const Mapa &mapa) {
    if (semTripulantes) {
        moverAutonomo(linhas, colunas, caravanas, itens, mapa);
        instantesRestantes--;
        if (instantesRestantes <= 0) {
            std::cout << "Caravana " << tipo << " na posição (" << linha
                      << ", " << coluna << ") desapareceu." << std::endl;
        }
    }
}
