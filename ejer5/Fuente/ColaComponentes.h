/*
 * ColaComponentes.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef COLACOMPONENTES_H_
#define COLACOMPONENTES_H_

#include "Definiciones.h"

class ColaComponentes {
public:
	ColaComponentes(bool crear = false);

	void enviar(const stMensaje& msj);

	void recibir(const stMensaje&msj, int idReceptor);

	void destruir();

	virtual ~ColaComponentes();
private:
	ColaMensajes _colaReal;
};

#endif /* COLACOMPONENTES_H_ */
