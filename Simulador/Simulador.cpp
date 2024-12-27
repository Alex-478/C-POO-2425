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
    for (const Caravana *caravana: caravanas) {
        char aux = caravana->obterRepresentacao();
        mapa.definirCelula(caravana->obterLinha(), caravana->obterColuna(), aux);
    }

    for (const Item &item: itens) {
        mapa.definirCelula(item.obterLinha(), item.obterColuna(), '*');
    }

    for (const Cidade *cidade: cidades) {
        mapa.definirCelula(cidade->obterLinha(), cidade->obterColuna(), cidade->obterID());
    }
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
                cout << "Removendo caravana sem tripulantes." << endl;
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
        adicionarCaravanaCidade(caravana);
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
            adicionarCaravanaCidade(caravana);
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

void Simulador::stop(int id) {
    for (Caravana* caravana : caravanas) {
        if(caravana->obterID() == id)
        caravana->setEstadoAutonoma(false);
    }
}
void Simulador::autoGestao(int id) {
    for (Caravana* caravana : caravanas) {
        if(caravana->obterID() == id)
            caravana->setEstadoAutonoma(false);
    }
}

string Simulador::precos() const {
    ostringstream descricao;
    descricao << "Preço Compra caravana: " << precoCaravana << endl;
    descricao << "Preço Compra Mercadoria: " << precoCompraMercadoria << endl;
    descricao << "Preço Venda Mercadoria: " << precoVendaMercadoria << endl;
    return descricao.str();
}

void Simulador::alterarMoedas(int quantidade) {
    moedas += quantidade;
}

//Cidade
void Simulador::adicionarCaravanaCidade(Caravana* caravana) {
    if (caravana->estaEmCidade()) {
        // A caravana já está em uma cidade, não faz nada
        return;
    }
    for (auto& cidade : cidades) {
        // Verifica se as coordenadas da caravana coincidem com as da cidade
        if (caravana->obterLinha() == cidade->obterLinha() &&
            caravana->obterColuna() == cidade->obterColuna()) {
            caravana->definirEmCidade(true);
            caravana->abastecerAgua();
            cidade->adicionarCaravana(caravana);
            cout << "Caravana " << caravana->obterID()
                      << " foi adicionada a cidade " << cidade->obterID() << "." << endl;


            return;
            }
    }
}
string Simulador::obterDescricaoCidade(int idCidade) const {
    // Percorre todas as cidades
    for (const Cidade *cidade: cidades) {
        if (cidade->obterID() == idCidade) { // Verifica se o ID corresponde
            return cidade->exibirConteudo(); // Retorna a descrição da caravana
        }
    }

    // Caso não encontre a caravana com o ID especificado
    return "Cidade com ID " + to_string(idCidade) + " não encontrada.";
}
void Simulador::compraMercadoria(int id, int quantidade) {
        if (quantidade <= 0) {
            std::cout << "Quantidade inválida." << std::endl;
            return;
        }
        for (Caravana* caravana : caravanas) {
            if (caravana->obterID() == id) { // Verifica se o ID corresponde
                if(!caravana->estaEmCidade()) {
                    cout << "Caravana nao esta numa cidade." << endl;
                    return;
                }

                int custo = quantidade * precoCompraMercadoria;

                if (moedas < custo) {
                    cout << "Moedas insuficientes." << endl;
                    return;
                }

                if (caravana->obterCarga() + quantidade > caravana->obterCargaMaxima()) {
                    cout << "Capacidade de carga insuficiente." << endl;
                    return;
                }

                moedas -= custo;
                caravana->aumentarCarga(quantidade);
                cout << "Compra realizada com sucesso." << endl;
                return;
            }
        }
        cout << "Caravana " << id << " não encontrada." << endl;
        return;
}
void Simulador::venda(int id) {
    for (Caravana* caravana : caravanas) {
        if (caravana->obterID() == id) { // Verifica se o ID corresponde
            if(!caravana->estaEmCidade()) {
                cout << "Caravana nao esta numa cidade." << endl;
                return;
            }

            moedas += caravana->obterCarga() * precoVendaMercadoria;
            caravana->reduzirCarga(caravana->obterCarga());

            cout << "Venda realizada com sucesso." << endl;
            return;
        }
    }
    cout << "Caravana " << id << " não encontrada." << endl;
}
void Simulador::compraCaravana(int idCidade, char tipo) {
    if (tipo != 'C' && tipo != 'M' && tipo != 'S') {
        cout << "Tipo de caravana inválido. Use 'C', 'M' ou 'S'." << endl;
        return;
    }
    if (moedas < precoCaravana) {
        cout << "Moedas insuficientes. Necessário: " << precoCaravana
             << ", Disponível: " << moedas << endl;
        return;
    }
    int contagemCaravanas = caravanas.size();

    if(contagemCaravanas >= 10) {
        cout << "Numero de caravanas maximo atingido" << 10 << endl;
        return;
    }

    Caravana* novaCaravana = nullptr; // Ponteiro para a nova caravana criada

    for (auto& cidade : cidades) {
        if (cidade->obterID() == idCidade) {
            if (tipo == 'C')
                novaCaravana = new CaravanaComercio(cidade->obterLinha(), cidade->obterColuna());
            else if (tipo == 'M')
                novaCaravana = new CaravanaMilitar(cidade->obterLinha(), cidade->obterColuna());
            else if (tipo == 'S')
                novaCaravana = new CaravanaSecreta(cidade->obterLinha(), cidade->obterColuna());
        }
    }

    if (novaCaravana) {
        caravanas.push_back(novaCaravana); // Adiciona a caravana ao vetor
        moedas -= precoCaravana;
        cout << "Caravana " << novaCaravana->obterID() << " criada com sucesso em ("
             << novaCaravana->obterLinha() << "," << novaCaravana->obterColuna() << ")" << endl;
    }
}
//////////
void Simulador::verificarInteracaoCidade(Caravana& caravana) {
    for (const auto& cidade : cidades) {
        if (caravana.obterLinha() == cidade->obterLinha() &&
            caravana.obterColuna() == cidade->obterColuna()) {
            cidade->interagirComCaravana(caravana);
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

      /*  // Exibe estado das caravanas
        for (const Caravana* caravana : caravanas) {
            cout << caravana->mostrarEstado();
        }*/
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
            caravana->gastarAgua(); // gastar agua conforme cada tipo de caravana
        }
        verificarCaravanasExpiradas();

        ++instantes;
    }

}
//5-Ler Comandos
void Simulador::lerComandos(const string& comando) {
    istringstream ss(comando);
    string cmd;
    ss >> cmd;

    if (cmd == "config") {
        string filename;
        ss >> filename;
        carregarConfiguracao(filename);
    } else if (cmd == "exec") {
        string filename;
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
        //compra(cidade, tipo);
    } else if (cmd == "precos") {
        cout << precos();
    } else if (cmd == "cidade") {
        char idC;
        ss >> idC;
        cout << obterDescricaoCidade(idC);
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
        compraMercadoria(id, quantidade);
    } else if (cmd == "vende") {
        int id;
        ss >> id;
        venda(id);
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
        autoGestao(id);
    } else if (cmd == "stop") {
        int id;
        ss >> id;
        stop(id);
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
        alterarMoedas(quantidade);
    } else if (cmd == "tripul") {
        int id, quantidade;
        ss >> id >> quantidade;
        //tripul(id, quantidade);
    } else if (cmd == "saves") {
        string nome;
        ss >> nome;
        //saves(nome);
    } else if (cmd == "loads") {
        string nome;
        ss >> nome;
        //loads(nome);
    } else if (cmd == "lists") {
        //lists();
    } else if (cmd == "dels") {
        string nome;
        ss >> nome;
        //dels(nome);
    } else if (cmd == "terminar") {
        //terminar();
    } else {
        cout << "Comando desconhecido: " << cmd << endl;
    }

    //if (comando == "gerar_itens") {gerarItens();}
}
