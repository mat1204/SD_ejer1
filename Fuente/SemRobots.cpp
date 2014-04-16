/*
 * SemRobots.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#include "SemRobots.h"

#include "Definiciones.h"

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

SemRobots::SemRobots(int cantRobots, char id) {

	_salida = &SalidaPorPantalla::instancia();

	if (cantRobots <= 0) {
		_salida->error("Cantidad de Semaforos negativa");
		exit(EXIT_FAILURE);
	}

	_cant = cantRobots;

	key_t clave = ftok(RUTA_ARCH_SEMAFOROS, id);

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

SemRobots::~SemRobots() {
}

void SemRobots::inicializar(int val) {
	semnum valor;
	valor.val = val;

	for (int i = 0; i < _cant ; i++) {
		if (semctl(_semId, i, SETVAL, valor ) == -1)
			_salida->error("error al inicializar semaforos");
	}
}

void SemRobots::wait(int numRobot) {
	if ( numRobot < _cant && numRobot >= 0 ) {
		struct sembuf op;
		op.sem_num = numRobot;
		op.sem_flg = SEM_UNDO;
		op.sem_op = -1;

		if (semop( _semId, &op, 1) == -1 ) {
			_salida->error("Error al intentar operacion wait() en semaforo");
		}

	}
	else {
		_salida->error("Error numero de semaforo de robont en wait");
	}
}

void SemRobots::signal(int numRobot) {
	if ( numRobot < _cant && numRobot >= 0 ) {
		struct sembuf op;
		op.sem_num = numRobot;
		op.sem_flg = SEM_UNDO;
		op.sem_op = 1;

		if (semop( _semId, &op, 1) == -1 ) {
			_salida->error("Error al intentar operacion signal() en semaforo");
		}

	}
	else {
		_salida->error("Error numero de semaforo de robont en signal");
	}
}

void SemRobots::destruir() {
	if (semctl( _semId, 0 , IPC_RMID) == -1) {
		_salida->error("Error al intentar destruir semaforos");
	}
}
