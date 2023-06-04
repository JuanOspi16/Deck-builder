#include "juego.h"

void caminar(int*vida, int*cantCartas, int*dinero, deck**inventario, int*personaje, bestiario**enemigos, arbol*camino){
	int seleccion, opcionA, opcionB;
	int flag=0;
	//Arreglo para mostrar la opcion del nodo
	char caminosPosibles[6][30]={"Inicio", "Batalla Comun", "Batalla contra enemigo elite", "Batalla contra un jefe", "Descanso", "Tienda"};
	//El primer numero indica los puntos de la accion, y el segundo un mult que depende del rango
	acciones ataquesEnemigosComunes[6]={
		{"Torbellino", "Ataque", 3, 6},
		{"Aliento toxico", "Ataque", 2, 6},
		{"Hechizo acido", "Ataque", 4, 6},
		{"Tormenta de fuego", "Ataque", 5, 6},
		{"Pocima de sanacion", "Magia", 2, 6},
		{"Angel de la muerte", "Magia", 4, 6},
	};
	acciones ataquesEnemigosElite[6]={
		{"Flechas igneas", "Ataque", 4, 8},
		{"Paralizacion", "Ataque", 2, 8},
		{"Descarga electrica", "Ataque", 5, 8},
		{"Puno de guerra", "Ataque", 3, 8},
		{"Sanacion heroica", "Magia", 2, 8},
		{"Curacion celestial", "Magia", 4, 8},
	};
	acciones ataquesEnemigosJefes[6]={
		{"Asteroides", "Ataque", 3, 10},
		{"Golpe nuclear", "Ataque", 4, 10},
		{"Lanzallamas", "Ataque", 5, 10},
		{"Lluvia de clavos", "Ataque", 2, 10},
		{"Ayuda de Asclepio", "Magia", 5, 10},
		{"Agua bendita", "Magia", 3, 10},
	};
	do{
		//Le muestran al usuario el enemigo que se encontraran al elegir el camino
		int aleatorio_normal=rand()%15;
		int aleatorio_epico=rand()%10+15;
		int aleatorio_jefe=rand()%5+25;
		//Almacenan las variables de los posibles destinos para ejecutar la funcion respectiva
		opcionA=nodoActual->hijoIzq->valor;
		opcionB=nodoActual->hijoDer->valor;
		
		printf("\n0.Salir\n1.%s", caminosPosibles[opcionA]);
		//Verifica si en los caminos hay batallas para imprimir a cual se encontrarian si lo eligen
		if(opcionA==1){
			printf("\n  Te encontraras con: %s, %s", lista_enemigos[aleatorio_normal].nombre, lista_enemigos[aleatorio_normal].descripcion);
		}else if(opcionA==2){
			printf("\n  Te encontraras con: %s, %s", lista_enemigos[aleatorio_epico].nombre, lista_enemigos[aleatorio_epico].descripcion);
		}else if(opcionA==3){
			printf("\n  Te encontraras con: %s, %s", lista_enemigos[aleatorio_jefe].nombre, lista_enemigos[aleatorio_jefe].descripcion);
		}
		printf("\n2.%s", caminosPosibles[opcionB]);
		if(opcionB==1){
			printf("\n  Te encontraras con: %s, %s", lista_enemigos[aleatorio_normal].nombre, lista_enemigos[aleatorio_normal].descripcion);
		}else if(opcionB==2){
			printf("\n  Te encontraras con: %s, %s", lista_enemigos[aleatorio_epico].nombre, lista_enemigos[aleatorio_epico].descripcion);
		}else if(opcionB==3){
			printf("\n  Te encontraras con: %s, %s", lista_enemigos[aleatorio_jefe].nombre, lista_enemigos[aleatorio_jefe].descripcion);
		}
		printf("\n\nElige tu destino: ");
		scanf("%d", &seleccion);
		if(seleccion!=0){
			//Si elige la opcion 1 se dirige a la izquierda, y el 2 a la derecha
			if(seleccion==1){
				seleccion=opcionA;
				nodoActual=nodoActual->hijoIzq;
			}else{
				seleccion=opcionB;
				nodoActual=nodoActual->hijoDer;
			}
			//Almacena el identificador del nodo en el que se encuentra el jugador actualmente
			ubicacion=nodoActual->ubi;
			//seleccion tomo el valor del nodo o camino elegido para que aqui se revise en la condicion
			switch(seleccion){
				case 1:batallas(aleatorio_normal, vida, dinero, cantCartas, inventario, personaje, enemigos, ataquesEnemigosComunes);
					break;
				case 2:batallas(aleatorio_epico, vida, dinero, cantCartas, inventario, personaje, enemigos, ataquesEnemigosElite);
					break;
				case 3:batallas(aleatorio_jefe, vida, dinero, cantCartas, inventario, personaje, enemigos, ataquesEnemigosJefes);
					break;
				case 4: sitioDescanso(vida);
					break;
				case 5:tienda(dinero, inventario, cantCartas);
					break;
				default:
					break;
			}
		}
	}while(banderaEspecial==0 && seleccion!=0);
}

void tienda(int*dinero, deck**carta, int*cantCartas){
	cartas cartaSeleccion;
	int contador=0, seleccion;
	int precio, i;
	while(contador<TAM){
		//Imprime las 15 cartas existentes
		printf("\n%d.", contador+1);
		printf("Nombre: %s\n", lista_cartas[contador].nombre);
		printf("Categoria: %s\n", lista_cartas[contador].tipo);
		printf("Descripcion: %s\n", lista_cartas[contador].descripcion);
		precio=(lista_cartas[contador].puntos)*TAM;
		printf("Precio: $%d\n", precio);
		contador++;
	}
	do{
		printf("\nDinero actual: %d\n", *dinero);
		printf("\n0.Salir\nCual carta desea comprar?: ");
		scanf("%d", &seleccion);
		if(seleccion>0){
			i=seleccion-1;
			precio=(lista_cartas[i].puntos)*8;
			cartaSeleccion= lista_cartas[i];
			if((*dinero)<precio){
				printf("No tienes dinero suficiente\n");
			}else{
				(*carta)=agregarOrden((*carta), cartaSeleccion);
				(*dinero)-=precio;
				(*cantCartas)=(*cantCartas)+1;
			}
		}
	}while(seleccion!=0);
}

void batallas(int numEnemigo, int*vida, int*dinero, int*cantCartas, deck**inventario, int*personaje, bestiario**enemigos, acciones arreglo[]){
	deck*mini_Deck=(deck*)malloc(sizeof(deck));
	enemigo villano=lista_enemigos[numEnemigo]; //Asigna el enemigo al que se enfrentara
	acciones accion;
	cartas cartaNueva;
	int seleccionJugador, elegido, bandera, seleccion; 
	int vidaEnemigo=villano.vida;
	int ataqueEnemigo=0, defensaJugador=0, ataqueJugador=0, puntos=5;
	int*pPuntos=&puntos;
	int*pDefensa=&defensaJugador;
	int*pVidaEnemigo=&vidaEnemigo;
	do{ //Determina el final de la batalla
		 //Reinicia el mini deck cuando empiece el turno
		mini_Deck=NULL;
		for(int i=0; i<5; i++){
			cartaNueva=miniDeck((*inventario), cantCartas);
			mini_Deck=agregarOrden(mini_Deck, cartaNueva); //Crea el mini deck
		}
		puntos=5;
		defensaJugador=0;
		seleccion=rand()%6; //Indica la posicion del ataque en el arreglo de ataques
		accion=arreglo[seleccion]; //Determina la accion que usara el enemigo 
		imprimirDeck(mini_Deck);
		printf("\n%s realizara %s de %d puntos de tipo %s", villano.nombre, accion.nombre, accion.ptos*accion.multiplicador, accion.tipo);
		//determina el final del turno
		do{ 
			printf("\n0.Terminar turno\nQue desea usar?: ");
			scanf("%d", &seleccionJugador);
			if(seleccionJugador!=0){
				elegido=seleccionJugador-1; //Sirve en la sgte funcion como cond de parada del ciclo que recorre el minideck
				bandera=interpretarCarta(mini_Deck, elegido, pPuntos, (*personaje), vida, pDefensa, pVidaEnemigo);
				if(bandera==1){
					//Elimina la carta solo si tenia los puntos suficientes para usarla
					mini_Deck=eliminarElemento(mini_Deck, elegido); 
				}
				if(puntos>0){
					imprimirDeck(mini_Deck);
				}
				printf("\nPuntos: %d", puntos);
				imprimirEstadisticas((*vida), pVidaEnemigo, villano.nombre);
			}
		}while(seleccionJugador!=0 && puntos>0 && vidaEnemigo>0);//Se acaba el turno al gastar los puntos
		if(vidaEnemigo>0){
			free(mini_Deck);
			printf("\n%s uso %s de tipo %s", villano.nombre, accion.nombre, accion.tipo);
			//Cond para conocer el tipo de accion del enemigo
			//El efecto de la accion enemiga se mult por un numero que depende del rango de este
			if(strcmp("Ataque", accion.tipo)==0){
				ataqueEnemigo=((accion.ptos)*accion.multiplicador)-defensaJugador; //Si el jugador uso carta defendiva se le resta al ataque enemigo
				if(ataqueEnemigo<0){
					ataqueEnemigo=0;
				}
				(*vida)=(*vida)-ataqueEnemigo;
				printf("\nEl ataque enemigo te causo %d de danio", ataqueEnemigo);
			}else{
				vidaEnemigo+=(accion.ptos)*(accion.multiplicador);
				printf("\nEl enemigo se curo %d puntos de vida", (accion.ptos)*(accion.multiplicador));
				if(vidaEnemigo>villano.vida){
					vidaEnemigo=villano.vida;
				}
			}
			imprimirEstadisticas((*vida), pVidaEnemigo, villano.nombre);	
		}
	}while((*vida)>0 && vidaEnemigo>0); //Se acaba la batalla
	
	if((*vida)<=0){
		printf("\nHas perdido el combate");
		banderaEspecial=1; //Permite devolver al usuario hasta el menu inicial
	}else{
		(*enemigos)=agregarOrdenEnemigo((*enemigos), villano);
		printf("\nFelicidades! Ganaste el combate");
		//El multiplicador del arreglo de ataques enemigos determina tambien la cant de dinero recompensada
		(*dinero)=(*dinero)+(arreglo[0].multiplicador*4);
		printf("\nGanaste %d monedas, ahora tienes %d monedas\n", (arreglo[0].multiplicador*4), (*dinero));
		elegirCartas(inventario, cantCartas);
	}
}

void menuDeJuego(int*vida, int*cantCartas, int*dinero, deck**inventario, int*personaje, bestiario**enemigos, arbol*camino){
	int seleccionMenu;
	do{
		printf("\n1.Caminar\n2.Deck\n3.Bestiario\n4.Guardar\n5.Salir\nSelecciona: ");
		scanf("%d", &seleccionMenu);
		switch(seleccionMenu){
			case 1:caminar(vida, cantCartas, dinero, inventario, personaje, enemigos, camino);
				break;
			case 2: imprimirDeck((*inventario));
				break;
			case 3:imprimirBestiario((*enemigos));
				break;
			case 4: //Guarda el progreso en archivos txt 
				guardarEst(vida, dinero, cantCartas, personaje);
				guardar((*inventario));
				guardarEnemigos((*enemigos));
				printf("\nSe guardo correctamente tu progreso");
				break;
			case 5:
				printf("\nSaliendo del menu de juego...\n");
				break;
			default:
				break;
		}
	}while(seleccionMenu!=5 && banderaEspecial==0);	
}

void imprimirEstadisticas(int vidaJugador, int*vidaEnemigo, char*nombreEnemigo){
	if((*vidaEnemigo)<0){
		(*vidaEnemigo)=0;
	}
	printf("\n\nVida jugador: %d\n", vidaJugador);
	printf("\nNombre: %s\nVida: %d\n", nombreEnemigo, (*vidaEnemigo));
}

//Realiza la accion dependiendo del tipo de la carta
int interpretarCarta(deck*carta, int seleccion, int*puntos, int personaje, int*vida, int*defensa, int*vidaEnemigo){
	deck*aux=(deck*)malloc(sizeof(deck));
	aux=carta;
	int bandera=1;
	int accion;
	int multiplicador;
	for(int i=0; i<seleccion; i++){
		aux=aux->pSgte;
	}
	//El sistema consiste en multiplicar los ptos de la carta por la caracteristica respectiva del personaje dividido entre 10
	//Esto permite que haya influencia de la caracteristica del personaje sobre la accion de la carta
	if(((*puntos)-aux->carta.puntos)<0){
		printf("\nNo tienes puntos suficientes");
		bandera=0;
	}else{
		printf("\n\nUsaste %s de tipo %s\n", aux->carta.nombre, aux->carta.tipo);
		bandera=1;
		(*puntos)=(*puntos)-aux->carta.puntos; //Resta de los puntos del turno, los puntos de la carta
		if(strcmp("Ataque", aux->carta.tipo)==0){
			multiplicador=lista_personajes[personaje].fuerza; //Multiplicador toma el valor de la caract del personaje dependiendo de la carta
			accion=(aux->carta.puntos)*(multiplicador/10);
			printf("\nLe quitaste %d puntos de vida\n", accion);
			(*vidaEnemigo)=(*vidaEnemigo)-accion;
		}
		else if(strcmp("Defensa", aux->carta.tipo)==0){
			multiplicador=lista_personajes[personaje].dureza;
			(*defensa)=(*defensa)+(aux->carta.puntos)*(multiplicador/10);
			printf("\nSe le restara %d puntos al proximo ataque enemigo", (*defensa));
		}
		else{
			//Las de habilidad solo permiten curar la vida
			multiplicador=lista_personajes[personaje].inteligencia;
			accion=(aux->carta.puntos)*(multiplicador/10);
			(*vida)=(*vida)+accion;
			printf("\nTu vida aumentara %d puntos", accion);
			if((*vida)>350){
				(*vida)=350;
			}
		}
	}
	return bandera; //Retorna 0 si no se pudo usar la carta y 1 en caso contrario
}

//Se implementa cuando se derrota un enemigo
void elegirCartas(deck**inventario, int*cantCartas){
	cartas aux;
	cartas cartaElegida;
	int arreglo[3]={}; //Guarda los numeros aleat generados
	int numeroElegido;
	int numero, seleccion;
	//Guarda el numero aleatorio (el indice de la carta) en un arreglo para facilitar la eleccion 
	for(int i=0; i<3; i++){
		numero=rand()%TAM; //numero que muestra una carta aleatoria
		aux=lista_cartas[numero]; 
		arreglo[i]=numero; //Guarda el numero en un arreglo para facilitar la eleccion
		printf("\n%d. Nombre: %s\nTipo: %s\nPuntos: %d\nDescripcion: %s\n", i+1, aux.nombre, aux.tipo, aux.puntos, aux.descripcion);
	}
	printf("Elige una carta: ");
	scanf("%d", &seleccion);
	seleccion-=1;
	//seleccion funciona como el indice del arreglo de los numeros aleatorios
	numeroElegido=arreglo[seleccion]; //Dependiendo de seleccion, numero elegido toma el valor de esa posicion en el arreglo de num aleat
	cartaElegida=lista_cartas[numeroElegido]; 
	(*inventario)= agregarOrden((*inventario), cartaElegida);
	(*cantCartas)=(*cantCartas)+1;
}

void sitioDescanso(int*vida){
	*vida=350;
	printf("\nHas recuperado toda tu vida. Vida: %d\n", *vida);
}