/*
 * mainLanzador.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "ArchConfiguracion.h"
#include "SalidaPorPantalla.h"


#include "ColaMensajes.h"

void configurar() {
	int prod,cons;

	std::cout << "Cantidad de productores: ";
	std::cin >> prod;

	std::cout << "Cantidad de consumidores: ";
	std::cin >> cons;

	ArchConfiguracion config(true);

	config.guardar(ET_CANT_CONSUMIDORES, cons);
	config.guardar(ET_CANT_PRODUCTORES, prod);

	config.serializar();
}

void inicializar() {
	ColaMensajes cola(true);
}

void correr() {

	ArchConfiguracion config;

	int prod,cons;

	if (config.leer(ET_CANT_CONSUMIDORES, cons) == false ||
			config.leer(ET_CANT_PRODUCTORES, prod) == false ) {
		SalidaPorPantalla::instancia().error("no se pudo leer de archivo de configuracion");
		exit(EXIT_FAILURE);
	}

}

void limpiar() {
	ColaMensajes cola;
	cola.destruir();
}

int main(int argc, char** argv) {

	if (argc != 2) {
		SalidaPorPantalla::instancia().etiqueta("arg");
		SalidaPorPantalla::instancia().mostrar("\t -c configurar");
		SalidaPorPantalla::instancia().mostrar("\t -i inicializar y correr");
		SalidaPorPantalla::instancia().mostrar("\t -t limpiar recursos");
		exit(EXIT_SUCCESS);
	}


	if (strcmp(argv[1], "-c") == 0) {
		configurar();
	}
	else if (strcmp(argv[1], "-i") == 0) {
		inicializar();
		correr();
	}
	else if (strcmp(argv[1], "-t") == 0) {
		limpiar();
	}


	return 0;
}
