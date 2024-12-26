#include "Simulador.h"
//#include "../Caravanas/CaravanaComercio.h"
//#include "../Caravanas/CaravanaMilitar.h"
//#include "../Caravanas/CaravanaSecreta.h"
#include <iostream>
#include <cstdlib>
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

        for (const Caravana* caravana : caravanas) {
            char aux = caravana->obterRepresentacao();
            mapa.definirCelula(caravana->obterLinha(), caravana->obterColuna(), aux);
        }

        for (const Item& item : itens) {
            mapa.definirCelula(item.obterLinha(), item.obterColuna(), '*');
        }


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

void Simulador::gerarItens() {
    if (itens.size() >= 5) return;

    int linha = rand() % linhas;
    int coluna = rand() % colunas;

    if (mapa.obterCelula(linha, coluna) == '.') {
        itens.emplace_back(linha, coluna, TipoItem::ArcaTesouro, 20);
        mapa.definirCelula(linha, coluna, '*');
        cout << "Debug: Item gerado na posição (" << linha << ", " << coluna << ")" << endl;
    }
}
void Simulador::verificarItensExpirados() {
    for (auto it = itens.begin(); it != itens.end(); ) {
        if (it->expirado()) { // Verifica se o item expirou
            cout << "Item na posição (" << it->obterLinha() << ", " << it->obterColuna()
                 << ") expirou e será removido." << endl;
            // Remove o item do mapa (se necessário)
            mapa.definirCelula(it->obterLinha(), it->obterColuna(), '.');
            // Remove o item do vetor
            it = itens.erase(it);
        } else {
            ++it; // Avança para o próximo item
        }
    }
}
void Simulador::verificarCaravanasExpiradas() {
    for (auto it = caravanas.begin(); it != caravanas.end(); ) {
        Caravana* caravana = *it;

        if (caravana->estaSemTripulantes()) {
            caravana->atualizarEstadoSemTripulantes(linhas, colunas,caravanas, itens, mapa);

            if (caravana->deveDesaparecer()) {
                // Remove a caravana do vetor
                cout << "Removendo caravana sem tripulantes." << std::endl;
                it = caravanas.erase(it);
                delete caravana; // Libera a memória da caravana removida
            } else {
                ++it; // Avança para o próximo elemento
                }
        } else {
            ++it; // Avança para o próximo elemento
        }
    }
}

void Simulador::moverCaravanaAutonomo() {
    for (Caravana* caravana : caravanas) {
        if (!caravana->obterEstadoAutonoma()) {
            continue;
        }

        int linhaAtual = caravana->obterLinha();
        int colunaAtual = caravana->obterColuna();
        mapa.definirCelula(linhaAtual, colunaAtual, '.');
        caravana->moverAutonomo(linhas, colunas, caravanas, itens, mapa);
    }
}

void Simulador::moverCaravana(int idCaravana, const char direcao) {
    //Caravana* caravana = caravanas[idCaravana - 1];
    for (Caravana* caravana : caravanas) {
        if (caravana->obterID() == idCaravana) {
            caravana->setEstadoAutonoma(false);
            int linhaAtual = caravana->obterLinha();
            int colunaAtual = caravana->obterColuna();
            mapa.definirCelula(linhaAtual, colunaAtual, '.');
            caravana->mover(direcao, linhas , colunas, mapa);
        }
    }
}

bool Simulador::adjacente(int l1, int c1, int l2, int c2) const {
    return (abs(l1 - l2) <= 1 && abs(c1 - c2) <= 1);
}

void Simulador::criarTempestadeAreia(int linha, int coluna, int raio) {
    // 1. Marca as células dentro do raio como parte da tempestade
    for (int i = linha - raio; i <= linha + raio; ++i) {
        for (int j = coluna - raio; j <= coluna + raio; ++j) {
            int linhaAjustada = (i + mapa.obterLinhas()) % mapa.obterLinhas(); // Considera mapa esférico
            int colunaAjustada = (j + mapa.obterColunas()) % mapa.obterColunas(); // Considera mapa esférico

            // Representa a tempestade no mapa, ignorando montanhas
            if (mapa.obterCelula(linhaAjustada, colunaAjustada) != '+') {
                mapa.definirCelula(linhaAjustada, colunaAjustada, 'S');
            }

            // 2. Afeta caravanas na área da tempestade
            for (Caravana* caravana : caravanas) {
                if (caravana->obterLinha() == linhaAjustada && caravana->obterColuna() == colunaAjustada) {
                    caravana->afetadaPorTempestade(); // Metodo para aplicar os efeitos na caravana
                }
            }

            // 3. Afeta itens na área da tempestade
            for (Item& item : itens) {
                if (item.obterLinha() == linhaAjustada && item.obterColuna() == colunaAjustada) {
                    item.afetadoPorTempestade(); // Metodo para aplicar os efeitos nos itens
                }
            }
        }
    }
    execInstantes(1);

    // 5. Remove a tempestade do mapa
    for (int i = linha - raio; i <= linha + raio; ++i) {
        for (int j = coluna - raio; j <= coluna + raio; ++j) {
            int linhaAjustada = (i + mapa.obterLinhas()) % mapa.obterLinhas();
            int colunaAjustada = (j + mapa.obterColunas()) % mapa.obterColunas();

            // Restaura células ao estado original, ignorando montanhas e caravanas
            if (mapa.obterCelula(linhaAjustada, colunaAjustada) == 'S') {
                mapa.definirCelula(linhaAjustada, colunaAjustada, '.');
            }
        }
    }

    cout << "A tempestade desapareceu!" << endl;
}

string Simulador::obterDescricaoCaravana(int idCaravana) const {
    // Percorre todas as caravanas
    for (const Caravana* caravana : caravanas) {
        if (caravana->obterID() == idCaravana) { // Verifica se o ID corresponde
            return caravana->mostrarEstado(); // Retorna a descrição da caravana
        }
    }
    // Caso não encontre a caravana com o ID especificado
    return "Caravana com ID " + to_string(idCaravana) + " não encontrada.";
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
                caravanas.push_back(new CaravanaComercio( i, j));
                cout << "Caravana Comercial criada na posicao (" << i << ", " << j << ")\n";
            } else if (caracter == '!') {
                // Cria uma caravana bárbara
                caravanas.push_back(new CaravanaMilitar( i, j));
                cout << "Caravana Barbara criada na posicao (" << i << ", " << j << ")\n";
            } else if (caracter >= 'a' && caracter <= 'z') {
                // Cria uma cidade
                cidades.push_back(new Cidade(caracter, i, j));
                cout << "Cidade criada na posicao (" << i << ", " << j << ")\n";
            } else if (caracter == '*') {
                // Cria um item
                //itens.push_back(new Item(r, c, ItemType::Surpresa, 20));
                cout << "Item criado na posicao (" << i << ", " << j << ")\n";
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
//3-Executar
void Simulador::executar() {
    atualizarMapa();
    buffer2.atualizarBuffer(mapa);
    buffer2.mostrar();

    // Exibe estado das caravanas
    for (const Caravana* caravana : caravanas) {
        cout << caravana->mostrarEstado();
    }

    while (true) {
        //execInstantes(1);
        string comando;
        cout << "Digite um comando: ";
        getline(cin, comando);
        lerComandos(comando);
    }
}
//4-Executar Instantes
void Simulador::execInstantes(int auxInstantes) {

    string comando;
    for (int i = 0; i < auxInstantes; ++i) {
        // Inicialização correta
        //atualizarBuffer();
        atualizarMapa();

        //limparBuffer();
        buffer2.limpar();
        buffer2.atualizarBuffer(mapa);
        buffer2.mostrar();

        // Exibe estado das caravanas
        for (const Caravana* caravana : caravanas) {
            cout << caravana->mostrarEstado();
        }
        cout << "Moedas: " << moedas << " | Instantes: " << instantes << endl;

        ////////////////////////////////

        //Verificações dos objetos em cada instante
        //Reduzir uma duração dos itens
        for (Item item : itens) {
            item.reduzirDuracao();
        }
        verificarItensExpirados();

        //Move em estado autonoma
        moverCaravanaAutonomo();
        //Caravanas todas para autonomas
        for (Caravana* caravana : caravanas) {
            caravana->setEstadoAutonoma(true);
            caravana->gastarAgua(); // gastar agua conforme cada tipo de caravana
        }
        verificarCaravanasExpiradas();

        ++instantes;
    }

}
//5-Ler Comandos
void Simulador::lerComandos(const string& comando) {
    std::istringstream ss(comando);
    std::string cmd;
    ss >> cmd;

    if (cmd == "config") {
        std::string filename;
        ss >> filename;
        carregarConfiguracao(filename);
    } else if (cmd == "exec") {
        std::string filename;
        ss >> filename;
        executar();
    } else if (cmd == "prox") {
        int n = 1;  // default value
        ss >> n;
        execInstantes(n);
    } else if (cmd == "comprac") {
        char cidade;
        char tipo;
        ss >> cidade >> tipo;
        //comprac(cidade, tipo);
    } else if (cmd == "precos") {
        //precos();
    } else if (cmd == "cidade") {
        char nome;
        ss >> nome;
        //cidade(nome);
    } else if (cmd == "caravana") {
        int id;
        if (ss >> id) {
            try {
                obterDescricaoCaravana(id);
            } catch (const out_of_range& e) {
                cout << "Caravana " << id << " não encontrada." << endl;
            }
        } else {
            cout << "Uso correto: caravana <id>" << endl;
        }
    } else if (cmd == "compra") {
        int id, quantidade;
        ss >> id >> quantidade;
        //compra(id, quantidade);
    } else if (cmd == "vende") {
        int id;
        ss >> id;
        //vende(id);
    } else if (cmd == "move") {
        int idCaravana;
        char direcao;
        ss >> idCaravana >> direcao;
        //int idCaravana = stoi(comando.substr(5, 1));
        //char direcao = comando.substr(7);
        moverCaravana(idCaravana, direcao);
    } else if (cmd == "auto") {
        int id;
        ss >> id;
        //autoGestao(id);
    } else if (cmd == "stop") {
        int id;
        ss >> id;
        //stop(id);
    } else if (cmd == "barbaro") {
        int x, y;
        ss >> x >> y;
        //barbaro(x, y);
    } else if (cmd == "tempestade") {
        int x, y, raio;
        ss >> x >> y >> raio;
        criarTempestadeAreia(x, y, raio);
        //areia(x, y, raio);
    } else if (cmd == "moedas") {
        int quantidade;
        ss >> quantidade;
        //adicionarMoedas(quantidade);
    } else if (cmd == "tripul") {
        int id, quantidade;
        ss >> id >> quantidade;
        //tripul(id, quantidade);
    } else if (cmd == "saves") {
        std::string nome;
        ss >> nome;
        //saves(nome);
    } else if (cmd == "loads") {
        std::string nome;
        ss >> nome;
        //loads(nome);
    } else if (cmd == "lists") {
        //lists();
    } else if (cmd == "dels") {
        std::string nome;
        ss >> nome;
        //dels(nome);
    } else if (cmd == "terminar") {
        //terminar();
    } else {
        std::cout << "Comando desconhecido: " << cmd << std::endl;
    }

    //if (comando == "gerar_itens") {gerarItens();}
}
