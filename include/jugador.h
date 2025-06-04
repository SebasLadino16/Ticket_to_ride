#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <map>
#include <vector>
#include <utility>

class Jugador {
private:
    std::string nombre;
    int vagones;
    int puntaje;
    std::map<std::string, int> cartas;
    std::vector<std::pair<std::string, std::string>> trayectosReclamados;

public:
    Jugador(const std::string& nombre);
    std::string getNombre() const;
    int getVagones() const;
    int getPuntaje() const;

    void agregarCartas(const std::string& color, int cantidad);
    bool tieneCartasSuficientes(const std::string& color, int cantidad) const;
    void usarCartas(const std::string& color, int cantidad);
    void reclamarTrayecto(const std::string& origen, const std::string& destino, int longitud);
    void mostrarEstado() const;
};

#endif
