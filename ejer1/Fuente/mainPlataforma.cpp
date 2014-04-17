/*
 * mainPlataforma.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "PlataformaReal.h"
#include "ArchConfiguracion.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc,char** argv) {
	ArchConfiguracion config;

	int capacidad;
	int cantRobots;

	config.leer(ET_CANT_ROBOTS, cantRobots);
	config.leer(ET_CAPCIDAD_PLAT, capacidad);

	PlataformaReal plataforma(capacidad, cantRobots);

	return plataforma.iniciar();
}
