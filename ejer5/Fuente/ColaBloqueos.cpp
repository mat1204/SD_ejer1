/*
 * ColaBloqueos.cpp
 *
 *  Created on: 14/05/2014
 *      Author: migue
 */

#include "ColaBloqueos.h"

ColaBloqueos::ColaBloqueos(bool crear) :
	_cola(RUTA_COLA_BLQ, ID_COLA_BLQ, crear)
{

}

ColaBloqueos::~ColaBloqueos() {

}


void ColaBloqueos::enviar(int id) {
	stMensajeBloqueo msj;
	msj._mtype = id;

	_cola.enviar((const void*) &msj, TAM_MSJ_BLQ);
}

void ColaBloqueos::recibir(int id) {
	stMensajeBloqueo msj;

	_cola.recibir((void*) &msj, TAM_MSJ_BLQ, id);
}

void ColaBloqueos::destruir() {
	_cola.destruir();
}
