/*
 * Mutex.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include "Definiciones.h"

class Mutex {
public:
	Mutex(char id);

	virtual ~Mutex();

	void wait();

	void signal();

	void inicializar(int x = 1);

	void destruir();

private:
	Semaforo _sem;
};

#endif /* MUTEX_H_ */
