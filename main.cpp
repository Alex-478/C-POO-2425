#include <iostream>
#include "Simulador/Simulador.h"

int main()
{
    // Inicializa o simulador com as dimensões do mapa
    int linhas = 10, colunas = 20;  // Dimensões do mapa (podem ser ajustadas conforme necessário)
    Simulador simulador(linhas, colunas);

    // Carrega a configuração e os dados do mapa a partir de um ficheiro especificado
    simulador.carregarConfiguracao("../Utils/config.txt");  // Certifique-se de que o caminho está correto

    // Executa o ciclo principal do simulador
    simulador.executar();

    return 0;
}
