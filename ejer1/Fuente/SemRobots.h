/*
 * SemRobots.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef SEMROBOTS_H_
#define SEMROBOTS_H_

#include "SalidaPorPantalla.h"

class SemRobots {
public:
	SemRobots(int cantRobots, char id);
	virtual ~SemRobots();

	void wait(int numRobot);
	void signal(int numRobot);

	void inicializar(int valor);
	void destruir();

private:
	int _semId;
	int _cant;

	SalidaPorPantalla* _salida;
};

#endif /* SEMROBOT// TODO Auto-generated constructor stubS_H_ */
