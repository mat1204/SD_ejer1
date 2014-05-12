/*
 * Definiciones.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

#include "../../comun/macros.h"

#include "../../comun/SalidaPorPantalla.h"
#include "../../comun/MemoriaCompartida.h"
#include "../../comun/Semaforo.h"
#include "../../comun/GestorArch.h"
#include "../../comun/ColaMensajes.h"

/************************************************************************/

namespace MtdSala {
	enum MetodoSala {

		// Para metodos de la Persona
		HAY_LUGAR,
		ESPERAR_POR_LUGAR,
		HACER_COLA,
		SUBIR_CC,

		// Para metodos del Cable Carril
		SALA_VACIA,
		SACAR_PERSONA_COLA,
		SUBIR_PERSONA,
		BAJAR_PERSONA

	};
};


union res {
	int ent;
	bool booleano;
};

typedef struct {
	long _mtype;


	int _idEmisor;
	MtdSala::MetodoSala metodo;
	int numPersona;

	res resultado;

} stMensaje;

#define TAM_MSJ_COLA	(sizeof(stMensaje) - sizeof(long int))

/************************************************************************/

#ifdef COMP_UBUNTU

	#define RUTA_MEM_COMP	"/home/migue/memcomp"
	#define RUTA_SEM		"/home/migue/sems"
	#define RUTA_COLA		"/home/migue/cola"

#else

	#define RUTA_MEM_COMP	"/home/knoppix/memcomp"
	#define RUTA_SEM		"/home/knoppix/sems"
	#define RUTA_COLA		"/home/knoppix/cola"

#endif

#define ID_COLA_MSJ		'a'

#define ID_SEM_MTX		'b'
#define ID_SEM_LLENO	'c'

#define ID_MEM_COMP		'd'


/************************************************************************/




/************************************************************************/



#endif /* DEFINICIONES_H_ */
