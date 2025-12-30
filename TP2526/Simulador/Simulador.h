#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "../Jardim/Jardim.h"
#include "../Jardineiro/Jardineiro.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class Simulador {
private:
    unique_ptr<Jardim> jardim;
    Jardineiro jardineiro;
    map<string, unique_ptr<Jardim>> copiasJardim;

    bool terminado;
    int turno;

    bool jardineiroNoJardim;
    bool jaSaiuNesteTurno;
    bool jaEntrouNesteTurno;

    int colheContador;
    int plantaContador;
    int movimentoContador;

    bool validaJardim() const;
    void spawnFerramenta();

public:
    Simulador();
    ~Simulador();

    bool naoTermina() const;
    void fazOpe(const string &linha);


    void comandoJardim(const string &args);
    void avanca(const string &args);

    void lplantas();
    void lplanta(const string &args);
    void larea();
    void lsolo(const string &args);
    void lferr();

    void colhe(const string &args);
    void planta(const string &args);
    void larga();
    void pega(const string &args);
    void compra(const string &args);

    void move(const string &args);
    void entra(const string &args);
    void sai();

    void grava(const string &args);
    void recupera(const string &args);
    void apaga(const string &args);
    void executa(const string &args);
    void fim();
};

#endif // SIMULADOR_H