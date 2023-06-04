#ifndef ARBOLH
#define ARBOLH
#include "listas.h"
typedef struct caminos{
	int valor; //Guarda que se encontrara en el camino
	int ubi; //Identificador del nodo
	struct caminos*hijoDer;
	struct caminos*hijoIzq; 
}caminos;

typedef struct arbol{
	caminos*raiz;
}arbol;

caminos*crearNodo(int valor, int ubi);
arbol*crearArbol();

//Mapa del juego
caminos*nodos[21];
//Guarda la ubicacion del jugador
caminos*nodoActual;

#endif