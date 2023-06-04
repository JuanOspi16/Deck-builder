#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "continuidad.h"

int main(){
	srand(time(NULL));
	leerCartas();
	leerEnemigos();
	leerPersonajes();
	int seleccionMenu; 
	int personaje; //Variable que indica el personaje elegido
	int cont=0;
	int dinero=0;
	int cantCartas=0; 
	int vida=350;
	deck*carta=NULL;
	deck**pCarta=&carta; //Puntero para la lista enlazada del deck
	arbol*arbolCreado=crearArbol();
	nodoActual=arbolCreado->raiz; //Indica la posicion dentro de los caminos o arbol
	bestiario*enemigos=NULL;
	bestiario**pEnemigos=&enemigos; //Puntero para el bestiario
	int*pDinero=&dinero;
	int*pVida=&vida;
	int*pCartas=&cantCartas;
	int*pPersonaje=&personaje; 
	int flag;
	do{
		flag=leerEst(pVida, pDinero, pCartas, pPersonaje); //Retorna 0 si existe un archivo
		banderaEspecial=0;
		if(flag==0){
			printf("0.Salir\n1.Juego Nuevo\n2.Continuar\n");
			scanf("%d", &seleccionMenu);
			if(seleccionMenu==1){
				nuevoJuego(pVida, pCartas, pDinero, pCarta, pPersonaje, pEnemigos, arbolCreado);
				nodoActual=nodos[0];
			}
			else if(seleccionMenu==2){
				nodoActual=nodos[ubicacion];
				enemigos=NULL;
				carta=NULL;
				leerDeck(pCarta);
				leerBestiario(pEnemigos);
				if(vida<=0){ //Si el jugador acaba de perder toda su vida en batalla, le da un respiro mas
					vida=200;
				}
			}
			if(seleccionMenu==1 || seleccionMenu==2){
				menuDeJuego(pVida, pCartas, pDinero, pCarta, pPersonaje, pEnemigos, arbolCreado);
			}
		}else{
			printf("0.Salir\n1.Juego Nuevo\n");
			scanf("%d", &seleccionMenu);
			if(seleccionMenu==1){
				nuevoJuego(pVida, pCartas, pDinero, pCarta, pPersonaje, pEnemigos, arbolCreado);
				menuDeJuego(pVida, pCartas, pDinero, pCarta, pPersonaje, pEnemigos, arbolCreado);
			}
		}
	}while(seleccionMenu!=0); 
}
