//
// Created by duart on 30/10/2025.
//

#include "UserInterface.h"
#include <iostream>
using namespace std;

UserInterface::UserInterface(Simulador &s) : simulador(s) {}

void UserInterface::executa() {
    string comando;
    while(simulador.naoTermina()) {
        cout << ">> ";
        getline(cin, comando);
        simulador.fazOpe(comando);
    }
}
