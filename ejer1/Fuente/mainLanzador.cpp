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

void testConfiguracion() {
	int p1=23, p2 = 2 ,p3=284455 , p4 = 34568291;

	std::cout << "Inicio de Pruebas." << std::endl;

	std::string etiq;

	{
		ArchConfiguracion config(true);

		std::cout << "Creacon de archivo." << std::endl;

		etiq = "num1";
		config.guardar(etiq.c_str(), p1);

		etiq = "num2";
		config.guardar(etiq.c_str(), p2);

		etiq = "num3";
		config.guardar(etiq.c_str(), p3);

		etiq = "num5";
		config.guardar(etiq.c_str(), p4);

		config.serializar();

	}


	{

		std::cout << "Comienza lectura." << std::endl;
		ArchConfiguracion arch;

		int valor;
		arch.leer("num2", valor);

		if (valor != p2) {
			std::cout << "Error en p2" << std::endl;
		}

		arch.leer("num1", valor);

		if (valor != p1) {
			std::cout << "Error en p1" << std::endl;
		}

		arch.leer("num3", valor);

		if (valor != p3) {
			std::cout << "Error en p3" << std::endl;
		}

		arch.leer("num5", valor);

		if (valor != p4) {
			std::cout << "Error en p4" << std::endl;
		}


		std::cout  << "Fin de prueba" << std::endl;
	}

}

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Se debe Ingresar -c,-i o -t para configurar, iniciar o eliminar recursos." << std::endl;
		exit(2);
	}

	SalidaPorPantalla::instancia().etiqueta("Lanzador");

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

	usleep(TIEMPO_TRABAJO);
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
			SalidaPorPantalla::instancia().mostrar("Lanzado proceso Armador-", i);
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
			SalidaPorPantalla::instancia().mostrar("Lanzado proceso Frecuencia-", i);
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
