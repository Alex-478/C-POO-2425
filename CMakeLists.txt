cmake_minimum_required(VERSION 3.29)
project(TPv2)

set(CMAKE_CXX_STANDARD 20)

add_executable(TPv2 main.cpp
        Buffer/Buffer.cpp
        Buffer/Buffer.h
        Caravanas/Caravana.cpp
        Caravanas/Caravana.h
        Caravanas/CaravanaMilitar.cpp
        Caravanas/CaravanaMilitar.h
        Caravanas/CaravanaComercio.cpp
        Caravanas/CaravanaComercio.h
        Caravanas/CaravanaSecreta.cpp
        Caravanas/CaravanaSecreta.h
        Mapa/Mapa.cpp
        Mapa/Mapa.h
        Itens/Item.cpp
        Itens/Item.h
        Simulador/Simulador.cpp
        Simulador/Simulador.h
        Cidade/Cidade.cpp
        Cidade/Cidade.h
        Caravanas/CaravanaBarbara.cpp
        Caravanas/CaravanaBarbara.h
)
