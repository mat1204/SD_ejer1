/*
 * ColaMensajes.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef COLAMENSAJES_H_
#define COLAMENSAJES_H_

#include "Definiciones.h"
#include "SalidaPorPantalla.h"

class ColaMensajes {
public:

	ColaMensajes(bool crear = false);

	virtual ~ColaMensajes();

	void recibir(MensajeCola& msj, int tipoEsperado);

	void enviar(const MensajeCola& msj);

	void crear();

	void destruir();

private:

	int _numCola;

	SalidaPorPantalla* _salida;
};

#endif /* COLAMENSAJES_H_ */
