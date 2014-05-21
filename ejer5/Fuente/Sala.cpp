/*
 * Sala.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#include "Sala.h"

Sala::Sala(LgSala::LugarSala lugar) {

	_lugar = lugar;

	if (_lugar == LgSala::CIMA) {
		_mtx = new Mutex(ID_SEM_MTX_CIMA);
		_semLleno = new Mutex(ID_SEM_LLENO_CIMA);
		_semVacio = new Mutex(ID_SEM_VACIO_CIMA);

		_area = new AreaPersonas(ID_MEMC_SALA_CIMA);
	}
	else if (_lugar == LgSala::PIE) {
		_mtx = new Mutex(ID_SEM_MTX_PIE);
		_semLleno = new Mutex(ID_SEM_LLENO_PIE);
		_semVacio = new Mutex(ID_SEM_VACIO_PIE);

		_area = new AreaPersonas(ID_MEMC_SALA_PIE);
	}
	else {
		SalidaPorPantalla::instancia().error("No se reconoce lugar de sala");
		exit(EXIT_FAILURE);
	}
}

Sala::~Sala() {
	delete _mtx;
	delete _semLleno;
	delete _semVacio;

	delete _area;
}

void Sala::inicializar() {
	_mtx->inicializar();
	_semLleno->inicializar(0);
	_semVacio->inicializar(0);

	_area->inicializar();
}

void Sala::destruir() {
	_mtx->destruir();
	_semLleno->destruir();
	_semVacio->destruir();

	_area->destruir();
}

bool Sala::hayLugar() {
	bool res;

	_mtx->wait();

	res = _area->hayLugar();

	_mtx->signal();

	return res;
}


void Sala::esperarPorLugar() {
	_mtx->wait();
	_area->esperandoPorLleno(1);
	_mtx->signal();

	_semLleno->wait();
}

bool Sala::salaVacia() {
	bool res;

	_mtx->wait();

	res = _area->salaVacia();

	_mtx->signal();

	return res;
}

bool Sala::sacarPersona(int& numPersona) {
	bool res;

	_mtx->wait();

	res = _area->sacarPersona(numPersona);

	if (_area->esperandoPorLleno() > 0) {
		_area->esperandoPorLleno(-1);
		_semLleno->signal();
	}

	_mtx->signal();

	return res;
}

bool Sala::hacerCola(const int numPersona) {
	bool res;
	_mtx->wait();

	res = _area->hacerCola(numPersona);

	_mtx->signal();

	return res;
}


void Sala::mostrarEstado() {
	_mtx->wait();

	_area->mostrarEstado();

	_mtx->signal();
}
