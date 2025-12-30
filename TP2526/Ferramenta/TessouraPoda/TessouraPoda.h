#ifndef TESSOURAPODA_H
#define TESSOURAPODA_H

#include "../Ferramenta.h"

class TessouraPoda : public Ferramenta {
public:
    TessouraPoda();
    unique_ptr<Ferramenta> clone() const override;
    string getTipo() const override;


    bool usar(Jardim& jardim, int l, int c) override;
};

#endif //TESSOURAPODA_H