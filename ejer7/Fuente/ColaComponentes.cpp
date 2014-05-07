/*
 * ColaComponentes.cpp
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */

#include "ColaComponentes.h"

ColaComponentes::ColaComponentes(bool crear) :
	_colaReal(RUTA_ARCH_COLA, ID_COLA , crear) {
}

void ColaComponentes::enviar(const stMensaje& msj) {
	_colaReal.enviar((void*) &msj, sizeof(msj));
}

void ColaComponentes::recibir(stMensaje& msj, int tipoEsp) {
	_colaReal.recibir((void*) &msj, sizeof(msj), tipoEsp);
}

void ColaComponentes::destruir() {
	_colaReal.destruir();
}

ColaComponentes::~ColaComponentes() {
}

