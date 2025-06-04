#include "../include/mapa.h"
#include <iostream>

using namespace std;
Mapa::Mapa() {
    agregarTrayecto("Bogota",       {"Medellin",     "rojo",     4}); // A → B
    agregarTrayecto("Medellin",     {"Cali",         "azul",     3}); // B → C
    agregarTrayecto("Cali",         {"Pereira",      "verde",    4}); // C → D
    agregarTrayecto("Pereira",      {"Manizales",    "amarillo", 2}); // D → E
    agregarTrayecto("Manizales",    {"Tunja",        "negro",    3}); // E → F
    agregarTrayecto("Tunja",        {"Bucaramanga",  "rojo",     5}); // F → G
    agregarTrayecto("Bucaramanga",  {"Cartagena",    "azul",     3}); // G → H
    agregarTrayecto("Cartagena",    {"Santa Marta",  "verde",    2}); // H → I
    agregarTrayecto("Santa Marta",  {"Barranquilla", "amarillo", 4}); // I → J
}

void Mapa::agregarTrayecto(const string& origen, const Trayecto& trayecto) {
    grafo[origen].push_back(trayecto);
}

void Mapa::mostrar() const {
    cout << "\n  Mapa de conexiones:\n";
    for (const auto& par : grafo) {
        cout << "Desde " << par.first << ":\n";
        for (const auto& tray : par.second) {
            cout << " → " << tray.destino << " | Color: " << tray.color << " | Cartas: " << tray.longitud;
            if (tray.reclamado) {
                cout << " | Reclamado por: " << tray.jugador;
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

bool Mapa::existeTrayecto(const string& origen, const string& destino) const {
    auto it = grafo.find(origen);
    if (it != grafo.end()) {
        for (const auto& tray : it->second) {
            if (tray.destino == destino) return true;
        }
    }
    return false;
}

const Trayecto& Mapa::obtenerTrayecto(const string& origen, const string& destino) const {
    for (const auto& tray : grafo.at(origen)) {
        if (tray.destino == destino) return tray;
    }
    throw runtime_error("Trayecto no encontrado.");
}

void Mapa::marcarComoReclamado(const string& origen, const string& destino, const string& jugador) {
    for (auto& tray : grafo[origen]) {
        if (tray.destino == destino && !tray.reclamado) {
            tray.reclamado = true;
            tray.jugador = jugador;
            return;
        }
    }
}
