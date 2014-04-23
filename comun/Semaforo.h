/*
 * SemRobots.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include "SalidaPorPantalla.h"

class Semaforo {
public:
	Semaforo(const char* ruta, int cant, char id);
	virtual ~Semaforo();

	void wait(int numRobot);
	void signal(int numRobot);

	void inicializar(int valor);
	void destruir();

private:
	int _semId;
	int _cant;
	SalidaPorPantalla* _salida;
};

#endif /* SEMAFORO// TODO Auto-generated constructor stubS_H_ */
