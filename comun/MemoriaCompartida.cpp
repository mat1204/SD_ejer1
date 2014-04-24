/*
 * MemoriaCompartida.cpp
 *
 *  Created on: 20/04/2014
 *      Author: migue
 */

#include "MemoriaCompartida.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#include <errno.h>
#include <stdlib.h>
extern int errno;


MemoriaCompartida::MemoriaCompartida(const char* ruta, char id, int tamanio) {
	_salida = &SalidaPorPantalla::instancia();

	// TODO Auto-generated constructor stub
	key_t clave = ftok(ruta, id);

	if (clave == -1) {
		_salida->error(strerror(errno));
		exit(EXIT_FAILURE);
	}

	_tamanio = tamanio;
	_idMemoria = shmget(clave, _tamanio, IPC_CREAT | 0660);

	if (_idMemoria == -1) {
		_salida->error(strerror(errno));
		exit(EXIT_FAILURE);
	}

	_memoria = (char*) shmat(_idMemoria, NULL, 0);

	if (_memoria == (char*) -1) {
		_salida->error(strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void MemoriaCompartida::leer(int posicion, void* dato, int tamDato) const {
	if (posicion < 0 || tamDato <= 0) {
		_salida->error("Parametros al leer en MemCompartida incorrectos");
	}

	if ((posicion + tamDato) > _tamanio) {
		_salida->error("Error al leer en posicion de memoria no valida");
	}

	void* origen = (void*) (_memoria + posicion);

	memcpy(dato, origen, tamDato);
}

void MemoriaCompartida::escribir(int posicion, void* dato, int tamDato) {
	if (posicion < 0 || tamDato <= 0) {
		_salida->error("Parametros al escribir en MemCompartida incorrectos");
	}

	if ((posicion + tamDato) > _tamanio) {
		_salida->error("Error al escribir en posicion de memoria no valida");
	}

	void* destino = (void*) (_memoria + posicion);
	memcpy(destino, dato, tamDato);
}

void MemoriaCompartida::destruir() {
	if (_memoria != NULL) {
		if (shmctl(_idMemoria, IPC_RMID, NULL) == -1) {
			_salida->error("No se pudo eliminar el segmento de MemCompartida");
		}

		_memoria = NULL;
	}
	else {
		_salida->error("MemCompartida ya se destruyo anteriormente");
	}
}

int MemoriaCompartida::tamanio() const {
	return _tamanio;
}

MemoriaCompartida::~MemoriaCompartida() {
	if (_memoria != NULL) {
		if (shmdt((void*)_memoria) == -1) {
			_salida->error("No se pudo desadosar la MemoriaCompartida");
		}
	}
}


