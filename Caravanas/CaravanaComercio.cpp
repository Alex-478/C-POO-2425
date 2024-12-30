#include "CaravanaComercio.h"

CaravanaComercio::CaravanaComercio(int linha, int coluna)
    : Caravana("Comercio", linha, coluna) {
    maxTripulacao = 40;
    tripulacao = 20;
    maxAgua = 200;
    maxCarga = 40;
}

string CaravanaComercio::mostrarEstado() const {
        ostringstream descricao;
        descricao << "Caravana de Comercio: ";
        descricao << Caravana::mostrarEstado(); // Chama o metodo da classe base
        return descricao.str(); // Retorna a descrição da caravana
}

void CaravanaComercio::mover(char direcao, int mapaLinhas, int mapaColunas, const Mapa &mapa) {
    // Caravana de comércio pode se mover até 2 posições em um turno
    // aleatorio??

    Caravana::mover(direcao, mapaLinhas, mapaColunas, mapa);
    //cout << "Caravana de Comercio moveu-se com foco no transporte." << endl;
}

void CaravanaComercio::moverAutonomo(int mapaLinhas, int mapaColunas, const vector<Caravana *> &caravanas, const vector<Item *> &itens, const Mapa &mapa) {
     int destinoRow = -1, destinoCol = -1;

    // 1. Verificar itens próximos
    for (const Item* item : itens) {
        int itemRow = item->obterLinha();
        int itemCol = item->obterColuna();

        // Verifica se o item está dentro da distância de 2 células
        if (std::abs(itemRow - linha) <= 2 && std::abs(itemCol - coluna) <= 2) {
            destinoRow = itemRow;
            destinoCol = itemCol;
            break; // Prioridade para o item mais próximo
        }
    }

    // 2. Se não houver itens próximos, tenta ficar ao lado de outra caravana do utilizador
    if (destinoRow == -1 && destinoCol == -1) {
        for (const Caravana* outraCaravana : caravanas) {
            if (outraCaravana == this) continue; // Ignora a si mesma

            int outraRow = outraCaravana->obterLinha();
            int outraCol = outraCaravana->obterColuna();

            // Verifica se está a mais de 1 célula de distância
            if (abs(outraRow - linha) > 1 || abs(outraCol - coluna) > 1) {
                destinoRow = outraRow;
                destinoCol = outraCol;
                break;
            }
        }
    }

    // 3. Se encontrou um destino, move-se em direção a ele
    if (destinoRow != -1 && destinoCol != -1) {
        if (linha < destinoRow) mover('B', mapaLinhas, mapaColunas, mapa);//linha ++
        else if (linha > destinoRow) mover('C', mapaLinhas, mapaColunas, mapa);//linha--

        if (coluna < destinoCol) mover( 'D', mapaLinhas, mapaColunas, mapa); //coluna--
        else if (coluna > destinoCol) mover( 'E', mapaLinhas, mapaColunas, mapa); //coluna++
        ostringstream logs;
        logs << "Caravana de Comercio moveu-se para (" << linha << ", " << coluna << ")\n";
        logDetalhado(logs.str());
    } else {
        Caravana::moverAutonomo(mapaLinhas, mapaColunas, caravanas, itens, mapa);
    }

}

void CaravanaComercio::afetadaPorTempestade() {
    // Exemplo: Reduz a tripulação ou destrói a caravana
    if (rand() % 2 == 0 && carga > 20 ) {
        // 50% de chance de destruição se a carga for maior que 20(metade)
        destruir();
        cout << "Caravana " << id << " foi destruida pela tempestade!" << endl;
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


void CaravanaComercio::gastarAgua() {
    if(tripulacao >= 20 ) {
        agua -= 2;
    }
    if(tripulacao <20 && tripulacao != 0) {
        agua--;
    }
    if(agua < 0) agua = 0;
}