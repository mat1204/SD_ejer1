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

	ColaMensajes(const char* ruta, char id, bool crear = false);

	virtual ~ColaMensajes();

	void recibir(void* msj, int tamMsj, int tipoEsperado);

	void enviar(const void* msj, int tamMsj);

	void crear();

	void destruir();

private:

	int _numCola;

	SalidaPorPantalla* _salida;
};

#endif /* COLAMENSAJES_H_ */
