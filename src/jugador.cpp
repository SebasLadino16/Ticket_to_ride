#include "../include/jugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador(const string& nombre) : nombre(nombre), vagones(18), puntaje(0) {}

string Jugador::getNombre() const { return nombre; }

int Jugador::getVagones() const { return vagones; }

int Jugador::getPuntaje() const { return puntaje; }

void Jugador::agregarCartas(const string& color, int cantidad) {
    cartas[color] += cantidad;
}

bool Jugador::tieneCartasSuficientes(const string& color, int cantidad) const {
    auto it = cartas.find(color);
    return it != cartas.end() && it->second >= cantidad;
}

void Jugador::usarCartas(const string& color, int cantidad) {
    if (tieneCartasSuficientes(color, cantidad)) {
        cartas[color] -= cantidad;
    }
}

void Jugador::reclamarTrayecto(const string& origen, const string& destino, int longitud) {
    trayectosReclamados.push_back({origen, destino});
    vagones -= longitud;
    switch (longitud) {
    case 2: puntaje += 1; break;
    case 3: puntaje += 2; break;
    case 4: puntaje += 4; break;
    case 5: puntaje += 6; break;
    case 6: puntaje += 9; break;
    default: puntaje += longitud * 2; 
}

}

void Jugador::mostrarEstado() const {
    cout << "\n Jugador: " << nombre << "\n";
    cout << " Vagones: " << vagones << "\n";
    cout << " Puntaje: " << puntaje << "\n";
    cout << " Cartas:\n";
    for (const auto& par : cartas) {
        cout << " - " << par.first << ": " << par.second << "\n";
    }
    cout << " Trayectos reclamados:\n";
    for (const auto& t : trayectosReclamados) {
        cout << " - " << t.first << " -> " << t.second << "\n";
    }
}
