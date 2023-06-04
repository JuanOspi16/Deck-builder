#ifndef LECTURAH
#define LECTURAH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 15
#define TAM1 30
#define TAM2 3

typedef struct cartas{
	char nombre[20];
	char tipo[10];
	int puntos;
	char descripcion[150];
}cartas;

typedef struct enemigos{
	char nombre[10];
	int vida;
	char tipo[10];
	char descripcion[120];
}enemigo;

typedef struct personajes{
	char nombre[15];
	int fuerza;
	int dureza;
	int inteligencia;
}personajes;

int leerCartas();
int leerEnemigos();
int leerPersonajes();

personajes lista_personajes[TAM2];
enemigo lista_enemigos[TAM1];
cartas lista_cartas[TAM];

int banderaEspecial;
int ubicacion;

#endif