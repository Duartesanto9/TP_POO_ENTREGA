#include "Roseira.h"
#include "../../Jardim/Jardim.h"

Roseira::Roseira() : Planta('r') {
    agua = Settings::Roseira::inicial_agua;
    nutrientes = Settings::Roseira::inicial_nutrientes;
}

unique_ptr<Planta> Roseira::clone() const { return make_unique<Roseira>(*this); }
string Roseira::getTipo() const { return "Roseira"; }

Beleza Roseira::getBeleza() const { return Beleza::BONITA; }

void Roseira::agir(Jardim& jardim, int l, int c) {
    if (!viva) return;
    idade++;

    agua -= Settings::Roseira::perda_agua;
    nutrientes -= Settings::Roseira::perda_nutrientes;

    if (jardim.getAgua(l, c) > 0) {
        int absA = Settings::Roseira::absorcao_agua;
        if (jardim.getAgua(l, c) < absA) absA = jardim.getAgua(l, c);
        jardim.addAgua(l, c, -absA);
        agua += absA;
    }
    if (jardim.getNutrientes(l, c) > 0) {
        int absN = Settings::Roseira::absorcao_nutrientes;
        if (jardim.getNutrientes(l, c) < absN) absN = jardim.getNutrientes(l, c);
        jardim.addNutrientes(l, c, -absN);
        nutrientes += absN;
    }

    //verifica vizinhos/morte
    bool vizinhancaCheia = true;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if (i==0 && j==0) continue;
            int vL = l + i, vC = c + j;
            if (jardim.validaPosicao(vL, vC)) {
                if (jardim.getPlanta(vL, vC) == nullptr) {
                    vizinhancaCheia = false;
                }
            }
        }
    }

    if (agua < Settings::Roseira::morre_agua_menor || nutrientes < Settings::Roseira::morre_nutrientes_menor ||
        nutrientes > Settings::Roseira::morre_nutrientes_maior || vizinhancaCheia) {
        viva = false;
        // morrer deixa metade do que tem
        jardim.addNutrientes(l, c, nutrientes / 2);
        jardim.addAgua(l, c, agua / 2);
        return;
    }

    //multipica
    if (nutrientes > Settings::Roseira::multiplica_nutrientes_maior) {
        // tenta reproduzir para 4 vizinhos
        int dL[] = {-1, 1, 0, 0};
        int dC[] = {0, 0, -1, 1};

        for(int i=0; i<4; i++) {
            int nL = l + dL[i];
            int nC = c + dC[i];

            // nasce em solo vazio
            if (jardim.validaPosicao(nL, nC) && jardim.getPlanta(nL, nC) == nullptr) {
                auto nova = make_unique<Roseira>();

                // Configuração da filha
                nova->agua = this->agua / 2;

                // configuraçao apos multiplicaçao
                this->nutrientes = Settings::Roseira::original_nutrientes;
                this->agua = this->agua / 2;

                jardim.adicionarPlanta(nL, nC, std::move(nova));
                break;
            }
        }
    }
}