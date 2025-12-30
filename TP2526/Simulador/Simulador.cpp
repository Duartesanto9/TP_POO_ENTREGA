#include "Simulador.h"

#include "../Planta/Cacto/Cacto.h"
#include "../Planta/Roseira/Roseira.h"
#include "../Planta/ErvaDaninha/ErvaDaninha.h"
#include "../Planta/PlantaExotica/PlantaExotica.h"
#include "../Ferramenta/Regador/Regador.h"
#include "../Ferramenta/Adubo/Adubo.h"
#include "../Ferramenta/TessouraPoda/TessouraPoda.h"
#include "../Ferramenta/FerramentaZ/FerramentaZ.h"
#include "../Settings.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

Simulador::Simulador() {
    jardim = nullptr;
    terminado = false;
    turno = 0;


    jardineiroNoJardim = false;
    jaSaiuNesteTurno = false;
    jaEntrouNesteTurno = false;

    colheContador = 0;
    plantaContador = 0;
    movimentoContador = 0;
}

Simulador::~Simulador() { }

bool Simulador::naoTermina() const { return !terminado; }

bool Simulador::validaJardim() const {
    if (!jardim) {
        cout << "O jardim ainda nao foi criado (use comando 'jardim')." << endl;
        return false;
    }
    return true;
}

// Cria ferramenta numa pos aleatoria
void Simulador::spawnFerramenta() {
    if (!jardim) return;

    // encontra posição livre
    for(int k=0; k<10; k++) { //limite 10 vezes
        int rL = rand() % jardim->getLinhas();
        int rC = rand() % jardim->getColunas();

        //se ja tiver ferramenta tenta outra vez
        int tipo = rand() % 4;
        unique_ptr<Ferramenta> nf;
        if(tipo == 0) nf = make_unique<Regador>();
        else if(tipo == 1) nf = make_unique<Adubo>();
        else if(tipo == 2) nf = make_unique<TessouraPoda>();
        else nf = make_unique<FerramentaZ>();

        if(jardim->adicionarFerramenta(rL, rC, std::move(nf))) {
            cout << "Nova ferramenta adicionada ao jardim" << endl;
            return;
        }
    }
}


void Simulador::fazOpe(const string &linha) {
    if (linha.empty()) return;
    stringstream ss(linha);
    string cmd, args;
    ss >> cmd;
    getline(ss, args);

    if (!args.empty() && args[0] == ' ') args = args.substr(1);


    if (cmd == "jardim") comandoJardim(args);
    else if (cmd == "avanca") avanca(args);
    else if (cmd == "lplantas") lplantas();
    else if (cmd == "lplanta") lplanta(args);
    else if (cmd == "larea") larea();
    else if (cmd == "lsolo") lsolo(args);
    else if (cmd == "lferr") lferr();
    else if (cmd == "colhe") colhe(args);
    else if (cmd == "planta") planta(args);
    else if (cmd == "larga") larga();
    else if (cmd == "pega") pega(args);
    else if (cmd == "compra") compra(args);
    else if (cmd == "move") move(args);
    else if (cmd == "entra") entra(args);
    else if (cmd == "sai") sai();
    else if (cmd == "grava") grava(args);
    else if (cmd == "recupera") recupera(args);
    else if (cmd == "apaga") apaga(args);
    else if (cmd == "executa") executa(args);
    else if (cmd == "fim") fim();
    else cout << "Comando desconhecido: " << cmd << endl;
}


void Simulador::comandoJardim(const string &args) {
    if (jardim) { cout << "Jardim ja existe." << endl; return; }
    stringstream ss(args);
    int l, c;
    if (!(ss >> l >> c)) { cout << "Parametros invalidos." << endl; return; }
    if (l > 26 || c > 26) { cout << "Dimensoes maximas 26x26."<< endl; return; }

    jardim = make_unique<Jardim>(l, c);

    for(int i=0; i<3; i++) {
        spawnFerramenta();
    }
    cout << "Jardim criado (" << l << "x" << c << ")." << endl;

    jardim->mostrar(jardineiroNoJardim, jardineiro.getLinha(), jardineiro.getColuna());
}

void Simulador::avanca(const string &args) {
    if (!validaJardim()) return;
    int n = 1;
    if (!args.empty()) {
        try { n = stoi(args); } catch(...) { n = 1; }
    }
    if (n < 1) n = 1;

    for (int k = 0; k < n; ++k) {
        cout << "--- Instante " << turno + 1 << " ---" << endl;

        //plantas
        vector<pair<int, int>> coords;
        for (int i = 0; i < jardim->getLinhas(); ++i)
            for (int j = 0; j < jardim->getColunas(); ++j)
                if (jardim->getPlanta(i, j)) coords.push_back({i, j});

        for (auto p : coords) {
            Planta* planta = jardim->getPlanta(p.first, p.second);
            if (planta && planta->estaViva()) {
                planta->agir(*jardim, p.first, p.second);
                if (!planta->estaViva()) {
                    cout << "Planta morreu em " << (char)('A' + p.first) << (char)('A' + p.second) << endl;
                    jardim->removerPlanta(p.first, p.second);
                }
            }
        }

        //ferramentas
        if (jardineiroNoJardim) {
            Ferramenta* f = jardineiro.getFerramentaNaMao();
            if (f) {
                //se usar retornar true a ferramenta gastou-se
                bool partiu = f->usar(*jardim, jardineiro.getLinha(), jardineiro.getColuna());
                if (partiu) {
                    jardineiro.removerFerramentaAtual();
                    cout << "Ferramenta removida da mochila." << endl;
                }
            }
        }

        turno++;
        colheContador = 0;
        plantaContador = 0;
        movimentoContador = 0;
        jaEntrouNesteTurno = false;
        jaSaiuNesteTurno = false;
    }
    jardim->mostrar(jardineiroNoJardim, jardineiro.getLinha(), jardineiro.getColuna());
}

// ---------------------------------------------------------
//                 COMANDOS DE MOVIMENTO
// ---------------------------------------------------------

void Simulador::entra(const string &args) {
    if(!validaJardim()) return;
    if(jaEntrouNesteTurno) { cout << "Ja entrou/saiu o maximo permitido neste turno." << endl; return; }

    if(jardineiroNoJardim) {
        stringstream ss(args); string pos; ss >> pos;
        int l = tolower(pos[0])-'a'; int c = tolower(pos[1])-'a';
        if(jardim->validaPosicao(l, c)) {
            jardineiro.setPosicao(l, c);
            cout << "Jardineiro moveu-se para " << pos << endl;
            jardim->mostrar(jardineiroNoJardim, jardineiro.getLinha(), jardineiro.getColuna());
        } else cout << "Posicao invalida."<< endl;
        return;
    }

    // se estiver fora
    stringstream ss(args); string pos; ss >> pos;
    int l = tolower(pos[0])-'a'; int c = tolower(pos[1])-'a';
    if(jardim->validaPosicao(l, c)) {
        jardineiroNoJardim = true;
        jaEntrouNesteTurno = true;
        jardineiro.setPosicao(l, c);

        // ve se tem ferramenta na possiçao
        unique_ptr<Ferramenta> fChao = jardim->removerFerramenta(l, c);
        if(fChao) {
            cout << "Encontrou " << fChao->getTipo() << " ao entrar e apanhou-a!"<< endl;
            jardineiro.apanharFerramenta(std::move(fChao));
            spawnFerramenta();
        }

        cout << "Jardineiro entrou no jardim." << endl;
        jardim->mostrar(jardineiroNoJardim, jardineiro.getLinha(), jardineiro.getColuna());
    } else cout << "Posicao invalida." << endl;
}

void Simulador::sai() {
    if(!jardineiroNoJardim) { cout << "Ja esta fora." << endl; return; }
    if(jaSaiuNesteTurno) { cout << "Ja nao pode sair neste turno." << endl; return; }

    jardineiroNoJardim = false;
    jaSaiuNesteTurno = true;
    cout << "Saiu do jardim." << endl;
}

void Simulador::move(const string &args) {
    if(!jardineiroNoJardim) { cout << "Jardineiro nao esta no jardim (use 'entra')." << endl; return; }
    if(movimentoContador >= Settings::Jardineiro::max_movimentos) {
        cout << "Limite de movimentos, avance de instante" << endl; return;
    }

    int dL=0, dC=0;

    char dir = tolower(args[0]);
    if(dir == 'c') dL = -1;
    else if(dir == 'b') dL = 1;
    else if(dir == 'e') dC = -1;
    else if(dir == 'd') dC = 1;
    else { cout << "Direcao invalida (c/b/e/d)." << endl; return; }

    int nL = jardineiro.getLinha() + dL;
    int nC = jardineiro.getColuna() + dC;

    if(jardim->validaPosicao(nL, nC)) {
        jardineiro.setPosicao(nL, nC);
        movimentoContador++;

        // apanha ferramenta automaticamente
        unique_ptr<Ferramenta> fChao = jardim->removerFerramenta(nL, nC);
        if(fChao) {
            cout << "Apanhou " << fChao->getTipo() << "!" << endl;
            jardineiro.apanharFerramenta(std::move(fChao));
            spawnFerramenta();
        }

        jardim->mostrar(jardineiroNoJardim, jardineiro.getLinha(), jardineiro.getColuna());
    } else {
        cout << "Limite de movimentos por turno atingido" << endl;
    }
}


void Simulador::colhe(const string &args) {
    if (!validaJardim()) return;
    if (colheContador >= Settings::Jardineiro::max_colheitas) {
        cout << "Ja colheu o maximo de plantas neste turno." << endl; return;
    }
    if (args.length() < 2) return;
    int l = tolower(args[0]) - 'a';
    int c = tolower(args[1]) - 'a';

    if (jardim->removerPlanta(l, c)) {
        cout << "Planta colhida com sucesso." << endl;
        colheContador++;
        jardim->mostrar(jardineiroNoJardim, jardineiro.getLinha(), jardineiro.getColuna());
    } else {
        cout << "Nao ha planta nessa posicao." << endl;
    }
}

void Simulador::planta(const string &args) {
    if (!validaJardim()) return;
    if (plantaContador >= Settings::Jardineiro::max_plantacoes) {
        cout << "Ja plantou o maximo neste turno." << endl; return;
    }
    stringstream ss(args);
    string pos, tipoStr;
    ss >> pos >> tipoStr;
    if(pos.size() < 2 || tipoStr.empty()) return;

    int l = tolower(pos[0]) - 'a';
    int c = tolower(pos[1]) - 'a';
    char tipo = tolower(tipoStr[0]);

    unique_ptr<Planta> nova;
    if(tipo == 'c') nova = make_unique<Cacto>();
    else if(tipo == 'r') nova = make_unique<Roseira>();
    else if(tipo == 'e') nova = make_unique<ErvaDaninha>();
    else if(tipo == 'x') nova = make_unique<PlantaExotica>();
    else { cout << "Planta desconhecida (c, r, e, x)." << endl; return; }

    if(jardim->adicionarPlanta(l, c, std::move(nova))) {
        cout << "Planta colocada." << endl;
        plantaContador++;
        jardim->mostrar(jardineiroNoJardim, jardineiro.getLinha(), jardineiro.getColuna());
    } else {
        cout << "Nao foi possivel plantar (local ocupado ou invalido)." << endl;
    }
}

void Simulador::larga() {
    Ferramenta* f = jardineiro.getFerramentaNaMao();
    if(f) {
        cout << "Guardou " << f->getTipo() << " na mochila." << endl;
        jardineiro.guardarFerramenta();
    } else {
        cout << "Nao tem ferramenta na mao." << endl;
    }
}

void Simulador::pega(const string &args) {
    if(args.empty()) return;
    int id = stoi(args);
    if(jardineiro.selecionarFerramenta(id)) {
        cout << "Pegou na ferramenta " << id << "." << endl;
    } else {
        cout << "Ferramenta nao encontrada na mochila." << endl;
    }
}

void Simulador::compra(const string &args) {
    if(args.empty()) return;
    char tipo = tolower(args[0]);
    unique_ptr<Ferramenta> f;

    if(tipo == 'g') f = make_unique<Regador>();
    else if(tipo == 'a') f = make_unique<Adubo>();
    else if(tipo == 't') f = make_unique<TessouraPoda>();
    else if(tipo == 'z') f = make_unique<FerramentaZ>();
    else { cout << "Ferramenta invalida. (g, a, t, z)." << endl; return; }

    cout << "Comprou " << f->getTipo() << "." << endl;
    jardineiro.apanharFerramenta(std::move(f));
}


void Simulador::lplantas() {
    if (!validaJardim()) return;
    cout << "--- Lista de Plantas ---" << endl;
    for(int i=0; i<jardim->getLinhas(); i++) {
        for(int j=0; j<jardim->getColunas(); j++) {
            Planta* p = jardim->getPlanta(i, j);
            if(p) {
                cout << "[" << (char)('A'+i) << (char)('A'+j) << "] "
                     << p->getTipo() << " | Saude: " << p->getAgua() << "A " << p->getNutrientes() << "N\n";
            }
        }
    }
}

void Simulador::lplanta(const string &args) {
    if (!validaJardim() || args.length() < 2) return;
    int l = tolower(args[0]) - 'a';
    int c = tolower(args[1]) - 'a';

    Planta* p = jardim->getPlanta(l, c);
    if(p) {
        cout << "Planta em " << args << ": " << p->getTipo() << endl;
        cout << "Agua: " << p->getAgua() << ", Nutrientes: " << p->getNutrientes() << endl;
        cout << "Viva: " << (p->estaViva() ? "Sim" : "Nao") << endl;
    } else {
        cout << "Nenhuma planta nessa posicao." << endl;
    }
}

void Simulador::larea() {
    if (!validaJardim()) return;
    cout << "--- Area Ocupada ---" << endl;
    for(int i=0; i<jardim->getLinhas(); i++) {
        for(int j=0; j<jardim->getColunas(); j++) {
            Planta* p = jardim->getPlanta(i, j);
            Ferramenta* f = jardim->getFerramenta(i, j);
            if(p || f) {
                cout << "[" << (char)('A'+i) << (char)('A'+j) << "] ";
                if(p) cout << "Planta: " << p->getTipo() << " ";
                if(f) cout << "Ferramenta: " << f->getTipo() << " ";
                cout << "| Solo: " << jardim->getAgua(i, j) << "A " << jardim->getNutrientes(i, j) << "N\n";
            }
        }
    }
}

void Simulador::lsolo(const string &args) {
    if (!validaJardim() || args.empty()) return;
    stringstream ss(args);
    string pos; int raio = 0;
    ss >> pos;
    if(ss >> raio) {}

    int l = tolower(pos[0]) - 'a';
    int c = tolower(pos[1]) - 'a';

    if(!jardim->validaPosicao(l, c)) { cout << "Posicao invalida." << endl; return; }

    int inicioL = max(0, l - raio);
    int fimL = min(jardim->getLinhas()-1, l + raio);
    int inicioC = max(0, c - raio);
    int fimC = min(jardim->getColunas()-1, c + raio);

    for(int i=inicioL; i<=fimL; i++) {
        for(int j=inicioC; j<=fimC; j++) {
            cout << "[" << (char)('A'+i) << (char)('A'+j) << "] "
                 << "Agua: " << jardim->getAgua(i, j)
                 << " | Nutrientes: " << jardim->getNutrientes(i, j);
            if(jardim->getPlanta(i,j)) cout << " [Tem Planta]";
            if(jardim->getFerramenta(i,j)) cout << " [Tem Ferramenta]";
            cout << endl;
        }
    }
}

void Simulador::lferr() {
    cout << "--- Ferramentas do Jardineiro ---" << endl;
    cout << jardineiro.listarFerramentas();
}


void Simulador::grava(const string &nome) {
    if(!validaJardim()) return;
    copiasJardim[nome] = make_unique<Jardim>(*jardim);
    cout << "Estado gravado como '" << nome << "'." << endl;
}

void Simulador::recupera(const string &nome) {
    auto it = copiasJardim.find(nome);
    if(it != copiasJardim.end()) {
        jardim = make_unique<Jardim>(*(it->second));
        copiasJardim.erase(it);
        cout << "Jardim recuperado." << endl;
        jardim->mostrar(jardineiroNoJardim, jardineiro.getLinha(), jardineiro.getColuna());
    } else {
        cout << "Gravacao nao encontrada." << endl;
    }
}

void Simulador::apaga(const string &nome) {
    if(copiasJardim.erase(nome)) cout << "Gravacao apagada." << endl;
    else cout << "Gravacao nao encontrada." << endl;
}

void Simulador::executa(const string &nomeFicheiro) {
    ifstream file(nomeFicheiro);
    if(!file.is_open()) { cout << "Erro ao abrir ficheiro." << endl; return; }

    string linha;
    while(getline(file, linha)) {
        cout << ">> CMD: " << linha << endl;
        fazOpe(linha);
        if(terminado) break;
    }
    file.close();
}

void Simulador::fim() {
    terminado = true;
    cout << "Simulador terminado." << endl;
}