#include "cola.h"
#include "testing.h"
#include <stdio.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

void pruebas_cola_catedra();

int main(void) {
    /* Ejecuta todas las pruebas unitarias. */
    /*cola_t* cola_crear(void);
	bool cola_esta_vacia(const cola_t *cola);
	bool cola_encolar(cola_t *cola, void* valor);
	void* cola_ver_primero(const cola_t *cola);
	void* cola_desencolar(cola_t *cola);
	void cola_destruir(cola_t *cola, void destruir_dato(void*));*/


    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_cola_alumno();

    #ifdef CORRECTOR
        printf("\n~~~ PRUEBAS CÁTEDRA ~~~\n");
        pruebas_cola_catedra();
    #endif 

    return failure_count() > 0;
}
