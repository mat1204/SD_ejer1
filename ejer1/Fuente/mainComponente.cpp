/*
 * mainComponente.cpp
 *
 *  Created on: 23/04/2014
 *      Author: migue
 */

#include "ComponenteRobot.h"
#include "../../comun/SalidaPorPantalla.h"
#include "Definiciones.h"
#include <sstream>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

	if (argc != 3) {
		SalidaPorPantalla::instancia().error("Se debe recibir como argumento numero y modo de robot");
		exit(EXIT_FAILURE);
	}

	std::stringstream ss;
	MdRobot::ModoRobot modo;

	ss << argv[1];

	int numRobot;
	ss >> numRobot;

	if (strcmp(argv[2], "A") == 0) {
		modo = MdRobot::ARMADOR;
	}
	else if (strcmp(argv[2], "F") == 0) {
		modo = MdRobot::DET_FRECUENCIA;
	}
	else {
		SalidaPorPantalla::instancia().error("Se debe recibir como argumento numero y modo de robot");
		exit(EXIT_FAILURE);
	}

	ComponenteRobot comp(numRobot, modo);

	return comp.correr();
}
