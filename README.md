# Caravan Simulator in C++

Este projeto é um simulador de caravanas desenvolvido como trabalho prático para a disciplina de Programação Orientada a Objetos (POO) em 2024/2025. O simulador modela interações entre diferentes tipos de caravanas, itens e um mapa dinâmico.

## Funcionalidades

- **Múltiplos tipos de caravanas**: Comercial, Militar, Secreta e Bárbara, cada uma com comportamentos únicos.
- **Mapa dinâmico**: Representação de um ambiente com cidades, montanhas e áreas transitáveis.
- **Interação com itens**: Diversos itens com efeitos distintos que afetam as caravanas.
- **Sistema de combate**: Simulação de combates entre caravanas com base no número de tripulantes.
- **Eventos dinâmicos**: Tempestades e outros eventos que alteram o estado do mapa e das caravanas.
- **Interface de controle**: Comandos de usuário para mover caravanas, salvar e carregar estados do jogo.
- **Sistema de buffer**: Armazenamento do estado visual do simulador para análise futura.

## Comandos de Utilizador

- **`M [id] [N|S|E|W]`**: Move a caravana com o ID especificado na direção indicada (Norte, Sul, Este ou Oeste).
- **`I [id]`**: Exibe informações detalhadas sobre a caravana com o ID especificado.
- **`S [nome]`**: Salva o estado atual do simulador com o nome fornecido.
- **`C [nome]`**: Carrega um estado previamente salvo com o nome fornecido.
- **`A [id]`**: Alterna o modo de movimento da caravana (autónomo/manual) com o ID especificado.
- **`T`**: Avança para o próximo turno da simulação.
- **`H`**: Exibe este menu de ajuda com os comandos disponíveis.
- **`F`**: Finaliza a simulação e encerra o programa.

## Estrutura do Projeto

- `src/`: Contém o código fonte do simulador.
  - `Simulador/`: Classes relacionadas à lógica principal do simulador.
  - `Caravanas/`: Implementações das diferentes caravanas.
  - `Itens/`: Definições dos itens e seus efeitos.
  - `Mapa/`: Lógica de representação e manipulação do mapa.
  - `Buffer/`: Sistema de buffer para visualização do estado do jogo.
  - `main.cpp`: Ponto de entrada do programa.
- `include/`: Contém os arquivos de cabeçalho (.h).
- `docs/`: Documentação do projeto (relatório, manual, etc.).

## Dependências

- Compilador C++ (C++11 ou superior)
- Biblioteca padrão C++
## Autor
- Alexandre Moreira
