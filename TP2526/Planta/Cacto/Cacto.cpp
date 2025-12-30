#include "Cacto.h"
#include "../../Jardim/Jardim.h"
#include <iostream>

Cacto::Cacto() : Planta('c') {
    agua = 0;
    nutrientes = 0;
    contadorExcessoA = 0;
    contadorFaltaN = 0;
}

unique_ptr<Planta> Cacto::clone() const { return make_unique<Cacto>(*this); }
string Cacto::getTipo() const { return "Cacto"; }

Beleza Cacto::getBeleza() const { return Beleza::NEUTRA; }

void Cacto::agir(Jardim& jardim, int l, int c) {
    if (!viva) return;
    idade++;

    int absA = jardim.getAgua(l, c) * Settings::Cacto::absorcao_agua_percentagem / 100;
    jardim.addAgua(l, c, -absA);
    agua += absA;


    int absN = Settings::Cacto::absorcao_nutrientes;
    if (jardim.getNutrientes(l,c) < absN) absN = jardim.getNutrientes(l,c);
    jardim.addNutrientes(l, c, -absN);
    nutrientes += absN;
    

    // solo > 100
    if (jardim.getAgua(l, c) > Settings::Cacto::morre_agua_solo_maior) {
        contadorExcessoA++;
    } else {
        contadorExcessoA = 0; 
    }

    //nutriente = 0
    if (jardim.getNutrientes(l, c) < Settings::Cacto::morre_nutrientes_solo_menor) {
        contadorFaltaN++;
    } else {
        contadorFaltaN = 0;
    }

    // 3 instantes seguidos de uma das condiçoes, mata planta
    if (contadorExcessoA >= Settings::Cacto::morre_agua_solo_instantes ||
        contadorFaltaN > Settings::Cacto::morre_nutrientes_solo_instantes) {

        viva = false;
        jardim.addNutrientes(l, c, nutrientes);
        return;
    }

    //multiplica
    if (nutrientes > Settings::Cacto::multiplica_nutrientes_maior &&
        agua > Settings::Cacto::multiplica_agua_maior) {

        int dL[]={-1,1,0,0}, dC[]={0,0,-1,1};
        for(int i=0; i<4; i++) {
            int nL=l+dL[i], nC=c+dC[i];


            if (jardim.validaPosicao(nL, nC) && jardim.getPlanta(nL, nC) == nullptr) {

                //cria na memoria temporaria
                auto filho = make_unique<Cacto>();

                int metadeAgua = this->agua / 2;
                int metadeNutrientes = this->nutrientes / 2;

                this->agua -= metadeAgua;
                this->nutrientes -= metadeNutrientes;

                filho->agua = metadeAgua;
                filho->nutrientes = metadeNutrientes;

                jardim.adicionarPlanta(nL, nC, std::move(filho));

                break;
            }
        }
    }
}