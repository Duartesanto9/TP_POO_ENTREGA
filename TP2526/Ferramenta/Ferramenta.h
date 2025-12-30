#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include "../Settings.h"
#include <string>
#include <memory>
#include <set>

class Jardim;

class Ferramenta {
protected:
    int numeroSerie;
    char simbolo;
    static int proximoID;

public:
    Ferramenta(char s);
    virtual ~Ferramenta();

    virtual unique_ptr<Ferramenta> clone() const = 0;

    int getNumeroSerie() const;
    char getSimbolo() const;

    virtual string getTipo() const = 0;

    virtual bool usar(Jardim& jardim, int l, int c) = 0;
};

#endif // FERRAMENTA_H