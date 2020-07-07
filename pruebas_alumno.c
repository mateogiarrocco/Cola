#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

#define VALOR_PRUEBA_1 3
#define VALOR_DE_PRUEBA_VOLUMEN 10
#define VALOR_VOLUMEN 10000

int* crear_valor_prueba(int valor){
	int* dato = malloc(sizeof(int));
	*dato = valor;
	return dato;
}

void pruebas_cola_vacia() {
    cola_t* cola = cola_crear();
    print_test("Cola creada correctamente", cola != NULL);
    print_test("El primero de la cola vacia es NULL", cola_ver_primero(cola) == NULL);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("cola no se puede desencolar", cola_desencolar(cola) == NULL);
    cola_destruir(cola, NULL);
    print_test("cola destruida correctamente", cola);
}

void destruir_cola_wrapper(void* pila){
	pila_destruir((pila_t*)pila);
}

void pruebas_destruccion_con_null(int* valor){
	//destruyo la cola sin elementos
	cola_t* cola = cola_crear();
	print_test("Cola creada correctamente", cola);
	cola_encolar(cola, valor);
	print_test("El primero de la cola no es null", cola_ver_primero(cola) == valor);
	print_test("Cola tiene elementos", !cola_esta_vacia(cola));
	cola_desencolar(cola);
	print_test("El primero de la cola vacia es null", cola_ver_primero(cola) == NULL);
	cola_destruir(cola, NULL);
}

void pruebas_destruccion_encolando_pilas(int* valor){
	//Pruebo encolar y destruir(sin desencolar)

	cola_t* cola = cola_crear();
	print_test("La cola no tiene elementos", cola_esta_vacia(cola));
	pila_t* pila1 = pila_crear();
	pila_t* pila2 = pila_crear();
	pila_apilar(pila2, valor);
	cola_encolar(cola, pila1);
	cola_encolar(cola, pila2);
	cola_destruir(cola, destruir_cola_wrapper);
	print_test("Cola destruida correctamente", cola);
}

void pruebas_cola_con_elementos_dinamicos(){
	printf("PRUEBAS COLA CON ELEMENTOS DINAMICOS\n");
	int valor_a_probar = VALOR_PRUEBA_1;
	int* valor = crear_valor_prueba(valor_a_probar);
	pruebas_destruccion_con_null(valor);
	pruebas_destruccion_encolando_pilas(valor);
	free(valor);
}

void pruebas_encolando_null(){
	printf("PRUEBAS ENCOLANDO NULL\n");
	void* valor = NULL;
	cola_t* cola = cola_crear();
	//destruyo la cola sin elementos
	for(int i = 0; i < 10; i ++) cola_encolar(cola, valor);
	print_test("El primero de la cola es null", cola_ver_primero(cola) == NULL);
	print_test("la cola tiene elementos", !cola_esta_vacia(cola));
	for(int i = 0; i < 6; i ++) cola_desencolar(cola);
	print_test("La cola no esta del todo vacia", !cola_esta_vacia(cola));
	for(int i = 0; i < 4; i ++) cola_desencolar(cola);
	print_test("La cola esta vacia", cola_esta_vacia(cola));
	cola_destruir(cola, NULL);

	cola_t* cola_2 = cola_crear();
	//destruyo la cola con NULLs adentro
	for (int i = 0; i < 20; i++) cola_encolar(cola_2, valor);
	for (int i = 0; i < 10; i++) cola_desencolar(cola_2);
	print_test("La cola no esta del todo vacia", !cola_esta_vacia(cola_2));
	cola_destruir(cola_2, free);
	print_test("Cola destruida correctamente", cola_2);
}

void pruebas_volumen(){
	printf("PRUEBAS VOLUMEN\n");
	int valor = VALOR_DE_PRUEBA_VOLUMEN;
	int* primero_cola;
	int* valor_nuevo;
	cola_t* cola = cola_crear();
	print_test("No se puede desencolar", !cola_desencolar(cola));
	print_test("No se puede ver el primero", !cola_ver_primero(cola));
	print_test("La cola esta vacia", cola_esta_vacia(cola));

	bool ok = true;
	int a_encolar[VALOR_VOLUMEN];
	for (int i = 0; i< VALOR_VOLUMEN; i++) a_encolar[i] = i;
	for (int i = 0; i< VALOR_VOLUMEN; i++){
		ok = ok && cola_encolar(cola, &a_encolar[i]);	   
	}
	primero_cola = cola_ver_primero(cola);
	ok = ok && (*primero_cola == 0);
	print_test("Se cumple la invariante de la cola", ok);

	for (int i = 0; i< VALOR_VOLUMEN; i++){
		ok = ok && (cola_ver_primero(cola) == cola_desencolar(cola));  
	}
	print_test("Se cumple la invariante de la COLA", ok);
	print_test("No se puede desencolar", !cola_desencolar(cola));
	print_test("La cola esta vacia", cola_esta_vacia(cola));
	print_test("El primero de la cola es NULL", (!cola_ver_primero(cola)));

	valor_nuevo = crear_valor_prueba(valor);
	cola_encolar(cola, valor_nuevo);
	print_test("La cola no esta vacia", !cola_esta_vacia(cola));
	print_test("El primero de la cola es valor_nuevo", (cola_ver_primero(cola)) == valor_nuevo);
	cola_destruir(cola, free);
}

void pruebas_cola_alumno(){
	pruebas_cola_vacia();
	pruebas_cola_con_elementos_dinamicos();
	pruebas_encolando_null();
	pruebas_volumen();
}