#ifndef FERRAMENTAZ_H
#define FERRAMENTAZ_H

#include "../Ferramenta.h"

class FerramentaZ : public Ferramenta {
public:
    FerramentaZ();

    unique_ptr<Ferramenta> clone() const override;

    string getTipo() const override;

    bool usar(Jardim& jardim, int l, int c) override;
};

#endif