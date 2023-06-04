#include "lecturaArchivos.h"

int leerCartas(){
	FILE *archivo;
	archivo = fopen("Listados cartas.csv", "r");
	if (archivo == NULL){
		printf("Error.0\n");
		return 1;
	}
	int read = 0;
	int records = 0;
	do{
		read = fscanf(archivo, "%30[^,], %10[^,], %d, %150[^,],\n", lista_cartas[records].nombre, lista_cartas[records].tipo, &lista_cartas[records].puntos, lista_cartas[records].descripcion);
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

int leerEnemigos(){
	FILE *archivo;
	archivo = fopen("Listas enemigos.csv", "r");
	if (archivo == NULL){
		printf("Error.0\n");
		return 1;
	}
	int read = 0;
	int records = 0;	
	do{
		read = fscanf(archivo, "%10[^,], %d, %5[^,], %120[^,],\n", lista_enemigos[records].nombre, &lista_enemigos[records].vida, lista_enemigos[records].tipo, lista_enemigos[records].descripcion);
		if(read == 4){
			records++;
		}
		else if(records != 4 && !feof(archivo)){
			printf("Error.1\n");
			return 1;
		}
		if(ferror(archivo)){
			printf("Error.2\n");
			return 1;
		}
		
		
	}while(!feof(archivo));
	
	fclose(archivo);
}

int leerPersonajes(){
	FILE *archivo;
	archivo = fopen("Jugadores.csv", "r");
	if (archivo == NULL){
		printf("Error.0\n");
		return 1;
	}
	int read = 0;
	int records = 0;
	do{
		read = fscanf(archivo, "%15[^,], %d, %d, %d\n", lista_personajes[records].nombre, &lista_personajes[records].fuerza, &lista_personajes[records].dureza, &lista_personajes[records].inteligencia);
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