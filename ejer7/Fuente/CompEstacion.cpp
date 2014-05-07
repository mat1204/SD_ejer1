/*
 * CompEstacion.cpp
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */

#include "CompEstacion.h"

CompEstacion::CompEstacion(int numEstacion) : _colaComp() , _estacion(numEstacion) {
	_numEstacion = numEstacion;
	_idComp = IdEstComp(numEstacion);
}

CompEstacion::~CompEstacion() {

}

int CompEstacion::correr() {

	while (true) {

		esperarMsj();

		MtdEstacion::MetodoEstacion metodo = _ultimoMsj.metodo;

		switch (metodo) {
			case MtdEstacion::ESPERAR_EST_SIG: esperarEstSiguiente();	break;

			case MtdEstacion::OBTENER_PIEZA_EST_ANT: obtenerPiezaEstAnt();	break;

			default:	break;
		}

		enviarRspt();
	}

	return 0;
}


void CompEstacion::esperarMsj() {
	_colaComp.recibir(_ultimoMsj, _idComp);
}

void CompEstacion::enviarRspt() {
	_respuesta._tipo = _ultimoMsj._idEmisor;
	_colaComp.enviar(_respuesta);
}

void CompEstacion::obtenerPiezaEstAnt() {
	_estacion.obtenerPiezaEstAnt(_respuesta.pieza);
}

void CompEstacion::esperarEstSiguiente() {
	_estacion.esperarEstSig(_ultimoMsj.pieza);
}
