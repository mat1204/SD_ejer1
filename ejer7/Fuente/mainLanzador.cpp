/*
 * mainLanzador.cpp
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */


#include "Definiciones.h"
#include "ColaComponentes.h"

#include <string.h>
#include <stdlib.h>



void inicializar();
void lanzar();
void limpiar();


int main(int argc, char** argv) {

	SalidaPorPantalla::instancia().etiqueta("Lanzador");

	if (strcmp(argv[1], "-i") == 0  || argc == 1) {
		inicializar();
		lanzar();
	}
	else if (strcmp(argv[1], "-t") == 0) {
		limpiar();
	}
	else {
		SalidaPorPantalla::instancia().error("Sin argumentos o incorrectos");
	}

	return 0;
}


void inicializar() {
	GestorArch gestor;
	gestor.crearArchivo(RUTA_ARCH_COLA);

	ColaComponentes cola(true);
}

void lanzar() {

	std::stringstream ss;

	int pid;
	for (int i = 0; i < CANT_ESTACIONES ; ++i) {
		ss << i;

		pid = fork();

		if (pid == 0) {
			execl("./estacion", "Est", ss.str().c_str(), NULL);
			SalidaPorPantalla::instancia().error("No se pudo iniciar proceso Estacion");
			exit(EXIT_FAILURE);
		}

		ss.str("");
	}

	SalidaPorPantalla::instancia().mostrar("Lanzados todos los procesos Estacion");

}

void limpiar() {
	ColaComponentes cola;
	cola.destruir();

	GestorArch gestor;
	gestor.destruirArchivo(RUTA_ARCH_COLA);
}
