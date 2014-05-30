/*
 * ColaDirecciones.h
 *
 *  Created on: 26/05/2014
 *      Author: migue
 */

#ifndef COLADIRECCIONES_H_
#define COLADIRECCIONES_H_

#include "Definiciones.h"

class ColaDirecciones {
public:
	ColaDirecciones(bool crear = false);

	void destruir();

	void enviar(const stDireccionHost& dir,int destino);

	void recibir(stDireccionHost& dir, int receptor);

	virtual ~ColaDirecciones();

private:
	ColaMensajes _colaReal;
};

#endif /* COLADIRECCIONES_H_ */
