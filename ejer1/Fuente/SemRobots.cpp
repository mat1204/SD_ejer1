/*
 * SemRobots.cpp
 *
 *  Created on: 23/04/2014
 *      Author: migue
 */

#include "SemRobots.h"
#include "Definiciones.h"

SemRobots::SemRobots(int cantRobots, char id) :
	_sem(RUTA_ARCH_SEMAFOROS, cantRobots, id){

}

SemRobots::~SemRobots() {
}

void SemRobots::wait(int numRobot) {
	_sem.wait(numRobot);
}
void SemRobots::signal(int numRobot) {
	_sem.signal(numRobot);
}

void SemRobots::destruir() {
	_sem.destruir();
}

void SemRobots::inicializar(int x) {
	_sem.inicializar(x);
}
