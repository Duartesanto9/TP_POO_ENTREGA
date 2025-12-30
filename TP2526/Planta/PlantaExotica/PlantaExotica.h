#ifndef TP_PLANTAEXOTICA_H
#define TP_PLANTAEXOTICA_H

#include "../Planta.h"

class PlantaExotica : public Planta {
private:
    int contadorRelogio;

public:
    PlantaExotica();

    unique_ptr<Planta> clone() const override;
    string getTipo() const override;

    Beleza getBeleza() const override;

    void agir(Jardim& jardim, int l, int c) override;
};

#endif //TP_PLANTAEXOTICA_H