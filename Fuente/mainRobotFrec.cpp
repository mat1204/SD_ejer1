/*
 * MainRobotSacar.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */


#include "PlataformaVirtual.h"
#include "ArchConfiguracion.h"
#include "SalidaPorPantalla.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <sstream>

int main(int argc,char** argv) {

	if (argc != 2) {
		perror("Se debe ingresar el numero de robot.");
	}

	int cantRobot;
	int numRobot;

	{
		ArchConfiguracion config;
		config.leer(ET_CANT_ROBOTS, cantRobot);

		std::stringstream ss;
		ss << argv[1];
		ss >> numRobot;

	}

	SalidaPorPantalla::instancia().etiqueta("RobotFrec", numRobot);

	int idRobot = idRobotFrec(numRobot);

	//SalidaPorPantalla::instancia().mostrar("Se inicio proceso de RobotFrec.");
	SalidaPorPantalla::instancia().agregarAlMsj("Se inicio RobotFrec_");
	SalidaPorPantalla::instancia().agregarAlMsj(argv[1]);
	SalidaPorPantalla::instancia().mostrarMsj();

	SalidaPorPantalla* salida = &SalidaPorPantalla::instancia();

	PlataformaVirtual p(cantRobot, idRobot);

	iPlataformaSacar* plataforma = &p;

	int numDispSacado;

	while ( plataforma->seguirTrabajando() ) {
		if ( plataforma->detectarFrecuencia() ) {

			usleep(TIEMPO_TRABAJO);

			if (plataforma->sacarDispositivo(numDispSacado)) {
				salida->agregarAlMsj("Se saco dispositivo numero: ");
				salida->agregarAlMsj(numDispSacado);
				salida->agregarAlMsj(", por el Robot ");
				salida->agregarAlMsj(numeroDeRobot(idRobot));
				salida->mostrarMsj();
			}
		}
	}

	return 0;
}
