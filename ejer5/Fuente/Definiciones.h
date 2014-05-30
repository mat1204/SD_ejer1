/*
 * Definiciones.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

#include "../../comun/macros.h"

#include "../../comun/ArchConfiguracion.h"
#include "../../comun/SalidaPorPantalla.h"
#include "../../comun/MemoriaCompartida.h"
#include "../../comun/Semaforo.h"
#include "../../comun/GestorArch.h"
#include "../../comun/ColaMensajes.h"

#include <stdlib.h>

/************************************************************************/

namespace LgSala {
	enum LugarSala {
		PIE = 0,
		CIMA  = 1
	};
};

namespace TpAgente {
	enum TipoAgente {
		CABLE_CARRIL = 0,
		PERSONA = 1
	};
};

namespace MtdSala {
	enum MetodoSala {

		// Para metodos de la Persona
		HAY_LUGAR  = 0,
		ESPERAR_POR_LUGAR = 1,
		HACER_COLA = 2,
		SUBIR_CC = 3,

		// Para metodos del Cable Carril
		SALA_VACIA = 10,
		SACAR_PERSONA_COLA,
		SUBIR_PERSONA,
		BAJAR_PERSONA,


		CERRAR

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
	int numCC;
	LgSala::LugarSala lugar;


	res resultado;

} stMensaje;

#define TAM_MSJ_COLA	(sizeof(stMensaje) - sizeof(long int))


typedef struct {
	long _mtype;

	int numCC;
	int numPersona;
} stMensajeBloqueo;

#define TAM_MSJ_BLQ		(sizeof(stMensajeBloqueo) - sizeof(long int))


#define TAM_SALA_ESP	5

typedef int NumeroPersonaSala;

namespace EstLugar {
	enum EstadoLugar {
		VACIO,
		OCUAPADO
	};
};

#define CANT_PAJ_CC		50




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

#define RUTA_COLA_BLQ RUTA_COLA


#define ID_COLA_MSJ		'a'
#define ID_COLA_BLQ		'b'

#define ID_SEM_MTX_CIMA		'b'
#define ID_SEM_LLENO_CIMA	'c'
#define ID_SEM_VACIO_CIMA	'j'

#define ID_SEM_MTX_PIE		'e'
#define ID_SEM_LLENO_PIE	'f'
#define ID_SEM_VACIO_PIE	'k'

#define ID_MEM_COMP		'g'

#define ID_MEMC_SALA_PIE		'h'
#define ID_MEMC_SALA_CIMA		'i'


/************************************************************************/

// Identificadores


#define ID_PRODUCTOR_0		40000

#define ID_PERSONA_0		3000
#define ID_COMP_PERSONA_0	30000

#define ID_CC				1000
#define ID_CC_COMP			2000

#define IdPersona(numPersona)		(ID_PERSONA_0 + numPersona)
#define IdPersonaComp(numPersona)	(ID_COMP_PERSONA_0 + numPersona)

#define IdCableCarril(numCC)		(ID_CC + numCC)
#define IdCablaCarrilComp(numCC)	(ID_CC_COMP + numCC)

/************************************************************************/
// Etiquetas para el archivo de configuracion

#define ET_CANT_CC			"CANT_CC"
#define ET_PERSONAS_PROD	"CANT_PERS"

/************************************************************************/

#define TIEMPO_TRABAJO		1000000

#define FRANDOM		( ((float) rand()) / ((float) RAND_MAX) )

#endif /* DEFINICIONES_H_ */
