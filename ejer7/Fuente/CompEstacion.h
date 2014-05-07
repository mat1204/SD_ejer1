/*
 * CompEstacion.h
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */

#ifndef COMPESTACION_H_
#define COMPESTACION_H_

#include "Estacion.h"
#include "ColaComponentes.h"

class CompEstacion {
public:
	CompEstacion(int numEstacion);
	virtual ~CompEstacion();

	int correr();

private:

	void esperarMsj();
	void enviarRspt();


	void obtenerPiezaEstAnt();
	void esperarEstSiguiente();

	stMensaje _ultimoMsj, _respuesta;

	int _numEstacion;
	int _idComp;

	Estacion _estacion;
	ColaComponentes _colaComp;
};

#endif /* COMPESTACION_H_ */
