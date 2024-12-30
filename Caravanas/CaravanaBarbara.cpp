#include "CaravanaBarbara.h"


CaravanaBarbara::CaravanaBarbara(int linha, int coluna)
        : Caravana("Barbara", linha, coluna) {
    maxAgua = 200;
    maxCarga = 40;
    tripulacao = 40;
    isBarbara = true;
    isAutonoma = true;
}
void CaravanaBarbara::afetadaPorTempestade() {
    int perdaTripulacao = tripulacao / 10; // Perde 10% da tripulação
    reduzirTripulacao(perdaTripulacao);
    if(rand() % 4 == 0) {
        // 25% de chance de destruição se a carga for maior que 10
        destruir();
        cout << "Caravana Barbara " << id << " foi destruída pela tempestade!" << endl;
    }
}

string CaravanaBarbara::mostrarEstado() const {
    ostringstream descricao;
    descricao << "Caravana Barbara: ";
    descricao << Caravana::mostrarEstado(); // Chama o metodo da classe base
    return descricao.str(); // Retorna a descrição da caravana
}

char CaravanaBarbara::obterRepresentacao() const {
    return '!'; // Por padrão, retorna o ID
}