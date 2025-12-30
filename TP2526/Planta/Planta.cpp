//
// Created by duart on 30/10/2025.
//

#include "Planta.h"

Planta::Planta(char s) : simbolo(s), viva(true), idade(0), agua(0), nutrientes(0) {}

bool Planta::estaViva() const { return viva; }
char Planta::getSimbolo() const { return simbolo; }
int Planta::getAgua() const { return agua; }
int Planta::getNutrientes() const { return nutrientes; }