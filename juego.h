#ifndef JUEGOH
#define JUEGOH
#include "arbol.h"
#include "continuidad.h"

typedef struct accionesEnemigos{
	char*nombre;
	char*tipo;
	int ptos;
	int multiplicador;
}acciones;

void caminar(int*vida, int*cantCartas, int*dinero, deck**inventario, int*personaje, bestiario**enemigos, arbol*camino);
void tienda(int*dinero, deck**carta, int*cantCartas);
void batallas(int numEnemigo, int*vida, int*dinero, int*cantCartas, deck**inventario, int*personaje, bestiario**enemigos, acciones arreglo[]);
void menuDeJuego(int*vida, int*cantCartas, int*dinero, deck**inventario, int*personaje, bestiario**enemigos, arbol*camino);
void imprimirEstadisticas(int vidaJugador, int*vidaEnemigo, char*nombreEnemigo);
int interpretarCarta(deck*carta, int seleccion, int*puntos, int personaje, int*vida, int*defensa, int*vidaEnemigo);
void elegirCartas(deck**inventario, int*cantCartas);
void sitioDescanso(int*vida);

#endif