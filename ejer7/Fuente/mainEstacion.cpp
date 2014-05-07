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



	EstacionVirtual e(numEstacion);

	iEstacion *estacion = &e;

	stPieza pieza;

	while (true) {

		// obtener pieza de estacion anterior
		SalidaPorPantalla::instancia().mostrar("Esperando Estacion ANTERIOR");
		estacion->obtenerPiezaEstAnt(pieza);
		SalidaPorPantalla::instancia().mostrar("Pieza conseguida de estacion anterior");

		if (materiales < 10) {
			SalidaPorPantalla::instancia().mostrar("Materiales Solicitados");
			materiales += estacion->solicitarMateriales();
		}
		// trabajando
		usleep(TIEMPO_TRABAJO);
		materiales -= 10;

		pieza.estaciones++;

		// pasar pieza a la estacion siguiente
		SalidaPorPantalla::instancia().mostrar("Esperando por Estacion SIGUIENTE");
		estacion->esperarEstSig(pieza);
		SalidaPorPantalla::instancia().mostrar("Pieza sacada por estacion siguiente");

	}


	return 0;
}
