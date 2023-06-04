#include "arbol.h"

caminos*crearNodo(int valor, int ubi){
	caminos*nuevoNodo=(caminos*)malloc(sizeof(caminos));
	//Indica si el destino es una de las batallas, tienda, o descanso
	nuevoNodo->valor=valor;
	//Le da un identificador al nodo que permite volver a el
	nuevoNodo->ubi=ubi;
	nuevoNodo->hijoDer=NULL;
	nuevoNodo->hijoIzq=NULL;
}

arbol*crearArbol(){
	arbol*nuevoArbol=(arbol*)malloc(sizeof(arbol));
	caminos*nuevo;
	//Crea el camino y lo que contendra cada nodo o destino
	//0 para el origen, 1, 2, y 3 para batallas comunes, elite y jefes, y 4 y 5 para tienda y descanso
	for(int i=0; i<21; i++){
		if(i==0){
			nuevo = crearNodo(0, i);
            nodos[i] = nuevo;
		}else if(i>0 && i<=5){
			nuevo=crearNodo(1, i);
			nodos[i]=nuevo;
		}else if(i>5 && i<=10){
			nuevo=crearNodo(2, i);
			nodos[i]=nuevo;
		}else if(i>10 && i<=12){
			nuevo=crearNodo(3, i);
			nodos[i]=nuevo;
		}else if(i>12 && i<=16){
			nuevo=crearNodo(4, i);
			nodos[i]=nuevo;
		}else{
			nuevo=crearNodo(5, i);
			nodos[i]=nuevo;
		}
	}
	//Crea las conexiones del arbol
	nuevoArbol->raiz=nodos[0];
	nodos[0]->hijoIzq=nodos[1]; nodos[0]->hijoDer=nodos[17];
	nodos[1]->hijoIzq=nodos[6]; nodos[1]->hijoDer=nodos[13];
	nodos[2]->hijoIzq=nodos[12]; nodos[2]->hijoDer=nodos[15];
	nodos[3]->hijoIzq=nodos[12]; nodos[3]->hijoDer=nodos[12];
	nodos[4]->hijoIzq=nodos[12]; nodos[4]->hijoDer=nodos[20];
	nodos[5]->hijoIzq=nodos[20]; nodos[5]->hijoDer=nodos[12];
	nodos[6]->hijoIzq=nodos[2]; nodos[6]->hijoDer=nodos[18];
	nodos[7]->hijoIzq=nodos[5]; nodos[7]->hijoDer=nodos[14];
	nodos[8]->hijoIzq=nodos[19]; nodos[8]->hijoDer=nodos[12];
	nodos[9]->hijoIzq=nodos[16]; nodos[9]->hijoDer=nodos[12];
	nodos[10]->hijoIzq=nodos[12]; nodos[10]->hijoDer=nodos[12];
	nodos[11]->hijoIzq=nodos[9]; nodos[11]->hijoDer=nodos[4];
	nodos[13]->hijoIzq=nodos[3]; nodos[13]->hijoDer=nodos[8];
	nodos[14]->hijoIzq=nodos[10]; nodos[14]->hijoDer=nodos[12];
	nodos[15]->hijoIzq=nodos[12]; nodos[15]->hijoDer=nodos[12];
	nodos[16]->hijoIzq=nodos[12]; nodos[16]->hijoDer=nodos[12];
	nodos[17]->hijoIzq=nodos[11]; nodos[17]->hijoDer=nodos[7];
	nodos[18]->hijoIzq=nodos[12]; nodos[18]->hijoDer=nodos[12];
	nodos[19]->hijoIzq=nodos[12]; nodos[19]->hijoDer=nodos[12];
	nodos[20]->hijoIzq=nodos[12]; nodos[20]->hijoDer=nodos[12];
	return nuevoArbol;
}
