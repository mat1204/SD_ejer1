/*
 * mainLanzador.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "ColaComponentes.h"
#include "ColaBloqueos.h"
#include "Sala.h"

#include <string.h>
#include <iostream>


void configurar();
void inicializar();
void correr();
void limpiar();

void lanzarVisorDebajo();

void mostrarConfiguracion();
void visor();


int main(int argc, char** argv) {

	SalidaPorPantalla::instancia().etiqueta("Lanzador");

	if (argc != 2) {
		std::cout << "Se debe ingresar alguno de los siguientes argumentos: " << std::endl;
		std::cout << " -c configurar los parametros de la aplicacion." << std::endl;
		std::cout << " -i inicializar y correr la aplicacion." << std::endl;
		std::cout << " -t limpiar los recursos utilizados." << std::endl;
		std::cout << " -m mostrar configuracion." << std::endl;
	}


	if (strcmp(argv[1], "-c") == 0) {
		configurar();
	}
	else if (strcmp(argv[1], "-i") == 0) {
		inicializar();
		lanzarVisorDebajo();
		correr();
	}
	else if (strcmp(argv[1], "--ii") == 0) {
		inicializar();
	}
	else if (strcmp(argv[1], "-t") == 0) {
		limpiar();
	}
	else if (strcmp(argv[1], "-v") == 0) {
		visor();
	}
	else if (strcmp(argv[1], "-m") == 0) {
		mostrarConfiguracion();
	}
	else {
		SalidaPorPantalla::instancia().mostrar("Parametro no reconocido");
	}



	return 0;
}


void configurar() {
	ArchConfiguracion config(true);

	int valor;

	std::cout << "Cantidad de personas a pasear: ";
	std::cin >> valor;

	config.escribir(ET_PERSONAS_PROD, (void*) &valor, sizeof(valor));


	std::cout << "Cantidad de Cable Carriles: ";
	std::cin >> valor;

	config.escribir(ET_CANT_CC, (void*) &valor, sizeof(valor));
}


void inicializar() {
	GestorArch gestor;


	gestor.crearArchivo(RUTA_COLA);
	gestor.crearArchivo(RUTA_MEM_COMP);
	gestor.crearArchivo(RUTA_SEM);

	ColaComponentes cola(true);
	ColaBloqueos colaBlq(true);

	Sala sc(LgSala::CIMA), sp(LgSala::PIE);

	sc.inicializar();
	sp.inicializar();
}


void correr() {
	std::stringstream ss;

	ArchConfiguracion config;

	int cantCC, pid;

	config.leer(ET_CANT_CC , cantCC);


	pid = fork();

	if (pid == 0) {
		execl("./prod", "Productor", NULL);
		SalidaPorPantalla::instancia().error("No se pudo iniciar Proceso Productor");
		exit(EXIT_FAILURE);
	}
	else {
		SalidaPorPantalla::instancia().mostrar("Lanzado productor");
	}

	for (int i = 0; i < cantCC ; ++i) {
		ss.str("");
		ss << i;

		pid = fork();

		if (pid == 0) {

			execl("./cc", "CableCarril", ss.str().c_str(), NULL);
			SalidaPorPantalla::instancia().error("No se pudod iniciar proceso Cable Carril");
			exit(EXIT_FAILURE);
		}
		else {
			SalidaPorPantalla::instancia().mostrar("Lanzado Cable Carril", i);
		}

	}
}

void limpiar() {
	Sala sc(LgSala::CIMA), sp(LgSala::PIE);

	sc.destruir();
	sp.destruir();

	ColaComponentes cola;
	ColaBloqueos colaBlq;

	colaBlq.destruir();
	cola.destruir();

	GestorArch gestor;

	gestor.destruirArchivo(RUTA_COLA);
	gestor.destruirArchivo(RUTA_MEM_COMP);
	gestor.destruirArchivo(RUTA_SEM);
}


void mostrarConfiguracion() {
	ArchConfiguracion config;
	int val;

	config.leer(ET_CANT_CC, val);
	std::cout << "Cantidad de cable Carriles: " << val << std::endl;

	config.leer(ET_PERSONAS_PROD, val);
	std::cout << "Cantidad de personas por pasear: " << val << std::endl;

}

void lanzarVisorDebajo() {
	system("xterm -e watch -n1 \"./lanzador -v\" &");
}

void visor() {
	Sala salaCima(LgSala::CIMA), salaPie(LgSala::PIE);

	std::cout << "Estado de la SALA al PIE de la Montaña" << std::endl;

	salaPie.mostrarEstado();

	std::cout << "Estado de la SALA en la CIMA de la Montaña" << std::endl;

	salaCima.mostrarEstado();
}
