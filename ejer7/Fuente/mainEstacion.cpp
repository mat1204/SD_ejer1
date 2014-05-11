/*
 * mainEstacion.cpp
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */


#include "Definiciones.h"
#include <sstream>

#include "EstacionVirtual.h"

int main(int argc, char** argv) {

	if (argc != 3) {
		SalidaPorPantalla::instancia().error("Se debe ingresar numero de estacion y cantidad de materiales");
		return 1;
	}


	int materiales;
	int numEstacion;

	std::stringstream ss;

	ss << argv[1];
	ss >> numEstacion;

	ss.str("");

	ss << argv[2];
	ss >> materiales;


	std::string nomEst = ESTACIONES[numEstacion];
	SalidaPorPantalla::instancia().etiqueta(nomEst.c_str(), numEstacion);
	SalidaPorPantalla* sal = &SalidaPorPantalla::instancia();


	EstacionVirtual e(numEstacion);

	iEstacion *estacion = &e;

	stPieza pieza;

	int numPieza = 1000;

	while (true) {

		if (numEstacion == 0) {
			pieza.numPieza = numPieza++;
			pieza.estaciones = 0;

		}
		else {
			// obtener pieza de estacion anterior
			sal->mostrar("Esperando Estacion ANTERIOR");
			estacion->obtenerPiezaEstAnt(pieza);
			sal->mostrar("Pieza conseguida de estacion anterior");
		}


		if (materiales < 10) {
			sal->mostrar("Materiales Solicitados");
			materiales += estacion->solicitarMateriales();
		}
		// trabajando
		usleep(TIEMPO_TRABAJO);
		materiales -= 10;

		pieza.estaciones++;



		if (numEstacion == (CANT_ESTACIONES - 1)) {
			sal->mostrar("Llevando a playa de estacionamiento", pieza.numPieza);
		}
		else {
			// pasar pieza a la estacion siguiente
			sal->mostrar("Esperando por Estacion SIGUIENTE");
			estacion->esperarEstSig(pieza);
			sal->mostrar("Pieza sacada por estacion siguiente");
		}


	}


	return 0;
}
