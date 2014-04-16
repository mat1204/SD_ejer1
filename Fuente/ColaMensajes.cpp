/*
 * ColaMensajes.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#include "ColaMensajes.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include <errno.h>
#include <stdlib.h>

#include <stdio.h>

extern int errno;

ColaMensajes::ColaMensajes(bool crear) {

	key_t clave = ftok(RUTA_ARCH_COLA, 'a');

	if (clave == -1) {
		_salida->error(strerror(errno));
		_salida->error("Error al obtener clave [ftok(...)]");
		exit(EXIT_FAILURE);
	}

	if (crear) {
		_numCola = msgget(clave, IPC_CREAT | IPC_EXCL | 0660 );
	}
	else {
		_numCola = msgget(clave, 0660);
	}

	if ( _numCola == -1 ) {
		_salida->error(strerror(errno));
		_salida->error("Error al crear o obtener la Cola de Mensajes");
		exit(EXIT_FAILURE);
	}

	_salida = &SalidaPorPantalla::instancia();
}

ColaMensajes::~ColaMensajes() {

}

void ColaMensajes::recibir(MensajeCola& msj, int tipoEsperado) {
	if (msgrcv(_numCola, (void*) &msj, TAM_MENSAJE_COLA, tipoEsperado , 0) == -1 ) {
		_salida->error("Error al recibir Mensaje por Cola");
		exit(EXIT_FAILURE);
	}
}

void ColaMensajes::enviar(const MensajeCola& msj) {
	if (msgsnd(_numCola, (const void*) &msj, TAM_MENSAJE_COLA, 0) == -1 ) {
		_salida->error("Error al enviar Mensaje por Cola");
		exit(EXIT_FAILURE);
	}
}

void ColaMensajes::destruir() {

	if ( msgctl(_numCola, IPC_RMID, NULL) == -1 ) {
		_salida->error(strerror(errno));
		_salida->error("Error al destruir la Cola");
		exit(EXIT_FAILURE);
	}
}
