#ifndef JUEGO_H
#define JUEGO_H

#include "mapa.h"
#include "jugador.h"
#include <vector>
#include "tablero.h"
#include <deque>
#include <random>
#include <algorithm>
#include <string>


class Juego {
private:
    Mapa mapa;
    std::vector<Jugador> jugadores;
    int turnoActual;

    std::deque<std::string> mazo;
    std::vector<std::string> descarte;
    std::vector<std::string> zonaVisible;

    void inicializarMazo();
    std::string robarCarta();
    void rebarajarSiEsNecesario();
    void reponerCartasVisibles();

public:
    Juego();
    void iniciar();
    void jugarTurno();
    void mostrarEstadoGeneral() const;
    bool juegoTerminado() const;
    void mostrarGanador() const;
    void mostrarZonaVisible() const;
    bool robarDeZonaVisible(int indice, std::string& cartaRobada);
};


#endif
