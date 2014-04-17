/*
 * Definiciones.h
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

/************************************************************************************/
/**
 *  Macro utilizadda para cambiar entorno de compilacion
 */
#define COMP_UBUNTU

/************************************************************************************/


typedef struct {
	int num;
} stPedido;

#define TAM_PEDIDO 	sizeof(stPedido)

typedef struct {
	long _mtype;
	stPedido pedido;
} stMensaje;


#define TAM_MENSAJE_COLA (sizeof(stMensaje) - sizeof(long int))

#define ET_CANT_CONSUMIDORES	"CANT_CONSUMIDORES"

#ifndef COMP_UBUNTU

	#define RUTA_ARCH_COLA	"/home/knoppix/cola"
	#define RUTA_ARCH_SEMAFOROS "/home/knoppix/semaforos"

#else

	#define RUTA_ARCH_COLA	"/home/migue/cola"
	#define RUTA_ARCH_SEMAFOROS "/home/migue/semaforos"

#endif

#endif /* DEFINICIONES_H_ */
