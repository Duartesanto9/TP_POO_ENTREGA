//
// Created by duart on 30/10/2025.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "../Simulador/Simulador.h"
#include <string>

class UserInterface {
private:
    Simulador &simulador;

public:
    UserInterface(Simulador &s);
    void executa();
};

#endif // USERINTERFACE_H
