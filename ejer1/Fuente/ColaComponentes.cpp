/*
 * ColaComponentes.cpp
 *
 *  Created on: 23/04/2014
 *      Author: migue
 */

#include "ColaComponentes.h"

ColaComponentes::ColaComponentes(bool crear) :
	_cola(RUTA_ARCH_COLA, 'a', crear) {

}

ColaComponentes::~ColaComponentes() {
}


void ColaComponentes::enviar(const MensajeCola& msj) {
	_cola.enviar((void*) &msj, TAM_MENSAJE_COLA);
}

void ColaComponentes::recibir(MensajeCola& msj, int tipo) {
	_cola.recibir((void*) &msj, TAM_MENSAJE_COLA, tipo);
}

void ColaComponentes::destruir() {
	_cola.destruir();
}
