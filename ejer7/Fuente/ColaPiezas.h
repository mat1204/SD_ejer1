/*
 * ColaPiezas.h
 *
 *  Created on: 25/04/2014
 *      Author: migue
 */

#ifndef COLAPIEZAS_H_
#define COLAPIEZAS_H_

#include "../../comun/ColaMensajes.h"

#include "Definiciones.h"

class ColaPiezas {
public:
	ColaPiezas(bool crear = false);

	void enviar(const stPieza& pieza, int idEstacionReceptor);

	void recibir(stPieza& pieza, int idEstacionActual);

	void destruir();

	virtual ~ColaPiezas();
private:
	ColaMensajes _colaReal;
};

#endif /* COLAPIEZAS_H_ */
