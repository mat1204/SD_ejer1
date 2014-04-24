/*
 * SemRobots.h
 *
 *  Created on: 23/04/2014
 *      Author: migue
 */

#ifndef SEMROBOTS_H_
#define SEMROBOTS_H_

#include "../../comun/Semaforo.h"

class SemRobots {
public:
	SemRobots(int cantRobot, char id);
	virtual ~SemRobots();

	void wait(int numRobot);
	void signal(int numRobot);

	void destruir();

	void inicializar(int x);

private:
	Semaforo _sem;
};

#endif /* SEMROBOTS_H_ */
