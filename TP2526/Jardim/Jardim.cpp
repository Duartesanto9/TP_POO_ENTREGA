#include "Jardim.h"
#include <cstdlib>

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    solo = new Celula*[linhas];
    for (int i = 0; i < linhas; ++i) {
        solo[i] = new Celula[colunas];
        for (int j = 0; j < colunas; ++j) {
            int minA = Settings::Jardim::agua_min;
            int maxA = Settings::Jardim::agua_max;
            solo[i][j].agua = minA + rand() % (maxA - minA + 1);

            int minN = Settings::Jardim::nutrientes_min;
            int maxN = Settings::Jardim::nutrientes_max;
            solo[i][j].nutrientes = minN + rand() % (maxN - minN + 1);
        }
    }
}

Jardim::Jardim(const Jardim& outro) : linhas(outro.linhas), colunas(outro.colunas) {
    solo = new Celula*[linhas];
    for (int i = 0; i < linhas; ++i) {
        solo[i] = new Celula[colunas];
        for (int j = 0; j < colunas; ++j) {
            solo[i][j].agua = outro.solo[i][j].agua;
            solo[i][j].nutrientes = outro.solo[i][j].nutrientes;
            if (outro.solo[i][j].planta)
                solo[i][j].planta = outro.solo[i][j].planta->clone();
            if (outro.solo[i][j].ferramenta)
                solo[i][j].ferramenta = outro.solo[i][j].ferramenta->clone();
        }
    }
}

Jardim::~Jardim() {
    for (int i = 0; i < linhas; ++i)
        delete[] solo[i];
    delete[] solo;
}


void Jardim::mostrar(bool temJardineiro, int jarL, int jarC) const {
    cout << "  ";
    for (int j = 0; j < colunas; ++j) cout << (char)('A' + j);
    cout << endl;

    for (int i = 0; i < linhas; ++i) {
        cout << (char)('A' + i) << " ";
        for (int j = 0; j < colunas; ++j) {

            // prioridades
            if (temJardineiro && i == jarL && j == jarC) {
                cout << "*";
            }
            else if (solo[i][j].planta) {
                cout << solo[i][j].planta->getSimbolo();
            }
            else if (solo[i][j].ferramenta) {
                cout << solo[i][j].ferramenta->getSimbolo();
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

bool Jardim::validaPosicao(int l, int c) const {
    return l >= 0 && l < linhas && c >= 0 && c < colunas;
}
int Jardim::getLinhas() const { return linhas; }
int Jardim::getColunas() const { return colunas; }

bool Jardim::adicionarPlanta(int l, int c, unique_ptr<Planta> p) {
    if (!validaPosicao(l, c) || solo[l][c].planta) return false;
    solo[l][c].planta = std::move(p);
    return true;
}

unique_ptr<Planta> Jardim::removerPlanta(int l, int c) {
    if (!validaPosicao(l, c)) return nullptr;
    return std::move(solo[l][c].planta);
}

Planta* Jardim::getPlanta(int l, int c) const {
    if (!validaPosicao(l, c)) return nullptr;
    return solo[l][c].planta.get();
}

bool Jardim::adicionarFerramenta(int l, int c, unique_ptr<Ferramenta> f) {
    if (!validaPosicao(l, c) || solo[l][c].ferramenta) return false;
    solo[l][c].ferramenta = std::move(f);
    return true;
}

unique_ptr<Ferramenta> Jardim::removerFerramenta(int l, int c) {
    if (!validaPosicao(l, c)) return nullptr;
    return std::move(solo[l][c].ferramenta);
}

Ferramenta* Jardim::getFerramenta(int l, int c) const {
    if (!validaPosicao(l, c)) return nullptr;
    return solo[l][c].ferramenta.get();
}

int Jardim::getAgua(int l, int c) const { return validaPosicao(l,c) ? solo[l][c].agua : 0; }
int Jardim::getNutrientes(int l, int c) const { return validaPosicao(l,c) ? solo[l][c].nutrientes : 0; }

void Jardim::addAgua(int l, int c, int qtd) {
    if (validaPosicao(l, c)) {
        solo[l][c].agua += qtd;
        if (solo[l][c].agua < 0) solo[l][c].agua = 0;
    }
}
void Jardim::addNutrientes(int l, int c, int qtd) {
    if (validaPosicao(l, c)) {
        solo[l][c].nutrientes += qtd;
        if (solo[l][c].nutrientes < 0) solo[l][c].nutrientes = 0;
    }
}