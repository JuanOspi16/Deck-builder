#ifndef CONTINUIDADH
#define CONTINUIDADH
#include "juego.h"
//Encabezados de las funciones que se encargan de guardar y continuar el programa
void nuevoJuego(int*vida, int*cantCartas, int*dinero, deck**inventario, int*personaje, bestiario**bestiario, arbol*arbolCreado);
void guardar(deck*inventario);
int leerDeck(deck**inventario);
void guardarEst(int*vida, int*dinero, int*cantCartas, int*personaje);
int leerEst(int*vida, int*dinero, int*cantCartas, int*personaje);
void guardarEnemigos(bestiario*enemigos);
int leerBestiario(bestiario**enemigos);

#endif
