#include "../include/juego.h"
#include "../include/tablero.h"

#include <ctime>
using namespace std;

int main() {
    inicializarTablero();
    imprimirTableroBonito();


    srand(time(0)); 
    Juego juego;
    juego.iniciar();

    
    while (!juego.juegoTerminado()) {
        juego.jugarTurno();
    }

    juego.mostrarEstadoGeneral();
    juego.mostrarGanador();

    return 0;
}
