/*
 * iSolicitar.h
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#ifndef ISOLICITAR_H_
#define ISOLICITAR_H_

#include "Definiciones.h"

class iSolicitar {
public:

	virtual void gestionarPedido(const stPedido& pedido) = 0;

	//virtual int numProductor() = 0;

	virtual ~iSolicitar() {}
};

#endif /* ISOLICITAR_H_ */
