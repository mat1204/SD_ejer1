/*
 * ColaBloqueos.h
 *
 *  Created on: 14/05/2014
 *      Author: migue
 */

#ifndef COLABLOQUEOS_H_
#define COLABLOQUEOS_H_

#include "Definiciones.h"

class ColaBloqueos {
public:
	ColaBloqueos(bool crear = false);

	void enviar(int id);

	void recibir(int id);

	void destruir();

	virtual ~ColaBloqueos();
private:
	ColaMensajes _cola;
};

#endif /* COLABLOQUEOS_H_ */
