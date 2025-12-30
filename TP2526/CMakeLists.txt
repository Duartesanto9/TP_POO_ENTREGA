cmake_minimum_required(VERSION 3.27)
project(TP2526)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP2526 main.cpp
        Jardim/Jardim.h
        Jardim/Jardim.cpp
        Jardineiro/Jardineiro.h
        Jardineiro/Jardineiro.cpp
        Ferramenta/Ferramenta.h
        Ferramenta/Ferramenta.cpp
        Ferramenta/FerramentaZ/FerramentaZ.cpp
        Ferramenta/FerramentaZ/FerramentaZ.h
        Ferramenta/Adubo/Adubo.cpp
        Ferramenta/Adubo/Adubo.h
        Ferramenta/Regador/Regador.cpp
        Ferramenta/Regador/Regador.h
        Ferramenta/TessouraPoda/TessouraPoda.cpp
        Ferramenta/TessouraPoda/TessouraPoda.h
        Planta/Planta.cpp
        Planta/Planta.h
        Planta/Cacto/Cacto.cpp
        Planta/Cacto/Cacto.h
        Planta/ErvaDaninha/ErvaDaninha.cpp
        Planta/ErvaDaninha/ErvaDaninha.h
        Planta/PlantaExotica/PlantaExotica.cpp
        Planta/PlantaExotica/PlantaExotica.h
        Planta/Roseira/Roseira.cpp
        Planta/Roseira/Roseira.h
        Simulador/Simulador.cpp
        Simulador/Simulador.h
        UserInterface/UserInterface.cpp
        UserInterface/UserInterface.h
)
