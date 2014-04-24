/*
 * ColaComponentes.h
 *
 *  Created on: 23/04/2014
 *      Author: migue
 */

#ifndef COLACOMPONENTES_H_
#define COLACOMPONENTES_H_

#include "Definiciones.h"
#include "ColaMensajes.h"

class ColaComponentes {
public:
	ColaComponentes(bool crear = false);

	void enviar(const MensajeCola& msj);
	void recibir(MensajeCola& msj, int tipo);

	void destruir();

	virtual ~ColaComponentes();
private:
	ColaMensajes _cola;
};

#endif /* COLACOMPONENTES_H_ */
