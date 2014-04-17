/*
 * GestorPedidos.h
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#ifndef GESTORPEDIDOS_H_
#define GESTORPEDIDOS_H_

#include "iProcesar.h"
#include "iSolicitar.h"

#include "ColaMensajes.h"

#define TIPO_CONSUMIDOR		0
#define TIPO_PRODUCTOR 		1


class GestorPedidos : public iProcesar, public iSolicitar {
public:
	GestorPedidos(int numeroConsumidor = 0);
	virtual ~GestorPedidos();

	virtual void sacarPedido(stPedido& pedido);

	virtual void gestionarPedido(const stPedido& pedido);

private:
	ColaMensajes _cola;
	int _cantConsumidores;
	int _numConsumidor;

	SalidaPorPantalla* _salida;

	void replicarPedido(const stPedido& pedido);
};

#endif /* GESTORPEDIDOS_H_ */
