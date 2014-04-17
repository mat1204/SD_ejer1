/**
 * mainInicializador.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */


#include "Definiciones.h"

#include "ColaMensajes.h"
#include "SemRobots.h"
#include "SalidaPorPantalla.h"
#include "ArchConfiguracion.h"

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

int test() {
	std::stringstream ss;

	std::string mm;


	ss << "hola";

	ss << 2;

	ss << "chau";

	ss << "ma bb";

	ss << 3;

	ss << "jaja";

	//ss >> mm;

	mm = ss.str();
	std::cout << "1) \""<< mm <<"\"" << std::endl;

	ss.str("");

	ss << 1 << "2345" << 67;

	ss >> mm;

	std::cout << "2) \""<< mm <<"\"" << std::endl;
	std::cout << "3) \""<< ss. str() <<"\"" << std::endl;


	return 0;
}

int main(int argc, char** argv) {

	//return test();

	if (argc != 2) {
		std::cout << "Se debe Ingresar -c,-i o -t para configurar, iniciar o eliminar recursos." << std::endl;
		exit(2);
	}


	if (strcmp(argv[1], "-c") == 0) {
		configurar();
	}
	else if (strcmp(argv[1] , "-i") == 0 ) {
		inicializar();
		correr();
	}
	else if ( strcmp(argv[1] , "-t") == 0 ) {
		limpiar();
	}

	return 0;
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

	ArchConfiguracion config;

	if (mknod(RUTA_ARCH_COLA, 0660, 0) == -1)
		SalidaPorPantalla::instancia().error("Error al crear archivo de COLA");

	if (mknod(RUTA_ARCH_SEMAFOROS, 0660, 0) == -1)
		SalidaPorPantalla::instancia().error("Error al crear archivo de SEMAFOROS");


	config.leer(ET_CANT_ROBOTS, cantRobots);

	SemRobots frec(cantRobots, ID_SEMS_FREC);
	SemRobots armar(cantRobots, ID_SEMS_ARMAR);

	frec.inicializar(0);
	armar.inicializar(1);

	ColaMensajes cola(true);
}

void correr() {
	std::string capacidad;

	// lanzar plataforma

	int pid;

	pid = fork();

	if (pid == 0) {
		execl("./plataforma","plataforma", (char*) NULL);
	}


	std::stringstream ss,nombre;

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

		nombre.str("");
		nombre << "RFrec-" << i;

		pid = fork();
		if (pid == 0) {
			execl("./robotFrec",nombre.str().c_str(), ss.str().c_str(), (char*) NULL);
			perror("Error al iniciar proceso RobotFrec");
			exit(2);
		}

		std::cout << "Se ARRANCARON los procesos del robot " << ss.str() << std::endl;

		ss.str("");
	}

	SalidaPorPantalla::instancia().mostrar("Lanzados todos los Procesos Robots.");
}

void limpiar() {
	ArchConfiguracion config;

	config.leer(ET_CANT_ROBOTS, cantRobots);

	SemRobots frec(cantRobots, ID_SEMS_FREC);
	SemRobots armar(cantRobots, ID_SEMS_ARMAR);

	frec.destruir();
	armar.destruir();

	ColaMensajes cola;
	cola.destruir();

	std::string cmd("rm ");
	cmd += RUTA_ARCH_COLA;
	system(cmd.c_str());

	cmd = "rm ";
	cmd += RUTA_ARCH_SEMAFOROS;
	system(cmd.c_str());

}
