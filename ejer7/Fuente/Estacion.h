/*
 * Estacion.h
 *
 *  Created on: 02/05/2014
 *      Author: migue
 */

#ifndef ESTACION_H_
#define ESTACION_H_

#include "Definiciones.h"
#include "iEstacion.h"
#include "ColaPiezas.h"

#include "../../comun/Semaforo.h"

class Estacion :public iEstacion {
public:
	Estacion(int numEstacion);

	virtual void obtenerPiezaEstAnt(stPieza& pieza);

	virtual void esperarEstSig(const stPieza& pieza);

	virtual int solicitarMateriales();

	virtual ~Estacion();

private:

	void esperarEstAnterior();
	void avisarEstAnterior();

	void esperarEstSiguiente();
	void avisarEstSiguiente();

	int _numEstacion;
	int _idEstacion;

	Semaforo *_semHayPieza;
	Semaforo *_semPiezaLista;

	ColaPiezas _colaPiezas;
};

#endif /* ESTACION_H_ */
