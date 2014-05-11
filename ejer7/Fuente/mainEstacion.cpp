/*
 * mainEstacion.cpp
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */


#include "Definiciones.h"
#include <sstream>

#include "EstacionVirtual.h"

int colorDeFuente(int numEstacion) {
	int color;

	switch (numEstacion) {
	case 0: color = FUENTE_ROJO;
		break;

	case 1: color = FUENTE_AZUL;
		break;

	case 2: color = FUENTE_VERDE;
		break;

	case 3: color = FUENTE_CYAN;
		break;

	case 4: color = FUENTE_MAGENTA;
		break;

	case 5: color = FUENTE_AMARILLA;
		break;

	default: color = FUENTE_BLANCA;
		break;
	}

	return color;
}

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
	SalidaPorPantalla::instancia().color(colorDeFuente(numEstacion));
	SalidaPorPantalla* sal = &SalidaPorPantalla::instancia();


	EstacionVirtual e(numEstacion);

	iEstacion *estacion = &e;

	stPieza pieza;

	int numPieza = 1000;

	while (true) {

		if (numEstacion == NUM_PRIMER_ESTACION) {
			pieza.numPieza = numPieza++;
			pieza.estaciones = 0;
			sal->mostrar("Pedido ingresado, pieza n°",pieza.numPieza);
		}
		else {
			// obtener pieza de estacion anterior
			//sal->mostrar("Esperando Estacion ANTERIOR");
			estacion->obtenerPiezaEstAnt(pieza);
			sal->mostrar("Pieza conseguida de estacion anterior, n°",pieza.numPieza);
		}


		if (materiales < 10) {
			sal->mostrar("Materiales Solicitados");
			materiales += estacion->solicitarMateriales();
		}
		// trabajando

		sal->mostrar("Trabajando...");

		usleep(TIEMPO_TRABAJO);
		materiales -= 2;

		pieza.estaciones++;



		if (numEstacion == NUM_ULTIMA_ESTACION) {
			sal->mostrar("Llevando a playa de estacionamiento, n°", pieza.numPieza);
		}
		else {
			// pasar pieza a la estacion siguiente
			//sal->mostrar("Esperando por Estacion SIGUIENTE");
			estacion->esperarEstSig(pieza);
			sal->mostrar("Pieza sacada por estacion siguiente");
		}


	}


	return 0;
}
