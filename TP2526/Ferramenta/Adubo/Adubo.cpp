#include "Adubo.h"
#include "../../Jardim/Jardim.h"
#include <iostream>

Adubo::Adubo() : Ferramenta('a'), quantidade(Settings::Adubo::capacidade) {}

unique_ptr<Ferramenta> Adubo::clone() const { return make_unique<Adubo>(*this); }
string Adubo::getTipo() const { return "Pacote de Adubo"; }

bool Adubo::usar(Jardim& jardim, int l, int c) {
    if (quantidade > 0) {
        jardim.addNutrientes(l, c, Settings::Adubo::dose);
        quantidade -= Settings::Adubo::dose;
        cout << "Adubou " << (char)('A'+l) << (char)('A'+c)
                  << ". Restam " << quantidade << "unidades de adubo." << endl;

        if (quantidade <= 0) {
            cout << "O pacote de adubo acabou e voou com o vento para o quintal do vizinho" << endl;
            return true;
        }
    }
    return false;
}