/*
 * Estacion.cpp
 *
 *  Created on: 02/05/2014
 *      Author: migue
 */

#include "Estacion.h"

Estacion::Estacion(int numEstacion) : _colaPiezas() {

	_numEstacion = numEstacion;
	_idEstacion = IdEstacion(_numEstacion);

	_semHayPieza = new Semaforo( RUTA_ARCH_SEM, CANT_ESTACIONES , ID_SEM_HAY_PIEZA);
	_semPiezaLista = new Semaforo( RUTA_ARCH_SEM, CANT_ESTACIONES, ID_SEM_PIEZA_LISTA);
}

Estacion::~Estacion() {
	delete _semHayPieza;
	delete _semPiezaLista;
}

void Estacion::obtenerPiezaEstAnt(stPieza& pieza) {

	this->esperarEstAnterior();

	_colaPiezas.recibir(pieza, _idEstacion);

	this->avisarEstAnterior();

}

void Estacion::esperarEstSig(const stPieza& pieza) {

	this->esperarEstSiguiente();

	_colaPiezas.enviar(pieza, _idEstacion + 1);

	this->avisarEstSiguiente();
}


void Estacion::esperarEstAnterior() {
	_semHayPieza->wait(_numEstacion);
}

void Estacion::avisarEstAnterior() {
	if (_numEstacion > 1)
		_semPiezaLista->signal(_numEstacion - 1);
}

void Estacion::esperarEstSiguiente() {
	_semPiezaLista->wait(_numEstacion);
}

void Estacion::avisarEstSiguiente() {
	if ( ( _numEstacion + 1 ) < CANT_ESTACIONES )
		_semHayPieza->signal(_numEstacion + 1);
}

int Estacion::solicitarMateriales() {

	return 10;
}


void Estacion::inicializarEstaciones() {

	Estacion est(-1);

	for (int i = 0 ; i < CANT_ESTACIONES ; ++i) {
		est._semHayPieza->inicializar(0);
		est._semPiezaLista->inicializar(0);
	}

	est._semPiezaLista->inicializar(1);
}


void Estacion::destruirEstaciones() {

	Estacion est(-1);


	for (int i = 0 ; i < CANT_ESTACIONES ; ++i) {
		est._semHayPieza->destruir();
		est._semPiezaLista->destruir();
	}
}

