#include "continuidad.h" 

//Reinicia todos los valores, listas, etc
void nuevoJuego(int*vida, int*cantCartas, int*dinero, deck**inventario, int*personaje, bestiario**bestiario, arbol*arbolCreado){
	(*vida)=350;
	(*dinero)=0;
	(*bestiario)=NULL;
	(*inventario)=NULL;
	(*cantCartas)=0;
	nodoActual=arbolCreado->raiz;
	printf("\nSeleccione un personaje: ");
	for(int j=0; j<TAM2; j++){
		printf("\n%d.Nombre: %s\nFuerza: %d\nDureza: %d\nInteligencia: %d\n\n", j+1, lista_personajes[j].nombre, lista_personajes[j].fuerza, lista_personajes[j].dureza, lista_personajes[j].inteligencia);
	}
	printf("Seleccion: ");
	scanf("%d", &(*personaje));
	(*personaje)=(*personaje)-1;
	printf("\nTu deck inicial es: ");
	for(int i=0; i<5; i++){
		(*cantCartas)=(*cantCartas)+1;
		(*inventario)=agregarOrden((*inventario), generarCarta());
	}
	imprimirDeck((*inventario));
}

void guardar(deck*inventario){
	//Guarda el deck
	deck*aux=(deck*)malloc(sizeof(deck));
	FILE*archivo;
	archivo=fopen("Registros.csv", "w");
	if(archivo==NULL){
		printf("\nError al crear el archivo");
	}
	aux=inventario;
	while(aux!=NULL){
		fprintf(archivo, "%s, %s, %d, %s,\n", aux->carta.nombre, aux->carta.tipo, aux->carta.puntos, aux->carta.descripcion);
		aux=aux->pSgte;
	}
	fclose(archivo);
}

int leerDeck(deck**inventario){
	FILE *archivo;
	archivo = fopen("Registros.csv", "r");
	if (archivo == NULL){
		printf("Error.0\n");
		return 1;
	}
	int read = 0;
	int records = 0;
	cartas carta;
	do{
		
		read = fscanf(archivo, "%30[^,], %10[^,], %d, %150[^,],\n", carta.nombre, carta.tipo, &carta.puntos, carta.descripcion);
		(*inventario)=agregarOrden((*inventario), carta);
		if(read == 4){
			records++;
		}
		else if(records != 4 && !feof(archivo)){
			printf("Error.1\n");
			return 1; 
		}
		else if(ferror(archivo)){
			printf("Error.2\n");
			return 1;
		}
		
	}while(!feof(archivo));
	
	fclose(archivo);
}

void guardarEst(int*vida, int*dinero, int*cantCartas, int*personaje){
	//Guarda la vida, el dinero, la cantidad de cartas, el personaje elegido y la ubicacion
	FILE*archivo;
	archivo=fopen("Estadisticas.csv", "w");
	if(archivo==NULL){
		printf("\nError al crear el archivo");
	}
	fprintf(archivo, "%d, %d, %d, %d, %d,", (*vida), (*dinero), (*cantCartas), (*personaje), ubicacion);
	fclose(archivo);
}

int leerEst(int*vida, int*dinero, int*cantCartas, int*personaje){
	FILE*archivo=fopen("Estadisticas.csv", "r");
	if (archivo == NULL){
		return 1;
	}
	int read = 0;
	int records = 0;
	cartas carta;
	do{	
		read = fscanf(archivo, "%d, %d, %d, %d, %d,\n", &(*vida), &(*dinero), &(*cantCartas), &(*personaje), &ubicacion);
		if(read == 5){
			records++;
			return 0;
		}
		else if(records != 5 && !feof(archivo)){
			printf("Error.1\n");
			return 1; 
		}
		else if(ferror(archivo)){
			printf("Error.2\n");
			return 1;
		}
		
	}while(!feof(archivo));
	
	fclose(archivo);
}

void guardarEnemigos(bestiario*enemigos){
	bestiario*aux=(bestiario*)malloc(sizeof(bestiario));
	FILE*archivo;
	archivo=fopen("Registros enemigos.csv", "w");
	if(archivo==NULL){
		printf("\nError al crear el archivo");
	}
	aux=enemigos;
	while(aux!=NULL){
		fprintf(archivo, "%s, %d, %s, %s,\n", aux->enemigos.nombre, aux->enemigos.vida, aux->enemigos.tipo, aux->enemigos.descripcion);
		aux=aux->pSgte;
	}
	fclose(archivo);
}

int leerBestiario(bestiario**enemigos){
	FILE *archivo;
	archivo = fopen("Registros enemigos.csv", "r");
	if (archivo == NULL){
		printf("Error.0\n");
		return 1;
	}
	int read = 0;
	int records = 0;
	enemigo enem;
	do{
		//Lee linea por linea y lo almacena en la variable enem
		read = fscanf(archivo, "%10[^,], %d, %10[^,], %120[^,],\n", enem.nombre, &enem.vida, enem.tipo, enem.descripcion);
		(*enemigos)=agregarOrdenEnemigo((*enemigos), enem);
		if(read == 4){
			records++;
		}
		else if(records != 4 && !feof(archivo)){
			printf("Error.1\n");
			return 1; 
		}
		else if(ferror(archivo)){
			printf("Error.2\n");
			return 1;
		}
		
	}while(!feof(archivo));
	
	fclose(archivo);
}