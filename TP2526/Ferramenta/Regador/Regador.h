#ifndef REGADOR_H
#define REGADOR_H
#include "../Ferramenta.h"

class Regador : public Ferramenta {
    int capacidade;
public:
    Regador();
    unique_ptr<Ferramenta> clone() const override;
    string getTipo() const override;

    bool usar(Jardim& jardim, int l, int c) override;
};

#endif