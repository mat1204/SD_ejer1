/*
 * Semaforo.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#include "Semaforo.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <string.h>
#include <errno.h>

#include <stdio.h>

union semnum {
	int val;
	struct semid_ds* buf;
	ushort* array;
};

Semaforo::Semaforo(const char* ruta ,int cant, char id) {

	_salida = &SalidaPorPantalla::instancia();

	if (cant <= 0) {
		_salida->error("Cantidad de Semaforos negativa");
		exit(EXIT_FAILURE);
	}

	_cant = cant;

	key_t clave = ftok(ruta, id);

	if (clave == -1) {
		_salida->error(strerror(errno));
		_salida->error("Error al obtner ftok de archivo de Semaforos");
		exit(EXIT_FAILURE);
	}

	_semId = semget(clave, _cant, IPC_CREAT | 0660);

	if (_semId == -1) {
		_salida->error(strerror(errno));
		_salida->error("Error al obtener identifiador de Semaforos");
		exit(EXIT_FAILURE);
	}
}

Semaforo::~Semaforo() {
}

void Semaforo::inicializar(int val) {
	semnum valor;
	valor.val = val;

	for (int i = 0; i < _cant ; i++) {
		if (semctl(_semId, i, SETVAL, valor ) == -1) {
			_salida->error("error al inicializar semaforos");
			exit(EXIT_FAILURE);
		}
	}
}

void Semaforo::wait(int numRobot) {
	if ( numRobot < _cant && numRobot >= 0 ) {
		struct sembuf op;
		op.sem_num = numRobot;
		op.sem_flg = SEM_UNDO;
		op.sem_op = -1;

		if (semop( _semId, &op, 1) == -1 ) {
			_salida->error("Error al intentar operacion wait() en semaforo");
			exit(EXIT_FAILURE);
		}

	}
	else {
		_salida->error("Error numero de semaforo de robont en wait");
		exit(EXIT_FAILURE);
	}
}

void Semaforo::signal(int numRobot) {
	if ( numRobot < _cant && numRobot >= 0 ) {
		struct sembuf op;
		op.sem_num = numRobot;
		op.sem_flg = SEM_UNDO;
		op.sem_op = 1;

		if (semop( _semId, &op, 1) == -1 ) {
			_salida->error("Error al intentar operacion signal() en semaforo");
			exit(EXIT_FAILURE);
		}

	}
	else {
		_salida->error("Error numero de semaforo de robont en signal");
		exit(EXIT_FAILURE);
	}
}

void Semaforo::destruir() {
	if (semctl( _semId, 0 , IPC_RMID) == -1) {
		_salida->error("Error al intentar destruir semaforos");
	}
}
