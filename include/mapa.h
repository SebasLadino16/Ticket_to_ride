#ifndef MAPA_H
#define MAPA_H

#include <string>
#include <map>
#include <vector>


struct Trayecto {
    std::string destino;
    std::string color;
    int longitud;
    bool reclamado;
    std::string jugador;

    Trayecto(const std::string& dest, const std::string& col, int len)
        : destino(dest), color(col), longitud(len), reclamado(false), jugador("") {}
};

class Mapa {
private:
    std::map<std::string, std::vector<Trayecto>> grafo;

public:
    Mapa();
    void agregarTrayecto(const std::string& origen, const Trayecto& trayecto);
    void mostrar() const;
    bool existeTrayecto(const std::string& origen, const std::string& destino) const;
    const Trayecto& obtenerTrayecto(const std::string& origen, const std::string& destino) const;
    void marcarComoReclamado(const std::string& origen, const std::string& destino, const std::string& jugador);
};


#endif
