#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "../Planta.h"

class Roseira : public Planta {
public:
    Roseira();
    unique_ptr<Planta> clone() const override;
    string getTipo() const override;


    Beleza getBeleza() const override;

    void agir(Jardim& jardim, int l, int c) override;
};

#endif