#  Ticket to Ride 

Proyecto final de programación en C++ que simula el juego de mesa **Ticket to Ride**, adaptado para ejecutarse completamente en la terminal.
---

##  Requisitos

- Compilador C++ (`g++`)
- Consola compatible con ANSI (Windows con terminal moderna, WSL, Linux o macOS)
- Visual Studio Code (recomendado)

---

##  Estructura del proyecto
Proyecto_trenes/
├── include/ # Archivos .h (headers)
├── src/ # Archivos .cpp (implementación)
├── bin/ # Ejecutable compilado
└── README.md 
---

##  Cómo compilar

Abre la terminal desde la raíz del proyecto y ejecuta:


g++ src/*.cpp -o bin/ticket_to_ride.exe -std=c++11

---

## Cómo ejecutar

./bin/ticket_to_ride.exe

## Cómo jugar
1. Jugadores: Ingresa el nombre de los 4 jugadores al inicio.

2. Turnos: Cada jugador, en su turno, puede elegir entre:

    Ver el mapa

    Ver su estado personal

    Reclamar trayecto (requiere cartas del mismo color)

    Robar cartas del mazo o zona visible

    Terminar turno

3. Fin del juego: Cuando un jugador tiene menos de 5 vagones, se termina la partida.

4. Ganador: El que tenga más puntos gana (los puntos se obtienen al reclamar trayectos).

## Mapa de ciudades

Letra	Ciudad
A	Bogotá
B	Medellín
C	Cali
D	Pereira
E	Manizales
F	Tunja
G	Bucaramanga
H	Cartagena
I	Santa Marta
J	Barranquilla

## Colores disponibles para las cartas

Rojo

Azul

Verde

Amarillo

Negro

## Notas técnicas

1. Evita usar using namespace std; en archivos .h. Solo utilízalo en los .cpp.

2. El juego usa códigos ANSI para mostrar colores. Si tu terminal no los soporta bien, prueba con Windows Terminal o WSL.

3. No uses acentos ni caracteres especiales en nombres de ciudades para evitar errores de entrada.
