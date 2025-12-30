//
// Created by duart on 30/10/2025.
//

#ifndef JARDIM_H
#define JARDIM_H

#include "../Settings.h"
#include "../Planta/Planta.h"
#include "../Ferramenta/Ferramenta.h"
#include <memory>
#include <iostream>

struct Celula {
    int agua;
    int nutrientes;
    unique_ptr<Planta> planta;
    unique_ptr<Ferramenta> ferramenta;

    Celula() : agua(0), nutrientes(0), planta(nullptr), ferramenta(nullptr) {}
};

class Jardim {
private:
    int linhas;
    int colunas;
    Celula **solo;

public:
    Jardim(int l, int c);
    Jardim(const Jardim& outro);
    ~Jardim();

    void mostrar(bool temJardineiro = false, int jarL = -1, int jarC = -1) const;

    bool validaPosicao(int l, int c) const;
    int getLinhas() const;
    int getColunas() const;

    bool adicionarPlanta(int l, int c, unique_ptr<Planta> p);
    unique_ptr<Planta> removerPlanta(int l, int c);
    Planta* getPlanta(int l, int c) const;

    bool adicionarFerramenta(int l, int c, unique_ptr<Ferramenta> f);
    unique_ptr<Ferramenta> removerFerramenta(int l, int c);
    Ferramenta* getFerramenta(int l, int c) const;

    int getAgua(int l, int c) const;
    int getNutrientes(int l, int c) const;
    void addAgua(int l, int c, int qtd);
    void addNutrientes(int l, int c, int qtd);

};

#endif
