#include "ErvaDaninha.h"
#include "../../Jardim/Jardim.h"

ErvaDaninha::ErvaDaninha() : Planta('e'), instantesSemMultiplicar(0) {
    agua = Settings::ErvaDaninha::inicial_agua;
    nutrientes = Settings::ErvaDaninha::inicial_nutrientes;
}

unique_ptr<Planta> ErvaDaninha::clone() const { return make_unique<ErvaDaninha>(*this); }
string ErvaDaninha::getTipo() const { return "Erva Daninha"; }

Beleza ErvaDaninha::getBeleza() const { return Beleza::FEIA; }

void ErvaDaninha::agir(Jardim& jardim, int l, int c) {
    if (!viva) return;
    idade++;
    instantesSemMultiplicar++;


    if (jardim.getAgua(l, c) > 0) {
        jardim.addAgua(l, c, -Settings::ErvaDaninha::absorcao_agua);
        agua += Settings::ErvaDaninha::absorcao_agua;
    }
    if (jardim.getNutrientes(l, c) > 0) {
        jardim.addNutrientes(l, c, -Settings::ErvaDaninha::absorcao_nutrientes);
        nutrientes += Settings::ErvaDaninha::absorcao_nutrientes;
    }


    if (idade >= Settings::ErvaDaninha::morre_instantes) {
        viva = false;
        return;
    }

    // multiplicacao
    if (nutrientes > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
        instantesSemMultiplicar >= Settings::ErvaDaninha::multiplica_instantes) {

        int dL[] = {-1, 1, 0, 0};
        int dC[] = {0, 0, -1, 1};

        for(int i=0; i<4; i++) {
            int nL = l + dL[i];
            int nC = c + dC[i];

            if (jardim.validaPosicao(nL, nC)) {
                // tem planta vizinha mata
                if (jardim.getPlanta(nL, nC) != nullptr) {
                    jardim.removerPlanta(nL, nC);
                }

                // cria erva
                auto nova = make_unique<ErvaDaninha>();

                jardim.adicionarPlanta(nL, nC, std::move(nova));
                instantesSemMultiplicar = 0;
                break;
            }
        }
    }
}