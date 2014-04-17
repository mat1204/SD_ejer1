/*
 * Definiciones.h
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

typedef struct {
	int num;
} stPedido;

#define TAM_PEDIDO 		sizeof(stPedido);

typedef struct {
	long _mtype;
	stPedido pedido;
} stMensaje;


#define TAM_MENSAJE_COLA (sizeof(stMensaje) - sizeof(long int))

#define ET_CANT_CONSUMIDORES	"CANT_CONSUMIDORES"


#endif /* DEFINICIONES_H_ */
