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

#include "Definiciones.h"
#include "ColaComponentes.h"

#include "ColaDirecciones.h"
#include "GestorActores.h"

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
	SalidaPorPantalla::instancia().mostrar("Inicializando recursos...");

	GestorArch g;
	g.crearArchivo(RUTA_ARCH_COLA);

	ColaComponentes cola(true);
}

void correr() {

	SalidaPorPantalla::instancia().mostrar("Lanzado procesos...");

	ArchConfiguracion config;

	int prod,cons;

	if (config.leer(ET_CANT_CONSUMIDORES, cons) == false ||
			config.leer(ET_CANT_PRODUCTORES, prod) == false ) {
		SalidaPorPantalla::instancia().error("no se pudo leer de archivo de configuracion");
		exit(EXIT_FAILURE);
	}

	int pid;

	std::stringstream ss;

	for (int i = 0 ; i < prod ; ++i) {
		ss << i + 1;

		pid = fork();

		if (pid == 0) {
			execl("./prod","Prod", ss.str().c_str(),NULL);
			SalidaPorPantalla::instancia().error("No se pudo iniciar proceso Productor n°", i+1);
			exit(EXIT_FAILURE);
		}

		ss.str("");
	}


	for (int i = 0 ; i < cons ; ++i) {
		ss << i + 1;
		pid = fork();
		if (pid == 0) {
			execl("./cons", "Cons", ss.str().c_str(), NULL);
			SalidaPorPantalla::instancia().error("No se pudo iniciar proceso Consumidor n°", i+1);
			exit(EXIT_FAILURE);
		}
		ss.str("");
	}

	SalidaPorPantalla::instancia().mostrar("Lanzados todos los procesos.");
}

void limpiar() {
	GestorArch g;
	ColaComponentes cola;
	cola.destruir();

	g.destruirArchivo(RUTA_ARCH_COLA);
}


void inicializarServidor() {
	GestorArch g;
	g.crearArchivo(RUTA_COLA_DIRS);
	g.crearArchivo(RUTA_MEM_COMP);
	g.crearArchivo(RUTA_SEMAFOROS);


	ColaDirecciones cola(true);
	GestorActores gestor;
	gestor.inicializar();
}

void correrServidor() {
	if (fork() == 0) {
		execl("./serv", "Servidor", NULL);
	}
	else {
		SalidaPorPantalla::instancia().mostrar("Proceso Servidor lanzado.");
	}
}

void limpiarServidor() {
	ColaDirecciones cola;
	GestorActores gestor;

	cola.destruir();
	gestor.destruir();

	GestorArch g;

	g.destruirArchivo(RUTA_COLA_DIRS);
	g.destruirArchivo(RUTA_MEM_COMP);
	g.destruirArchivo(RUTA_SEMAFOROS);

}

int main(int argc, char** argv) {

	SalidaPorPantalla::instancia().etiqueta("Lanzador");
	SalidaPorPantalla::instancia().dormirTrasImprimir(false);

	if (argc != 2) {
		std::cout << "Se debe ingrear alguno de los siguientes Parametros:" << std::endl;
		std::cout << " -c configurar" << std::endl;
		std::cout << " -i inicializar y correr" << std::endl;
		std::cout << " -t limpiar recursos" << std::endl;
		exit(EXIT_SUCCESS);
	}

	if (strcmp(argv[1], "-c") == 0) {
		configurar();
	}
	else if (strcmp(argv[1], "-i") == 0) {
		inicializar();
		correr();
	}
	else if (strcmp(argv[1], "-ii") == 0) {
		inicializar();
	}
	else if (strcmp(argv[1], "-t") == 0) {
		limpiar();
	}
	else if (strcmp(argv[1], "-is") == 0) {
		inicializarServidor();
		correrServidor();
	}
	else if (strcmp(argv[1], "-iis") == 0) {
		inicializarServidor();
	}
	else if (strcmp(argv[1], "-ts") == 0) {
		limpiarServidor();
	}
	else if (strcmp(argv[1], "-tt") == 0) {
		limpiar();
		limpiarServidor();
	}
	else if (strcmp(argv[1], "-ix") == 0) {
		inicializar();
		inicializarServidor();
	}
	return 0;
}
