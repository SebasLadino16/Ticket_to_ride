#include "../include/tablero.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
using namespace std;

vector<ConexionVisual> conexiones = {
    {1, 2, 5, 2, '|'},     // A → B (4)
    {5, 2, 5, 5, '-'},     // B → C (3)
    {5, 5, 9, 5, '|'},     // C → D (4)
    {9, 5, 11, 5, '|'},    // D → E (2) 
    {11, 5, 11, 8, '-'},   // E → F (3)
    {11, 8, 16, 8, '|'},   // F → G (5) 
    {16, 8, 16, 11, '-'},  // G → H (3)
    {16, 11, 16, 13, '-'}, // H → I (2)
    {16, 13, 16, 17, '-'}  // I → J (4)
};


vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, ' '));

void inicializarTablero() {
    for (const auto& con : conexiones) {
        int f1 = con.fila1, c1 = con.col1;
        int f2 = con.fila2, c2 = con.col2;
        int df = (f2 - f1 == 0) ? 0 : (f2 - f1) / abs(f2 - f1);
        int dc = (c2 - c1 == 0) ? 0 : (c2 - c1) / abs(c2 - c1);

        int f = f1 + df;
        int c = c1 + dc;
        while (f != f2 || c != c2) {
            tablero[f][c] = con.simbolo;
            f += df;
            c += dc;
        }
    }

    
    tablero[1][2] = 'A';     // Bogotá
    tablero[5][2] = 'B';     // Medellín
    tablero[5][5] = 'C';     // Cali
    tablero[9][5] = 'D';     // Pereira
    tablero[11][5] = 'E';    // Manizales
    tablero[11][8] = 'F';    // Tunja
    tablero[16][8] = 'G';    // Bucaramanga
    tablero[16][11] = 'H';   // Cartagena
    tablero[16][13] = 'I';   // Santa Marta
    tablero[16][17] = 'J';   // Barranquilla
}

void imprimirTableroBonito() {
    cout << "\n TABLERO (Estaciones y trayectos):\n\n   ";
    for (int col = 0; col < COLUMNAS; ++col) {
        cout << setw(2) << col % 10;
    }
    cout << "\n";

    for (int i = 0; i < FILAS; ++i) {
        cout << setw(2) << i << " ";
        for (int j = 0; j < COLUMNAS; ++j) {
            char c = tablero[i][j];
            string color;
            switch (c) {
                case 'A': case 'a': color = "\033[31m"; break;
                case 'B': case 'b': color = "\033[34m"; break;
                case 'C': case 'c': color = "\033[32m"; break;
                case 'D': case 'd': color = "\033[33m"; break;
                case 'E': case 'e': color = "\033[35m"; break;
                case 'F': case 'f': color = "\033[36m"; break;
                case 'G': case 'g': color = "\033[91m"; break;
                case 'H': case 'h': color = "\033[96m"; break;
                case 'I': case 'i': color = "\033[92m"; break;
                case 'J': case 'j': color = "\033[93m"; break;
                default: color = "\033[0m"; break;
            }

            cout << "[" << color << c << "\033[0m" << "]";
        }
        cout << "\n";
    }
    cout << "\033[0m"; // Reset del color
}

void actualizarTableroConexion(int fila1, int col1, int fila2, int col2, char simbolo) {
    int df = (fila2 - fila1 == 0) ? 0 : (fila2 - fila1) / abs(fila2 - fila1);
    int dc = (col2 - col1 == 0) ? 0 : (col2 - col1) / abs(col2 - col1);

    int f = fila1 + df;
    int c = col1 + dc;
    while (f != fila2 || c != col2) {
        tablero[f][c] = simbolo;
        f += df;
        c += dc;
    }
}

map<char, string> coloresJugador = {
    {'A', "\033[31m"}, // Jugador A - Rojo
    {'B', "\033[34m"}, // Jugador B - Azul
    {'C', "\033[32m"}, // Jugador C - Verde
    {'D', "\033[33m"}  // Jugador D - Amarillo
};

void mostrarLeyendaDeTrayectos() {
    cout << "\nTrayectos disponibles (letras y ciudades):\n";
    map<char, string> letrasCiudades = {
        {'A', "Bogota"}, {'B', "Medellin"}, {'C', "Cali"}, {'D', "Pereira"},
        {'E', "Manizales"}, {'F', "Tunja"}, {'G', "Bucaramanga"},
        {'H', "Cartagena"}, {'I', "Santa Marta"}, {'J', "Barranquilla"}
    };

    for (const auto& con : conexiones) {
        char origen = tablero[con.fila1][con.col1];
        char destino = tablero[con.fila2][con.col2];
        int longitud = max(abs(con.fila2 - con.fila1), abs(con.col2 - con.col1));
        cout << " " << origen << " (" << letrasCiudades[origen] << ")"
                  << " -> " << destino << " (" << letrasCiudades[destino] << ")"
                  << "  | simbolo: '" << con.simbolo << "'"
                  << "  | longitud: " << longitud << "\n";
    }
}
