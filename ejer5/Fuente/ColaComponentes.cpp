/*
 * ColaComponentes.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#include "ColaComponentes.h"

ColaComponentes::ColaComponentes(bool crear) :
_colaReal(RUTA_COLA, ID_COLA_MSJ, crear) {
}

ColaComponentes::~ColaComponentes() {
}

void ColaComponentes::enviar(const stMensaje& msj) {
	//SalidaPorPantalla::instancia().mostrar("Enviando msj...");
	_colaReal.enviar((const void*) &msj, TAM_MSJ_COLA);
}

void ColaComponentes::recibir(const stMensaje&msj, int idReceptor) {
	_colaReal.recibir((void*) &msj, TAM_MSJ_COLA, idReceptor);
	//SalidaPorPantalla::instancia().mostrar("Mensaje recibido.");
}

void ColaComponentes::destruir() {
	_colaReal.destruir();
}
