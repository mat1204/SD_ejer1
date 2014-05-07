/*
 * iEstacion.h
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */

#ifndef IESTACION_H_
#define IESTACION_H_

#include "Definiciones.h"

class iEstacion {
public:

	virtual void obtenerPiezaEstAnt(stPieza& pieza) = 0;

	virtual void esperarEstSig(const stPieza& pieza) = 0;

	virtual int solicitarMateriales() = 0;

	virtual ~iEstacion() {}
};

#endif /* IESTACION_H_ */
