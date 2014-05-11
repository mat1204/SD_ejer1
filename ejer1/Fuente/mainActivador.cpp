/*
 * mainActivador.cpp
 *
 *  Created on: 29/04/2014
 *      Author: migue
 */

#include "Plataforma.h"

#include <unistd.h>
#include <stdlib.h>

int posicionRandom(int maximo);

int main(int argc, char** argv) {

	SalidaPorPantalla::instancia().etiqueta("Activador");
	SalidaPorPantalla::instancia().color(FUENTE_AZUL);

	Plataforma plat;

	int capacidad = plat.capacidad();

	int posicion;


	while (plat.seguirActivando()) {

		usleep(TIEMPO_TRABAJO);

		posicion = posicionRandom(capacidad);

		//SalidaPorPantalla::instancia().mostrar("intentando activar dispositivo en posicion ", posicion);

		plat.activarDispositivo(posicion);
	}

	return 0;
}


int posicionRandom(int maximo) {
	static float fmax = (float) RAND_MAX;
	float aux = ( (float) rand() ) / fmax;

	int res = maximo * aux;

	return res;
}
