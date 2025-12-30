#include "Regador.h"
#include "../../Jardim/Jardim.h"
#include <iostream>

Regador::Regador() : Ferramenta('g'), capacidade(Settings::Regador::capacidade) {}

unique_ptr<Ferramenta> Regador::clone() const { return make_unique<Regador>(*this); }
string Regador::getTipo() const { return "Regador"; }

bool Regador::usar(Jardim& jardim, int l, int c) {
    if (capacidade > 0) {
        jardim.addAgua(l, c, Settings::Regador::dose);
        capacidade -= Settings::Regador::dose;
        cout << "Regou " << (char)('A'+l) << (char)('A'+c)
                  << ". Restam " << capacidade << "unidades de agua." << endl;

        if (capacidade <= 0) {
            cout << "O regador ficou vazio e o jardineiro atirou-o para longe." << endl;
            return true;
        }
    }
    return false;
}