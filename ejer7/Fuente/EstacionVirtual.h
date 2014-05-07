/*
 * EstacionVirtual.h
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */

#ifndef ESTACIONVIRTUAL_H_
#define ESTACIONVIRTUAL_H_

#include "iEstacion.h"
#include "ColaComponentes.h"

class EstacionVirtual : public iEstacion {
public:

	EstacionVirtual(int numEstacion);

	virtual void obtenerPiezaEstAnt(stPieza& pieza);

	virtual void esperarEstSig(const stPieza& piezaAEnviar);

	virtual int solicitarMateriales();

	virtual ~EstacionVirtual();

private:

	void iniciarComponente();

	int _numEstacion, _idEstVirtual, _idComp;
	ColaComponentes _colaComp;

};

#endif /* ESTACIONVIRTUAL_H_ */
