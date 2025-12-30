#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "../Planta.h"

class ErvaDaninha : public Planta {
private:
    int instantesSemMultiplicar;
public:
    ErvaDaninha();
    unique_ptr<Planta> clone() const override;
    string getTipo() const override;

    Beleza getBeleza() const override;

    void agir(Jardim& jardim, int l, int c) override;
};

#endif