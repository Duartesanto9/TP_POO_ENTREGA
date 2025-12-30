//
// Created by duart on 30/10/2025.
//

#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include "../Settings.h"
#include "../Ferramenta/Ferramenta.h"
#include <vector>
#include <memory>
#include <string>

class Jardineiro {
private:
    int linha, coluna;
    vector<unique_ptr<Ferramenta>> mochila;
    Ferramenta* ferramentaNaMao;

public:
    Jardineiro();

    void setPosicao(int l, int c);
    int getLinha() const;
    int getColuna() const;

    void apanharFerramenta(unique_ptr<Ferramenta> f);

    void guardarFerramenta();

    unique_ptr<Ferramenta> removerFerramentaAtual();

    bool selecionarFerramenta(int serie);
    Ferramenta* getFerramentaNaMao() const;

    string listarFerramentas() const;
};

#endif
