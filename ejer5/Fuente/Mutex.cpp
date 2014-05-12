/*
 * Mutex.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#include "Mutex.h"

Mutex::Mutex(char id) :
	_sem(RUTA_MEM_COMP, 1, id) {
}

Mutex::~Mutex() {
}

void Mutex::wait() {
	_sem.wait(0);
}

void Mutex::signal() {
	_sem.signal(0);
}

void Mutex::inicializar(int x) {
	_sem.inicializar(x);
}

void Mutex::destruir() {
	_sem.destruir();
}
