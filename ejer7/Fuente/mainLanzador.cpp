/*
 * mainLanzador.cpp
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */


#include "Definiciones.h"
#include "ColaComponentes.h"
#include "Estacion.h"

#include <string>
#include <string.h>
#include <stdlib.h>



void inicializar();
void lanzar();
void limpiar();

const std::string materialesRandom();

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

	Estacion::inicializarEstaciones();
}

void lanzar() {

	std::stringstream ss;

	int pid;
	for (int i = 0; i < CANT_ESTACIONES ; ++i) {
		ss << i;

		pid = fork();

		if (pid == 0) {
			execl("./estacion", "Est", ss.str().c_str(), materialesRandom().c_str(), NULL);
			SalidaPorPantalla::instancia().error("No se pudo iniciar proceso Estacion");
			exit(EXIT_FAILURE);
		}

		ss.str("");
	}

	SalidaPorPantalla::instancia().mostrar("Lanzados todos los procesos Estacion");

}

void limpiar() {
	Estacion::destruirEstaciones();

	ColaComponentes cola;
	cola.destruir();

	GestorArch gestor;
	gestor.destruirArchivo(RUTA_ARCH_COLA);
}


const std::string materialesRandom() {
	float aux = ((float) rand()) / ((float) RAND_MAX);

	int res = 20 + ((int)(20.0 * aux));

	std::stringstream ss;

	ss << res;

	return ss.str();
}
