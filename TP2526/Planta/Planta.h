#ifndef PLANTA_H
#define PLANTA_H

#include "../Settings.h"
#include <string>
#include <memory>

class Jardim;

enum class Beleza { FEIA, BONITA, NEUTRA };

class Planta {
protected:
    int agua;
    int nutrientes;
    char simbolo;
    bool viva;
    int idade;

public:
    Planta(char s);
    virtual ~Planta() = default;

    virtual unique_ptr<Planta> clone() const = 0;

    bool estaViva() const;
    char getSimbolo() const;
    int getAgua() const;
    int getNutrientes() const;

    virtual Beleza getBeleza() const = 0;

    virtual string getTipo() const = 0;
    virtual void agir(Jardim& jardim, int l, int c) = 0;
    virtual void drenar(int a, int n) {
        agua -= a;
        nutrientes -= n;
        if (agua < 0) agua = 0;
        if (nutrientes < 0) nutrientes = 0;
    }
};

#endif