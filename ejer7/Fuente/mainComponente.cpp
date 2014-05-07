/*
 * mainComponente.cpp
 *
 *  Created on: 02/05/2014
 *      Author: migue
 */

#include "Definiciones.h"


int main(int argc, char** argv) {

	SalidaPorPantalla::instancia().etiqueta("Componente");

	if (argc != 2) {
		SalidaPorPantalla::instancia().error("Se debe ingresar como parametro el numero de Estacion");
	}

	int numEstacion;
	std::stringstream ss;

	ss << argv[1];
	ss >> numEstacion;

	SalidaPorPantalla::instancia().etiqueta("CompEst", numEstacion);

	CompEstacion comp(numEstacion);

	return comp.correr();
}
