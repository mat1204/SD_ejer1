/**
 * mainInicializador.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */


#include "Definiciones.h"

#include "ColaComponentes.h"
#include "SemRobots.h"
#include "SalidaPorPantalla.h"
#include "ArchConfiguracion.h"
#include "Plataforma.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <string.h>
#include <stdio.h>
#include <iostream>

#include <string>
#include <sstream>

int cantRobots;

int capacidadPlataforma;

void configurar();

void inicializar();

void correr();

void limpiar();

void mostrarConfiguracion();

void visor();

void lanzarVisor();

int main(int argc, char** argv) {

	SalidaPorPantalla::instancia().etiqueta("Lanzador");

	if (argc != 2) {
		std::cout << "Se debe Ingresar alguno de los siguientes parametros:" << std::endl;
		std::cout << " -c establecer los parametros de configuracion (cantidad de robots, capacidad de plataforma, etc)" << std::endl;
		std::cout << " -i iniciar la aplicacion con la configuracion dada" << std::endl;
		std::cout << " -t eliminar los recursos utilizados por la aplicacion" << std::endl;
		std::cout << " -m muesta la configuracion actual" << std::endl;
		return 0;
	}

	if (strcmp(argv[1], "-c") == 0) {
		configurar();
	}
	else if (strcmp(argv[1] , "-i") == 0 ) {
		inicializar();
		lanzarVisor();
		correr();
	}
	else if ( strcmp(argv[1] , "-t") == 0 ) {
		limpiar();
	}
	else if ( strcmp(argv[1], "-m") == 0 ) {
		mostrarConfiguracion();
	}
	else if ( strcmp(argv[1], "-v") == 0 ) {
			visor();
	}

	return 0;
}

void lanzarVisor() {
	system("xterm -e watch -n1 \"./lanzador -v\" &");
	usleep(TIEMPO_TRABAJO / 2);
}

void mostrarConfiguracion() {
	ArchConfiguracion config;

	if (config.lecturaValida() == false) {
		SalidaPorPantalla::instancia().mostrar("No se pudo leer archivo de configuracion");
		return;
	}

	int valor;

	config.leer(ET_CANT_ROBOTS, valor);
	SalidaPorPantalla::instancia().mostrar("Cantidad de Robots: ", valor);

	config.leer(ET_CAPCIDAD_PLAT, valor);
	SalidaPorPantalla::instancia().mostrar("Capacidad de Plataforma: ", valor);

}


void configurar() {

	ArchConfiguracion config(true);

	int valor;
	std::string eti(ET_CAPCIDAD_PLAT);


	std::cout << "Capacidad plataforma: " << std::endl;
	std::cin >> valor;

	config.guardar(eti, valor);

	int cantRobots;
	std::cout << "Cantidad de robots: " << std::endl;
	std::cin >> cantRobots;
	eti = ET_CANT_ROBOTS;
	config.guardar(eti, cantRobots);


	for (int i = 0; i < cantRobots ; i++ ) {
		eti = config.armarEtiqueta(ET_PILAS_ROBOT, i);

		std::cout << "Robot N°" << i+1 <<":" << std::endl;
		std::cout << "\t Cantidad de pilas: ";
		std::cin >> valor;
		config.guardar(eti, valor);


		eti = config.armarEtiqueta(ET_DISP_ROBOT, i);

		std::cout << "\t Cantidad de Dispositivos Dispositivos: ";
		std::cin >> valor;
		config.guardar(eti, valor);


		std::cout << std::endl << std::endl;;
	}
}

void inicializar() {

	SalidaPorPantalla::instancia().mostrar("inicializando recursos");

	ArchConfiguracion config;

	if (mknod(RUTA_ARCH_COLA, 0660, 0) == -1)
		SalidaPorPantalla::instancia().error("Error al crear archivo de COLA");

	if (mknod(RUTA_ARCH_SEMAFOROS, 0660, 0) == -1)
		SalidaPorPantalla::instancia().error("Error al crear archivo de SEMAFOROS");


	config.leer(ET_CANT_ROBOTS, cantRobots);

	ColaComponentes cola(true);

	Plataforma plat;
	plat.inicializar();

	SalidaPorPantalla::instancia().mostrar("recursos inicializados");
}

void correr() {
	int pid;

	std::stringstream ss,nombre;

	SalidaPorPantalla::instancia().mostrar("Lanzando procesos");

	for (int i = 0; i < cantRobots ; i++) {
		ss << i;

		nombre.str("");
		nombre << "RArmar-" << i;

		pid = fork();
		if (pid == 0) {
			execl("./robotArmar",nombre.str().c_str(), ss.str().c_str(), (char*) NULL);
			perror("Error al iniciar proceso RobotArmar");
			exit(2);
		}
		else {
			//SalidaPorPantalla::instancia().mostrar("Lanzado proceso Armador-", i);
		}

		nombre.str("");
		nombre << "RFrec-" << i;

		pid = fork();
		if (pid == 0) {
			execl("./robotFrec",nombre.str().c_str(), ss.str().c_str(), (char*) NULL);
			perror("Error al iniciar proceso RobotFrec");
			exit(2);
		}
		else {
			//SalidaPorPantalla::instancia().mostrar("Lanzado proceso Frecuencia-", i);
		}

		std::cout << "Se ARRANCARON los procesos del robot " << ss.str() << std::endl;

		ss.str("");
	}


	pid = fork();

	if (pid == 0) {
		execl("./activ", "Activador", NULL);
		perror("Error no se pudo iniciar proceso activador");
		exit(2);
	}

	SalidaPorPantalla::instancia().mostrar("Lanzados todos los Procesos Robots.");
}

void limpiar() {
	Plataforma plat;
	plat.destruir();

	ColaComponentes cola;
	cola.destruir();

	std::string cmd("rm ");
	cmd += RUTA_ARCH_COLA;
	system(cmd.c_str());

	cmd = "rm ";
	cmd += RUTA_ARCH_SEMAFOROS;
	system(cmd.c_str());

}

void visor() {
	Plataforma plat;
	ArchConfiguracion config;

	int capacidad, cantRobots;

	{
		config.leer(ET_CANT_ROBOTS, cantRobots);
		config.leer(ET_CAPCIDAD_PLAT, capacidad);
	}

	std::cout << "Capacidad: " << capacidad << std::endl;
	std::cout << "Cantidad de Robots: " << cantRobots << std::endl;
	std::cout << std::endl;

	std::cout << "Lugares: " << std::endl;

	plat.mostrarLugares();


	std::cout << std::endl << "Robots: " << std::endl;
	plat.mostrarRobots();


}
