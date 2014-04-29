/*
 * ColaComponentes.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef ColaComponentes_H_
#define ColaComponentes_H_

#include "Definiciones.h"
#include "../../comun/SalidaPorPantalla.h"
#include "../../comun/ColaMensajes.h"


class ColaComponentes {
public:

	ColaComponentes(bool crear = false);

	virtual ~ColaComponentes();

	void recibir(stMensaje& msj, int tipoEsperado);

	void enviar(const stMensaje& msj);

	void destruir();

private:
	int _numCola;
	ColaMensajes _colaReal;

	SalidaPorPantalla* _salida;
};

#endif /* ColaComponentes_H_ */
