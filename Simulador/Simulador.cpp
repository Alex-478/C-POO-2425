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
    srand(time(nullptr)); // Semente para aleatoriedade
}

Simulador::~Simulador() {
    // Liberta memória das caravanas
    for (Caravana* caravana : caravanas) {
        delete caravana;
    }
    for(Cidade* cidade : cidades){
        delete cidade;
    }
}

void Simulador::atualizarMapa() {
    mapa.atualizarCaravanas(caravanas);
    mapa.atualizarItens(itens);

    /*
    for (const Caravana* caravana : caravanas) {
        //buffer[caravana->obterLinha()][caravana->obterColuna()] = 'C';
        mapa.definirCelula(caravana->obterLinha(),caravana->obterColuna(),'C');
    }

    // Adiciona itens ao buffer
    for (const Item& item : itens) {
        //buffer[item.obterLinha()][item.obterColuna()] = '*';
        mapa.definirCelula(item.obterLinha(),item.obterColuna(),'*');
    }
    */


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

//3-Executar
void Simulador::executar() {
    string comando;
    while (true) {
        // Inicialização correta
        //atualizarBuffer();
        atualizarMapa();

        //limparBuffer();
        buffer2.limpar();
        buffer2.atualizarBuffer(mapa);
        buffer2.mostrar();


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
        cout << "Debug: Item gerado na posição (" << linha << ", " << coluna << ")" << endl;
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


//1-Inciar Config
void Simulador::carregarConfiguracao(const string& nomeFicheiro) {
    cout << "Carregar configuração do Ficheiro: " << nomeFicheiro << endl;
    //mapa.carregarDeArquivo(nomeFicheiro);
    carregarDeArquivo(nomeFicheiro);
    //Incializa Buffer
    buffer2 = Buffer(linhas, colunas);

    // Exemplo de criação inicial de caravanas
    caravanas.push_back(new CaravanaComercio(0, 0));
    caravanas.push_back(new CaravanaMilitar(1, 1));
    caravanas.push_back(new CaravanaSecreta( 2, 2));
}
//2-Le ficheiro
void Simulador::carregarDeArquivo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo do mapa: " << nomeArquivo << endl;
        return;
    }

    arquivo >> linhas >> colunas;
    cout << "linhas: " << linhas << endl;
    cout << "colunas: " << colunas << endl;

    // Inicializa o mapa com as dimensões lidas - User new com ponteiro ???
    mapa = Mapa(linhas, colunas);
    char caracter;
    // Carrega os dados do arquivo para a grelha
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            arquivo >> caracter;
            mapa.definirCelula(i, j, caracter);


            if (caracter >= '0' && caracter <= '9') {
                // Cria uma caravana comercial
                caravanas.push_back(new CaravanaComercio( linhas, colunas));
                cout << "Caravana Comercial criada na posicao (" << linhas << ", " << colunas << ")\n";
            } else if (caracter == '!') {
                // Cria uma caravana bárbara
                caravanas.push_back(new CaravanaMilitar( linhas, colunas));
                cout << "Caravana Barbara criada na posicao (" << linhas << ", " << colunas << ")\n";
            } else if (caracter >= 'a' && caracter <= 'z') {
                // Cria uma cidade
                cidades.push_back(new Cidade(caracter, linhas, colunas));
                cout << "Cidade criada na posicao (" << linhas << ", " << colunas << ")\n";
            } else if (caracter == '*') {
                // Cria um item
                //itens.push_back(new Item(r, c, ItemType::Surpresa, 20));
                cout << "Item criado na posicao (" << linhas << ", " << colunas << ")\n";
            }

        }
    }

    //Lê os parâmetros configuráveis do ficheiro
    string parametro;
    while (arquivo >> parametro) {
        if (parametro == "moedas") {
            arquivo >> moedasIniciais;
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
