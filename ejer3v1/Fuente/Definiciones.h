/*
 * Definiciones.h
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

#include "../../comun/macros.h"
#include <stdlib.h>
#include <signal.h>

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

/*****************************************************************************/

/**
 * Etiquetas de archivo para el archivo de configuracion
 */

#define ET_CANT_CONSUMIDORES	"CANT_CONS"
#define ET_CANT_PRODUCTORES 	"CANT_PROD"

/*****************************************************************************/


#ifndef COMP_UBUNTU

	#define RUTA_ARCH_COLA			"/home/knoppix/cola"

#else

	#define RUTA_ARCH_COLA	"/home/migue/cola"

#endif

/****************************************************************************/

#define TIEMPO_TRABAJO 5000000


/****************************************************************************/
// Identificadores

#define ID_PROD_0	1000
#define ID_CONS_0	5000

#define IdProductor(numProd) 	(numProd + ID_PROD_0)
#define IdConsumidor(numCons)	(numCons + ID_CONS_0)


/****************************************************************************/
/****************************************************************************/
/**
 * Nuevas definiciones
 */

/****************************************************************************/
#define NOMBRE_SERVIDOR_IDS		"servidor_ids"

#define PUERTO_SERVIDOR 	50000

#define PUERTO_CONS_0		51000
//#define PUERTO_PROD_0		52000

#define PuertoConsumidor(numCons) 	(numCons + PUERTO_CONS_0)
//#define PuertoProductor(numProd)	(numProd + PUERTO_PROD_0)


#define DESVIO_NUM_PROD			100000


typedef struct {
	// @TODO llenar con la cosas de un host
	struct sockaddr_in _dir;
	int puerto;
	int numActor;
} stDireccionHost;

namespace TpActor {
	enum TipoActor {
		CONSUMIDOR = 0,
		PRODUCTOR
	};
}


typedef struct {
	TpActor::TipoActor tipo;
	int id;
} stMensajeId;

union stMultiMensaje {
	stDireccionHost _dir;
	stMensaje _msj;
	stMensajeId _id;
};

namespace TpPaquete {
	enum TipoPaquete {
		IDENTIFICACION,
		DIRECION_HOST,
		MENSAJE_COLA
	};
}


typedef struct {

	TpPaquete::TipoPaquete _tipo;

	stMultiMensaje _datos;

} stPaquete;

/*************************************************************************/
// IPCs


#ifdef COMP_UBUNTU
	#define RUTA_SEMAFOROS			"/home/migue/sem_v1"
	#define RUTA_MEM_COMP			"/home/migue/memcomp_v1"
	#define RUTA_COLA_DIRS 			"/home/migue/cola_v1"

#else
	#define RUTA_SEMAFOROS			"/home/knoppix/sem_v1"
	#define RUTA_MEM_COMP			"/home/knoppix/memcomp_v1"
	#define RUTA_COLA_DIRS 			"/home/knoppix/cola_v1"

#endif

#define ID_SEM_MUTEX		'a'
#define ID_SEM_NV_PROD		'b'
#define ID_SEM_NV_CONS		'c'

#define ID_MEM_COMP			'd'
#define ID_COLA_DIRS		'e'

#endif /* DEFINICIONES_H_ */
