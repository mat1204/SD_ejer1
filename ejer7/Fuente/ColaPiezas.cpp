/*
 * ColaPiezas.cpp
 *
 *  Created on: 25/04/2014
 *      Author: migue
 */

#include "ColaPiezas.h"
#include <string.h>


ColaPiezas::ColaPiezas(bool crear) :
	_colaReal(RUTA_ARCH_COLA, ID_COLA, crear) {
}


void ColaPiezas::enviar(const stPieza& pieza, int idEstacionReceptor) {
	stMensaje msj;

	msj._tipo = idEstacionReceptor;

	memcpy((void*) &msj.pieza, (const void*) &pieza, sizeof(pieza));

	_colaReal.enviar((void*) &msj, sizeof(msj));
}

void ColaPiezas::recibir(stPieza& pieza, int idEstacionActual) {
	stMensaje msj;
	_colaReal.recibir((void*) &msj, sizeof(msj), idEstacionActual);

	memcpy((void*) &pieza, (void*) &msj.pieza, sizeof(pieza));
}

void ColaPiezas::destruir() {
	_colaReal.destruir();
}

ColaPiezas::~ColaPiezas() {
}

