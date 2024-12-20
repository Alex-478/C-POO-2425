#ifndef SIMULADOR_H
#define SIMULADOR_H
#include "../Mapa/Mapa.h"
#include "../Caravanas/Caravana.h"
#include "../Itens/Item.h"
#include "../Buffer/Buffer.h"
#include "../Cidade/Cidade.h"
#include <vector>
#include <string>
using namespace std;

class Simulador {
    Mapa mapa;                              // Mapa do deserto
    vector<Caravana*> caravanas;            // Lista de caravanas
    vector<Item> itens;                     // Lista de itens no mapa
    vector<Cidade*> cidades;
    int moedas;                             // Moedas do jogador
    int instantes;                          // Contador de instantes da simulação
    char** buffer;                          // Buffer 2D para o estado do ecrã
    int linhas, colunas;                    // Dimensões do mapa e do buffer
    Buffer buffer2;

public:
    Simulador(int linhas, int colunas);
    ~Simulador();
    void carregarConfiguracao(const string& nomeArquivo);

    void criarObjetosInciais();

    void carregarDeArquivo(const string &nomeArquivo);

    void executar();
    void gerarItens();
    void aplicarEfeitosItem(Caravana& caravana);
    bool adjacente(int l1, int c1, int l2, int c2) const;
    void moverCaravana(int idCaravana, const string& direcao);
    void criarTempestadeAreia(int linha, int coluna, int raio);

    void inicializarBuffer();

    void limparBuffer();                    // Limpa o buffer
    void atualizarMapa();                 // Atualiza o buffer com o estado atual
};



#endif //SIMULADOR_H
