#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo {
    void* dato;
    struct nodo* prox;
} nodo_t;

typedef struct cola {
    nodo_t* primero;
    nodo_t* ultimo;
} cola_t;

nodo_t* nodo_crear(void* valor){
	nodo_t* nodo = malloc(sizeof(nodo_t)); 
	if (!nodo) return NULL; 
	nodo->dato = valor;
	nodo->prox = NULL; 
	return nodo; 
}

cola_t* cola_crear(){
	cola_t* cola = malloc(sizeof(cola_t));
	if(!cola) return NULL;
	cola->primero = NULL;
	cola->ultimo = NULL;
	return cola;
}
bool cola_esta_vacia(const cola_t *cola){
	return !cola->primero;
}

void* cola_desencolar(cola_t *cola){
	if(cola_esta_vacia(cola)) return NULL;
	void* valor = cola->primero->dato;
	nodo_t* nodo_aux = cola->primero;
	cola->primero = cola->primero->prox;
	free(nodo_aux);
	return valor;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	void* dato_aux;
	while(!cola_esta_vacia(cola)){
		dato_aux = cola_desencolar(cola);
		if(destruir_dato) destruir_dato(dato_aux);
	}
	free(cola);
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* nodo = nodo_crear(valor);
	if(!nodo) return false;
	if(cola_esta_vacia(cola)) cola->primero = nodo;
	else cola->ultimo->prox = nodo; 
	cola->ultimo = nodo;
	return true;
}
void* cola_ver_primero(const cola_t *cola){
	if(cola_esta_vacia(cola)) return NULL;
	return cola->primero->dato;
}