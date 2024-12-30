#include <iostream>
#include <string>
#include "Simulador/Simulador.h"
using namespace std;

int main()
{
    string nomeArquivo;
    string escolha;
    cout << "Deseja usar o arquivo padrao (config.txt)? (s/n): ";
    cin >> escolha;

    if (escolha == "s" || escolha == "S") {
         nomeArquivo = "../Utils/config.txt"; // Caminho padrão do arquivo
    } else {
        cout << "Digite o nome do ficheiro de configuração: ";
        cin >> nomeArquivo;
    }

    // Inicializa o simulador
    Simulador simulador(5, 10); // Exemplo de dimensões iniciais do mapa

    // Carrega a configuração do arquivo especificado
    simulador.carregarConfiguracao(nomeArquivo);

    // Executa o ciclo principal do simulador
    simulador.executar();

    return 0;
}


