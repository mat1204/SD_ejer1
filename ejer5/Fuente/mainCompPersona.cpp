/*
 * mainCompPersona.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */


#include "Definiciones.h"
#include "CompPersona.h"

int main(int argc, char** argv) {

	if (argc != 2) {
		SalidaPorPantalla::instancia().error("No se recibio numero de persona");
		return EXIT_FAILURE;
	}

	std::stringstream ss;


	int numPersona;

	ss << argv[1];
	ss >> numPersona;

	SalidaPorPantalla::instancia().etiqueta("CompPersona", numPersona);

	CompPersona comp(numPersona);

	return comp.correr();
}
