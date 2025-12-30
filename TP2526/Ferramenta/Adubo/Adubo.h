#ifndef ADUBO_H
#define ADUBO_H
#include "../Ferramenta.h"

class Adubo : public Ferramenta {
private:
    int quantidade;
public:
    Adubo();
    unique_ptr<Ferramenta> clone() const override;
    string getTipo() const override;

    bool usar(Jardim& jardim, int l, int c) override;
};

#endif