/*
 * ColaComponentes.h
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */

#ifndef COLACOMPONENTES_H_
#define COLACOMPONENTES_H_

#include "Definiciones.h"
#include "../../comun/ColaMensajes.h"

class ColaComponentes {
public:
	ColaComponentes(bool crear = false);

	void enviar(const stMensaje& msj);

	void recibir(stMensaje& msj, int tipoEsperado);

	void destruir();

	virtual ~ColaComponentes();
private:
	ColaMensajes _colaReal;
};

#endif /* COLACOMPONENTES_H_ */
