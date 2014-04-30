/*
 * MainRobotPoner.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#include "SalidaPorPantalla.h"
#include "ArchConfiguracion.h"

#include "PlataformaVirtual.h"
#include <unistd.h>
#include <stdlib.h>


int main(int argc,char** argv) {

	SalidaPorPantalla* salida = &SalidaPorPantalla::instancia();

	if (argc != 2) {
		salida->error("Error, se deben ingresar el numero de robot");
		exit(2);
	}


	int numRobot;
	int cantRobots;

	int pilas;
	int disp;

	{
		ArchConfiguracion config;
		std::string eti;

		std::stringstream ss;
		ss << argv[1];
		ss >> numRobot;

		salida->etiqueta("RobotArmar", numRobot);

		config.leer(ET_CANT_ROBOTS, cantRobots);

		eti = config.armarEtiqueta(ET_PILAS_ROBOT, numRobot);

		if (config.leer(eti.c_str(), pilas) == false )
			salida->error("Error al leer cantidad de pilas del robotArmar,", numRobot);
		else
			salida->mostrar("Leida cantidad de pilas: ", pilas);

		eti = config.armarEtiqueta(ET_DISP_ROBOT, numRobot);

		if (config.leer(eti.c_str(), disp) == false )
			salida->error("Error al leer cantidad de dispositivos del robotArmar,", numRobot);
		else
			salida->mostrar("Leida cantidad de dispositivos: ", disp);
	}


	int idReal = idRobotArmar(numRobot);


	salida->agregarAlMsj("Se inicio RobotArmar_");
	salida->agregarAlMsj(argv[1]);
	salida->mostrarMsj();


	salida->agregarAlMsj("Cantidad de pilas y dispositivos, ");
	salida->agregarAlMsj(pilas);
	salida->agregarAlMsj(" y ");
	salida->agregarAlMsj(disp);
	salida->mostrarMsj();


	//PlataformaVirtual p(numRobot, pilas, disp);
	PlataformaVirtual p(numRobot,pilas, disp);
	iPlataformaPoner* plataforma = &p;

	int numDispositivo = 100 * numRobot + 1000;

	while (pilas > 1 && disp > 0) {


		if (plataforma->plataformaLlena()) {
			plataforma->esperar();
		}
		else {
			pilas -= 2;
			disp--;

			//armando
			usleep(TIEMPO_TRABAJO);

			if (plataforma->colocarDispositivo(numDispositivo)) {
				salida->agregarAlMsj("Se coloco dispositivo n°");
				salida->agregarAlMsj(numDispositivo);
				salida->mostrarMsj();
			}

			// colocando
			usleep(TIEMPO_TRABAJO);
		}
	}

	return 0;
}
