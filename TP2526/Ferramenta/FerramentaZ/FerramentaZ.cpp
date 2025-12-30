#include "FerramentaZ.h"
#include "../../Jardim/Jardim.h"
#include <iostream>


FerramentaZ::FerramentaZ() : Ferramenta('z') {}

unique_ptr<Ferramenta> FerramentaZ::clone() const {
    return make_unique<FerramentaZ>(*this);
}

string FerramentaZ::getTipo() const {
    return "Ferramenta>";
}

bool FerramentaZ::usar(Jardim& jardim, int l, int c) {
    cout << "A Ferramenta Z utilizada, adicionou 50A e 50N ao solo num raio de 2." << endl;

    int raio = 2;

    for (int i = l - raio; i <= l + raio; ++i) {
        for (int j = c - raio; j <= c + raio; ++j) {

            if (jardim.validaPosicao(i, j)) {
                jardim.addNutrientes(i, j, 50);
                jardim.addAgua(i, j, 50);
            }
        }
    }

    cout << "Ferramenta de utilizaçao unica, partiu-se apos utilizacao" << endl;

    return true;
}