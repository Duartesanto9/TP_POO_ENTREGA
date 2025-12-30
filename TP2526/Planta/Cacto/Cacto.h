#ifndef CACTO_H
#define CACTO_H

#include "../Planta.h"

class Cacto : public Planta {
    int contadorExcessoA;
    int contadorFaltaN;
public:
    Cacto();
    unique_ptr<Planta> clone() const override;
    string getTipo() const override;

    Beleza getBeleza() const override;

    void agir(Jardim& jardim, int l, int c) override;
};

#endif