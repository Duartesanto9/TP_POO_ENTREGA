#include "Simulador/Simulador.h"
#include "UserInterface/UserInterface.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(std::time(nullptr));
    Simulador sim;
    UserInterface ui(sim);
    ui.executa();
    return 0;
}
