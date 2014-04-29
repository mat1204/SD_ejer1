/*
 * ColaComponentes.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#include "ColaComponentes.h"

ColaComponentes::ColaComponentes(bool crear) : _colaReal(RUTA_ARCH_COLA, 'a', crear){
}

ColaComponentes::~ColaComponentes() {

}

void ColaComponentes::recibir(stMensaje& msj, int tipoEsperado) {
	_colaReal.recibir((void*) &msj, TAM_MENSAJE_COLA, tipoEsperado);
}

void ColaComponentes::enviar(const stMensaje& msj) {
	_colaReal.enviar((void*) &msj, TAM_MENSAJE_COLA);
}

void ColaComponentes::destruir() {
	_colaReal.destruir();
}
