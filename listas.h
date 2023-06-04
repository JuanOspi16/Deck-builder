#ifndef LISTASH
#define LISTASH

#include "lecturaArchivos.h"

typedef struct deck{
	cartas carta;
	struct deck*pSgte;
}deck;

typedef struct bestiario{
	enemigo enemigos;
	struct bestiario*pSgte;
}bestiario;

deck*insertarCartas(deck*cabezaLista, cartas agregarCarta);
deck*eliminarElemento(deck*cabezaLista, int seleccion);
cartas miniDeck(deck*inventario, int*cantCartas);
cartas generarCarta();
bestiario*insertarEnemigo(bestiario*cabezaLista, enemigo agregarEnemigo);
void imprimirDeck(deck*carta);
void imprimirBestiario(bestiario*cabezaLista);
deck*agregarOrden(deck*cabezaLista, cartas agregarCarta);
bestiario*agregarOrdenEnemigo(bestiario*cabezaLista, enemigo agregarEnemigo);

#endif