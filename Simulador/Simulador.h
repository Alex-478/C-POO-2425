#ifndef SIMULADOR_H
#define SIMULADOR_H
#include "../Mapa/Mapa.h"
#include "../Caravanas/Caravana.h"
#include "../Caravanas/CaravanaComercio.h"
#include "../Caravanas/CaravanaMilitar.h"
#include "../Caravanas/CaravanaSecreta.h"
#include "../Itens/Item.h"
#include "../Buffer/Buffer.h"
#include "../Cidade/Cidade.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Simulador {
    Mapa mapa;                              // Mapa do deserto
    vector<Caravana*> caravanas;            // Lista de caravanas
    vector<Item> itens;                     // Lista de itens no mapa
    vector<Cidade*> cidades;                // Lista de cidades no mapa
    int moedas;                             // Moedas do jogador
    int instantes;                          // Contador de instantes da simulação
    //int auxInstantes;
    int linhas, colunas;                    // Dimensões do mapa e do buffer
    Buffer buffer2;                         // Buffer 2D para o estado do ecrã

    // Variáveis do ficheiro
    int moedasIniciais;                     // Moedas iniciais
    int instantesEntreNovosItens;
    int duracaoItem;
    int maxItens;
    int precoVendaMercadoria;
    int precoCompraMercadoria;
    int precoCaravana;
    int instantesEntreNovosBarbaros;
    int duracaoBarbaros;


public:
    Simulador(int linhas, int colunas);
    ~Simulador();
    void carregarConfiguracao(const string& nomeArquivo);

    void criarObjetosInciais();

    void carregarDeArquivo(const string &nomeArquivo);

    void executar();

    void execInstantes(int auxInstantes);

    void lerComandos(const std::string &comando);

    void gerarItens();

    void verificarItensExpirados();

    void verificarCaravanasExpiradas();

    void moverCaravanaAutonomo();

    void aplicarEfeitosItem(Caravana& caravana);
    bool adjacente(int l1, int c1, int l2, int c2) const;
    void moverCaravana(int idCaravana, const char direcao);
    void criarTempestadeAreia(int linha, int coluna, int raio);

    string obterDescricaoCaravana(int idCaravana) const;

    void atualizarMapa();                 // Atualiza o buffer com o estado atual
};



#endif //SIMULADOR_H
