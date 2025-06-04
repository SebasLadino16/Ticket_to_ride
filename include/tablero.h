#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <vector>
#include <map>
#include <string>


const int FILAS = 20;
const int COLUMNAS = 25;

struct ConexionVisual {
    int fila1, col1;
    int fila2, col2;
    char simbolo;
};

extern std::vector<std::vector<char>> tablero;
extern std::vector<ConexionVisual> conexiones;
extern std::map<char, std::string> coloresJugador;

void inicializarTablero();
void actualizarTableroConexion(int fila1, int col1, int fila2, int col2, char simbolo);
void imprimirTableroBonito();
void mostrarLeyendaDeTrayectos();

#endif