#include "TessouraPoda.h"
#include "../../Jardim/Jardim.h"
#include "../../Planta/Planta.h"
#include <iostream>

TessouraPoda::TessouraPoda() : Ferramenta('t') {}

unique_ptr<Ferramenta> TessouraPoda::clone() const { return make_unique<TessouraPoda>(*this); }
string TessouraPoda::getTipo() const { return "Tesoura de Poda"; }

bool TessouraPoda::usar(Jardim& jardim, int l, int c) {
    Planta* p = jardim.getPlanta(l, c);
    if (p != nullptr) {
        if (p->getBeleza() == Beleza::FEIA) {
            jardim.removerPlanta(l, c);
            cout << "Planta feia cortada com sucesso!" << endl;
        } else {
            cout << "Esta planta nao e feia (e "
                      << (p->getBeleza() == Beleza::BONITA ? "Bonita" : "Neutra")
                      << ") ou seja nao da para cortar." << endl;
        }
    } else {
        cout << "Ferramenta nao utilizada pois nao tem planta." << endl;
    }
    return false;
}