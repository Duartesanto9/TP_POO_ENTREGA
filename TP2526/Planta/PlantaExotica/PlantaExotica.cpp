#include "PlantaExotica.h"
#include "../../Jardim/Jardim.h"
#include <iostream>

PlantaExotica::PlantaExotica() : Planta('x'), contadorRelogio(0) {
    agua = 50;
    nutrientes = 50;
    viva = true;
}

unique_ptr<Planta> PlantaExotica::clone() const {
    return make_unique<PlantaExotica>(*this);
}

string PlantaExotica::getTipo() const {
    return "Planta Carnivora (Exotica)";
}

Beleza PlantaExotica::getBeleza() const {
    return Beleza::BONITA;
}

void PlantaExotica::agir(Jardim& jardim, int l, int c) {
    agua -= 1;
    nutrientes -= 1;

    if (agua <= 0 || nutrientes <= 0) {
        viva = false;
        return;
    }


    contadorRelogio++;

    if (contadorRelogio >= 5) {
        cout << "A Planta Exotica em " << (char)('A' + l) << (char)('A' + c) << " roubou a vizinhanca!" << endl;

        contadorRelogio = 0;

        // quadrado 3x3 à volta ignorando o centro
        for (int i = l - 1; i <= l + 1; ++i) {
            for (int j = c - 1; j <= c + 1; ++j) {
                if (i == l && j == c) continue;

                if (jardim.validaPosicao(i, j)) {
                    Planta* vizinha = jardim.getPlanta(i, j);

                    if (vizinha != nullptr && vizinha->estaViva()) {

                        int rouboAgua = vizinha->getAgua() / 2;
                        int rouboNutrientes = vizinha->getNutrientes() / 2;

                        this->agua += rouboAgua;
                        this->nutrientes += rouboNutrientes;

                        vizinha->drenar(rouboAgua, rouboNutrientes);
                    }
                }
            }
        }
    }
}