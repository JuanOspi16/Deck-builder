#include "listas.h"

deck*insertarCartas(deck*cabezaLista, cartas agregarCarta){
	//Inserta cartas en la cabeza de la lista
	deck*cartaNueva=(deck*)malloc(sizeof(deck));
	if (cartaNueva == NULL){
		printf("No fue posible reservar memoria\n");
	}else{
		cartaNueva->carta=agregarCarta;
	}
	cartaNueva->pSgte=cabezaLista;
	cabezaLista=cartaNueva;
	return cabezaLista;
}

//Elimina la carta en el minideck
deck*eliminarElemento(deck*cabezaLista, int seleccion){
	deck*aux=cabezaLista;
	deck*temp=NULL;
	int cont=0;
	if(aux!=NULL){
		//En caso de que se quiera eliminar el primer elemento del deck
		if(seleccion==0){ 
			temp=aux->pSgte;
			free(aux);
			cabezaLista=temp;
		}else{
			temp=aux->pSgte;
			while(temp!=NULL && cont<seleccion){ 
				//Antes de que aux cambie, temp toma su valor
				temp=aux;
				aux = aux -> pSgte;
				cont++; 
			}
			//En caso de que se quiera eliminar el ultimo elemento
			if(aux->pSgte==NULL){ 
				free(aux);
				temp->pSgte=NULL;
			}else{ 
				//Cualquier elemento del deck menos el primero y ultimo
				temp->pSgte=aux->pSgte; 
				free(aux);
			}
		}
	}
	return cabezaLista;
}

cartas miniDeck(deck*inventario, int*cantCartas){
	deck*aux=(deck*)malloc(sizeof(deck));
	int numeroAleatorio;
	int bandera=0, cont=0;
	aux=inventario;
	//Elige las cartas del inventario, y la retorna
	numeroAleatorio=rand()%(*cantCartas);
	for(int j=0; j<numeroAleatorio; j++){
		aux=aux->pSgte;
	}
	return aux->carta;
}

cartas generarCarta(){
	int numAleatorio=rand()%15;
	//Elige aleatoriamente una carta de las predefinidas, es decir, del arreglo
	cartas agregarCarta;
	agregarCarta=lista_cartas[numAleatorio];
	return agregarCarta;	
}

bestiario*insertarEnemigo(bestiario*cabezaLista, enemigo agregarEnemigo){
	bestiario*nuevoEnemigo=(bestiario*)malloc(sizeof(bestiario));
	if (nuevoEnemigo == NULL){
		printf("No fue posible reservar memoria\n");
	}else{
		nuevoEnemigo->enemigos=agregarEnemigo;
	}
	nuevoEnemigo->pSgte=cabezaLista;
	cabezaLista=nuevoEnemigo;
	return cabezaLista;
}

void imprimirDeck(deck*carta){
	deck*temp=(deck*)malloc(sizeof(deck));
	temp=carta;
	int cont=0;
	while(temp!=NULL){
		printf("\n%d.Nombre:    %s\n",cont+1, temp->carta.nombre);
		printf("Categoria:   %s\n", temp->carta.tipo);
		printf("Puntos:      %d\n", temp->carta.puntos);
		printf("Descripcion: %s\n", temp->carta.descripcion);
		temp=temp->pSgte;		
		cont++;
	}
} 

void imprimirBestiario(bestiario*cabezaLista){
	bestiario*temp=cabezaLista;
	int cont=0; 
	if(temp==NULL){
		printf("\nNo has derrotado ningun enemigo aun.\n");
	}else{
		printf("\nEn tu trayectoria has derrotado a: \n");
		while(temp!=NULL){
			printf("\n%d.Nombre: %s\n",cont+1, temp->enemigos.nombre);
			printf("Tipo: %s\n", temp->enemigos.tipo);
			printf("Vida: %d\n", temp->enemigos.vida);
			printf("Descripcion: %s\n", temp->enemigos.descripcion);
			temp=temp->pSgte;		
			cont++;
		}
	}
}  

bestiario*agregarOrdenEnemigo(bestiario*cabezaLista, enemigo agregarEnemigo){
	bestiario*nuevoNodo=(bestiario*)malloc(sizeof(bestiario));
	nuevoNodo->enemigos=agregarEnemigo;
	nuevoNodo->pSgte=NULL;
	if(cabezaLista==NULL){
		cabezaLista=nuevoNodo;
	}else{
		if(strcmp(cabezaLista->enemigos.nombre, nuevoNodo->enemigos.nombre)>0){
			cabezaLista=insertarEnemigo(cabezaLista, agregarEnemigo);
		}else{
			bestiario*anterior=cabezaLista;
			bestiario*sig=cabezaLista->pSgte;
			while(sig!=NULL && strcmp(sig->enemigos.nombre, nuevoNodo->enemigos.nombre)<0){
				anterior=sig;
				sig=sig->pSgte;
			}
			nuevoNodo->pSgte=sig;
			anterior->pSgte=nuevoNodo;
		}
	}
	return cabezaLista;
}

deck*agregarOrden(deck*cabezaLista, cartas agregarCarta){
	deck*nuevoNodo=(deck*)malloc(sizeof(deck));
	nuevoNodo->carta=agregarCarta;
	nuevoNodo->pSgte=NULL;
	if(cabezaLista==NULL){
		//Lista vacia
		cabezaLista=nuevoNodo;
	}else{
		//strcmp devuelve 0 si son iguales, >0 si el primero va despues en ASCII, y <0 en caso contrario
		if(strcmp(cabezaLista->carta.nombre, nuevoNodo->carta.nombre)>0){
			//Si el primer elemento va antes que el segundo, lo inserta por la cabeza
			//Teniendo en cuenta que los sgtes ya estan ordenados
			cabezaLista=insertarCartas(cabezaLista, agregarCarta);
		}else{
			deck*anterior=cabezaLista;
			deck*sig=cabezaLista->pSgte;
			//sig avanza como auxiliar hasta que encuentre un elemento que vaya despues que el nuevo alfabeticamente
			while(sig!=NULL && strcmp(sig->carta.nombre, nuevoNodo->carta.nombre)<0){
				anterior=sig; //Guarda el nodo anterior al aux
				sig=sig->pSgte;
			}
			//El nuevo nodo apunta al primero que encuentre que sea mayor que el en cod ASCII
			nuevoNodo->pSgte=sig;
			//El nodo ubicado antes que el aux ahora apunta al nuevo
			anterior->pSgte=nuevoNodo;
		}
	}
	return cabezaLista;
}