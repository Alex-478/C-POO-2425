#ifndef SIMULADOR_H
#define SIMULADOR_H
#include "../Mapa/Mapa.h"
#include "../Caravanas/Caravana.h"
#include "../Caravanas/CaravanaComercio.h"
#include "../Caravanas/CaravanaMilitar.h"
#include "../Caravanas/CaravanaSecreta.h"
#include "../Caravanas/CaravanaBarbara.h"
#include "../Itens/Item.h"
#include "../Buffer/Buffer.h"
#include "../Cidade/Cidade.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
using namespace std;

class Simulador {
    Mapa mapa;                              // Mapa do deserto
    vector<Caravana*> caravanas;            // Lista de caravanas
    vector<Item*> itens;                     // Lista de itens no mapa
    vector<Cidade*> cidades;                // Lista de cidades no mapa
    int moedas;                             // Moedas do jogador
    int instantes;                          // Contador de instantes da simulação
    //int auxInstantes;
    int linhas, colunas;                    // Dimensões do mapa e do buffer
    Buffer buffer;                         // Buffer 2D para o estado do ecrã
    map <string, Buffer> estadosBuffer;
    int combatesGanhos;                     // Contador de combates ganhos
    bool terminar;

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

    void verificarItensAdjacentes();

    void aplicarEfeito(Caravana &caravana, Item &item);

    void execInstantes(int auxInstantes);

    void lerComandos(const std::string &comando);

    void saves(const string &nome);

    void loads(const std::string &nome) const;

    void list() const;

    void del(const std::string &nome);

    void gerarItens();

    void verificarItensExpirados();

    void verificarCaravanasExpiradas();

    void moverCaravanaAutonomo();

    void aplicarEfeitosItem(Caravana& caravana);
    bool adjacente(int l1, int c1, int l2, int c2) const;
    void moverCaravana(int idCaravana, const char direcao);
    void criarTempestadeAreia(int linha, int coluna, int raio);

    string obterDescricaoCaravana(int idCaravana) const;

    void stop(int id);

    void autoGestao(int id);

    string precos() const;

    void alterarMoedas(int quantidade);

    void logs();

    void terminarSimulador();

    void processarCombate(Caravana *caravana1, Caravana *caravana2);

    void criaBarbaro(int linha, int coluna);

    void adicionarCaravanaCidade(Caravana *caravana);

    string obterDescricaoCidade(int idCidade) const;

    void compraMercadoria(int id, int quantidade);

    void venda(int id);

    void compraCaravana(int idCidade, char tipo);

    void compraTripulacao(int id, int quantidade);

    void verificarInteracaoCidade(Caravana &caravana);

    void atualizarMapa();                 // Atualiza o buffer com o estado atual
};



#endif //SIMULADOR_H
