#include "../include/juego.h"
#include "../include/mapa.h"
#include "../include/tablero.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random> 
#include <string>

using namespace std;
string obtenerColorAleatorio() {
    vector<string> colores = {"rojo", "azul", "verde", "amarillo", "negro"};
    int indice = rand() % colores.size();
    return colores[indice];
}

Juego::Juego() : turnoActual(0) {}

void Juego::inicializarMazo() {
    vector<string> colores =  {"rojo", "azul", "verde", "amarillo", "negro"};
    
    for (const auto& color : colores) {
        for (int i = 0; i < 12; ++i) {
            mazo.push_back(color);
        }
    }

    // Barajar el mazo
    auto rng = default_random_engine(time(nullptr));
    shuffle(mazo.begin(), mazo.end(), rng);

    // Inicializar zona de descarte
    for (int i = 0; i < 5 && !mazo.empty(); ++i) {
        zonaVisible.push_back(robarCarta());
    }
}

string Juego::robarCarta() {
    if (mazo.empty()) {
        rebarajarSiEsNecesario();
    }

    if (!mazo.empty()) {
        string carta = mazo.front();
        mazo.pop_front();
        return carta;
    } else {
        return "";  // No hay cartas disponibles
    }
}

void Juego::rebarajarSiEsNecesario() {
    if (mazo.empty() && !descarte.empty()) {
        copy(descarte.begin(), descarte.end(), back_inserter(mazo));
        descarte.clear();

        auto rng = default_random_engine(time(nullptr));
        shuffle(mazo.begin(), mazo.end(), rng);
    }
}



void Juego::iniciar() {
    inicializarTablero();
    cout << "¡Bienvenido a Ticket to Ride!\n";
    cout << "Ingrese el nombre de los 4 jugadores:\n";
    for (int i = 0; i < 4; ++i) {
        string nombre;
        cout << " - Jugador " << (i + 1) << ": ";
        getline(cin, nombre);
        jugadores.push_back(Jugador(nombre));
    }
    inicializarMazo();
    cout << "\n Jugadores registrados. Comienza la partida\n";
    reponerCartasVisibles();

}

void Juego::jugarTurno() {
    Jugador& jugador = jugadores[turnoActual];
    cout << "\n Turno de " << jugador.getNombre() << "\n";

    // Robo de cartas
    string carta1 = robarCarta();
    string carta2 = robarCarta();
    if (!carta1.empty()) jugador.agregarCartas(carta1, 1);
    if (!carta2.empty()) jugador.agregarCartas(carta2, 1);


    cout << "\n Cartas robadas: " << carta1 << ", " << carta2 << "\n";

    bool turnoActivo = true;
    while (turnoActivo) {
        cout << "\n Menu de acciones:\n";
        cout << "1. Ver mapa\n";
        cout << "2. Ver estado personal\n";
        cout << "3. Reclamar trayecto\n";
        cout << "4. Terminar turno\n";
        cout << "5. Ver zona de descarte\n";
        cout << "6. Robar carta de la zona de descarte\n";

        cout << "Elige una opcion: ";

        string opcion;
        getline(cin, opcion);

        if (opcion == "1") {
            mapa.mostrar();
            imprimirTableroBonito();  
            mostrarLeyendaDeTrayectos();
        } else if (opcion == "2") {
            jugador.mostrarEstado();
        } else if (opcion == "3") {
            string origen, destino, color;
            cout << "Ingrese la estacion de origen: ";
            getline(cin, origen);
            cout << "Ingrese la estacion de destino: ";
            getline(cin, destino);

            if (!mapa.existeTrayecto(origen, destino)) {
                cout << "El trayecto no existe.\n";
                continue;
            }

            const Trayecto& tray = mapa.obtenerTrayecto(origen, destino);
            if (tray.reclamado) {
                cout << "El trayecto ya fue reclamado.\n";
                continue;
            }

            cout << "Este trayecto requiere " << tray.longitud << " cartas de color " << tray.color << ".\n";
            cout << "¿Con que color deseas reclamarlo?: ";
            getline(cin, color);

            if (!jugador.tieneCartasSuficientes(color, tray.longitud)) {
                cout << "No tienes suficientes cartas.\n";
                continue;
            }

            jugador.usarCartas(color, tray.longitud);

            for (int i = 0; i < tray.longitud; ++i) {
            descarte.push_back(color);  // guarda cada carta usada
            }

            jugador.reclamarTrayecto(origen, destino, tray.longitud);
            mapa.marcarComoReclamado(origen, destino, jugador.getNombre());
            for (const auto& con : conexiones) {
                char letra1 = tablero[con.fila1][con.col1];
                char letra2 = tablero[con.fila2][con.col2];

                if ((letra1 == origen[0] && letra2 == destino[0]) || (letra1 == destino[0] && letra2 == origen[0])) {
                    actualizarTableroConexion(con.fila1, con.col1, con.fila2, con.col2, jugador.getNombre()[0]);
                }
            }



            cout << "Trayecto reclamado con exito.\n";
        } else if (opcion == "4") {
            turnoActivo = false;
        } else if (opcion == "5") {
            mostrarZonaVisible();
        }else if (opcion == "6") {
            mostrarZonaVisible();
            string entrada;
            cout << "Ingresa el indice de la carta (0-4): ";
            getline(cin, entrada);

            if (entrada.empty() || entrada.find_first_not_of("01234") != string::npos) {
                cout << "Entrada invalida. Debes ingresar un numero entre 0 y 4.\n";
                continue;
            }

            int indice = stoi(entrada);

            string carta;
            if (robarDeZonaVisible(indice, carta)) {
                cout << "Robaste: " << carta << "\n";
                jugador.agregarCartas(carta, 1);
                reponerCartasVisibles();  // Reponemos después de robar
            } else {
                cout << "Indice invalido o carta no disponible.\n";
            }
        }else {
            cout << "Opción invalida. Intenta de nuevo.\n";
        }
    }

    // Cambiar turno
    turnoActual = (turnoActual + 1) % jugadores.size();
}


void Juego::mostrarEstadoGeneral() const {
    cout << "\nEstado general del juego:\n";
    for (const auto& jugador : jugadores) {
        jugador.mostrarEstado();
        cout << "-----------------------------\n";
    }
}

bool Juego::juegoTerminado() const {
    for (const auto& jugador : jugadores) {
        if (jugador.getVagones() < 5) {
            cout << "El " << jugador.getNombre() << " tiene menos de 5 vagones. ¡El juego ha terminado!\n";
            return true;
        }
    }
    return false;
}

void Juego::mostrarGanador() const {
    int maxPuntos = 0;
    vector<string> ganadores;

    for (const auto& jugador : jugadores) {
        if (jugador.getPuntaje() > maxPuntos) {
            maxPuntos = jugador.getPuntaje();
            ganadores.clear();
            ganadores.push_back(jugador.getNombre());
        } else if (jugador.getPuntaje() == maxPuntos) {
            ganadores.push_back(jugador.getNombre());
        }
    }

    cout << "\nPUNTUACION FINAL:\n";
    for (const auto& jugador : jugadores) {
        cout << " - " << jugador.getNombre() << ": " << jugador.getPuntaje() << " puntos\n";
    }

    if (ganadores.size() == 1) {
        cout << "\n¡El ganador es " << ganadores[0] << " con " << maxPuntos << " puntos!\n";
    } else {
        cout << "\n¡Empate entre: ";
        for (const auto& nombre : ganadores) {
            cout << nombre << " ";
        }
        cout << "con " << maxPuntos << " puntos!\n";
    }
}

void Juego::reponerCartasVisibles() {
    while (zonaVisible.size() < 5 && !mazo.empty()) {
        zonaVisible.push_back(mazo.front());
        mazo.pop_front();
    }
}
void Juego::mostrarZonaVisible() const {
    cout << "\nZona de descarte:\n";

    for (size_t i = 0; i < zonaVisible.size(); ++i) {
        string color;
        const string& carta = zonaVisible[i];

        if (carta == "rojo") color = "\033[31m";
        else if (carta == "azul") color = "\033[34m";
        else if (carta == "verde") color = "\033[32m";
        else if (carta == "amarillo") color = "\033[33m";
        else if (carta == "negro") color = "\033[30m";
        

        cout << i << ": " << color << carta << "\033[0m" << "\n";
    }
}


bool Juego::robarDeZonaVisible(int indice, string& cartaRobada) {
    if (indice >= 0 && indice < static_cast<int>(zonaVisible.size())) {
        cartaRobada = zonaVisible[indice];
        zonaVisible.erase(zonaVisible.begin() + indice);
        return true;
    }
    return false;
}


