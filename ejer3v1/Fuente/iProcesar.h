/*
 * iProcesar.h
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#ifndef IPROCESAR_H_
#define IPROCESAR_H_

#include "Definiciones.h"

class iProcesar {
public:

	virtual void sacarPedido(stPedido& pedido) = 0;

	//virtual int numConsumidor() = 0;

	virtual ~iProcesar(){}
};

#endif /* IPROCESAR_H_ */
