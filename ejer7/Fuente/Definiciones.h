/*
 * Definiciones.h
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_


#include "../../comun/macros.h"
#include "../../comun/SalidaPorPantalla.h"
#include "../../comun/GestorArch.h"

//#define COMP_UBUNTU

typedef struct {
	int numPieza;
	int estaciones;
} stPieza;

namespace MtdEstacion {
	enum MetodoEstacion {
		OBTENER_PIEZA_EST_ANT,
		ESPERAR_EST_SIG
	};
};

typedef struct {
	long int _tipo;
	int _idEmisor;

	MtdEstacion::MetodoEstacion metodo;
	stPieza pieza;
} stMensaje;


#define ID_COLA					'a'
#define ID_SEM_EST				'c'
#define ID_SEM_HAY_PIEZA		'd'
#define ID_SEM_PIEZA_LISTA		'e'


#define CANT_ESTACIONES 	6

#define NUM_PRIMER_ESTACION 	0
#define NUM_ULTIMA_ESTACION		5

#define ID_EST_VIRTUAL_0	1000
#define ID_ESTACION_0		2000
#define ID_EST_COMP_0		3000

#define IdEstVirtual(numEstacion)	(numEstacion + ID_EST_VIRTUAL_0)
#define IdEstacion(numEstacion) 	(numEstacion + ID_ESTACION_0)
#define IdEstComp(numEstacion)		(numEstacion + ID_EST_COMP_0)

#define NOM_EST_0		"Chasis"
#define NOM_EST_1		"Pintura"
#define NOM_EST_2		"Secado"
#define NOM_EST_3		"ArmarMotor"
#define NOM_EST_4		"ArmarInterior"
#define NOM_EST_5		"ArmarPuertas"

static const char* ESTACIONES[] = { NOM_EST_0, NOM_EST_1, NOM_EST_2, NOM_EST_3, NOM_EST_4, NOM_EST_5 };


#ifdef COMP_UBUNTU
	#define RUTA_ARCH_COLA "/home/migue/cola"

#else
	#define RUTA_ARCH_COLA "/home/knoppix/cola"

#endif


#define RUTA_ARCH_SEM	RUTA_ARCH_COLA

#define TIEMPO_TRABAJO		10000

#endif /* DEFINICIONES_H_ */
