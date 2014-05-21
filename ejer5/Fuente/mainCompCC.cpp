/*
 * mainCompCC.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "SalaVirtual.h"

#include "CompCableCarril.h"

#include <iostream>

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Se debe ingresar el numero de cable Carril" << std::endl;
		return EXIT_FAILURE;
	}

	std::stringstream ss;
	int numCC;

	ss << argv[1];
	ss >> numCC;


	SalidaPorPantalla::instancia().etiqueta("CompCC", numCC);

	CompCableCarril comp(numCC);

	return comp.correr();
}


