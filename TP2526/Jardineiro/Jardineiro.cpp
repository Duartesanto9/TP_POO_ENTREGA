#include "Jardineiro.h"
#include <sstream>

Jardineiro::Jardineiro() : linha(-1), coluna(-1), ferramentaNaMao(nullptr) {}

void Jardineiro::setPosicao(int l, int c) { linha = l; coluna = c; }
int Jardineiro::getLinha() const { return linha; }
int Jardineiro::getColuna() const { return coluna; }

void Jardineiro::apanharFerramenta(unique_ptr<Ferramenta> f) {
    if (f) {
        mochila.push_back(std::move(f));
        if (!ferramentaNaMao) ferramentaNaMao = mochila.back().get();
    }
}

void Jardineiro::guardarFerramenta() {
    ferramentaNaMao = nullptr;
}

unique_ptr<Ferramenta> Jardineiro::removerFerramentaAtual() {
    if (!ferramentaNaMao) return nullptr;

    for (auto it = mochila.begin(); it != mochila.end(); ++it) {
        if (it->get() == ferramentaNaMao) {
            unique_ptr<Ferramenta> temp = std::move(*it);
            mochila.erase(it);

            ferramentaNaMao = nullptr;

            return temp;
        }
    }
    return nullptr;
}

bool Jardineiro::selecionarFerramenta(int serie) {
    for (const auto& f : mochila) {
        if (f->getNumeroSerie() == serie) {
            ferramentaNaMao = f.get();
            return true;
        }
    }
    return false;
}

Ferramenta* Jardineiro::getFerramentaNaMao() const { return ferramentaNaMao; }

string Jardineiro::listarFerramentas() const {
    stringstream ss;
    if (mochila.empty()) {
        ss << "Mochila vazia." << endl;
    } else {
        for (const auto& f : mochila) {
            ss << f->getTipo() << " (ID:" << f->getNumeroSerie() << ")";
            if (f.get() == ferramentaNaMao) ss << " [EM MAO]";
            ss << "\n";
        }
    }
    return ss.str();
}