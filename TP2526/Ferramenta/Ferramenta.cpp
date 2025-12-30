#include "Ferramenta.h"

int Ferramenta::proximoID = 1;

Ferramenta::Ferramenta(char s) : simbolo(s) {
    numeroSerie = proximoID++;
}

Ferramenta::~Ferramenta() { }

int Ferramenta::getNumeroSerie() const {
    return numeroSerie;
}

char Ferramenta::getSimbolo() const {
    return simbolo;
}