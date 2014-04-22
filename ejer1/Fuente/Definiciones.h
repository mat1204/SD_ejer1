/*
 * Definiciones.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

/************************************************************************************/
/**
 *  Macro utilizadda para cambiar entorno de compilacion
 */
#define COMP_UBUNTU

/************************************************************************************/
namespace MdRobot {
	enum ModoRobot {
		ARMADOR,
		DET_FRECUENCIA
	};
};

/************************************************************************************/

typedef struct {


} stPlataforma;


/************************************************************************************/
/**
 * Metodos que se pueden consultar en la plataforma
 */

namespace MtdPlataforma {
	enum MetodoPlataforma {
		PLATAFORMA_LLENA,
		RESERVAR_LUGAR,
		HAY_DISP_ACTIVOS,
		COLOCAR_DISP,


		SACAR_DISP,
		DETERCAR_FREC,
		ESTADO_ROBOT_FREC,
		ROBOT_FREC,
		ESTADO_ROBOT_ARMAR,
		ROBOT_ARMAR,
		ROBOTS_FINALIZADOS,

		// Nuevos

		SEGUIR_TRABAJANDO_FREC,
		ESPERAR
	};
}

namespace EstRobotFrec {
	enum EstadoRobotFrec {
		ESPERANDO = 0,
		OCUPADO,
		FINALIZADO
	};
}


namespace EstRobotArmar {
	enum EstadoRobotArmar {
		ESPERANDO = 0,
		OCUPADO,
		ARMANDO,
		FINALIZADO
	};
}


typedef union {
	int entero;
	bool booleano;
} _resultado_;

typedef struct {
	long int _tipo;

	MtdPlataforma::MetodoPlataforma metodo;
	int numRobot;
	int idRobot;
	int numDispositivo;

	_resultado_ resultado;

} MensajeCola;

#define TAM_MENSAJE_COLA (sizeof(MensajeCola) - sizeof(long int))

#ifndef COMP_UBUNTU

	#define RUTA_ARCH_COLA	"/home/knoppix/cola"
	#define RUTA_ARCH_SEMAFOROS "/home/knoppix/semaforos"

#else

	#define RUTA_ARCH_COLA	"/home/migue/cola"
	#define RUTA_ARCH_SEMAFOROS "/home/migue/semaforos"

#endif

#define ID_SEMS_FREC 'a'
#define ID_SEMS_ARMAR 'b'
#define ID_SEM_MUTEX 'c'

namespace EstadoLugarPlataforma {
	enum EstadoLugarPlataforma {
		VACIO = 0,
		OCUPADO,
		RESERVADO,
		ENCENDIDO
	};
}

typedef struct {
	EstadoLugarPlataforma::EstadoLugarPlataforma lugar;
	int numDispositivo;
} LugarPlataforma;


#define ID_PLATAFORMA 5
#define ID_ROBOT_0 100

#define ID_COMP_0 10000

#define idRobotArmar(X) ((X*2) + ID_ROBOT_0)
#define idRobotFrec(X) ((X*2) + 1 + ID_ROBOT_0)

#define idRobotArmarComp(X)		((X*2) + ID_COMP_0)
#define idRobotFrecComp(X)		((X*2) + 1 + ID_COMP_0)

#define numeroDeRobot(IdRobot) ((IdRobot - ID_ROBOT_0)/2)


/**
 * Etiquetas para el archivo de configuracion
 *
 */

#define ET_CAPCIDAD_PLAT	"CAPACIDAD_PLATAFORMA"
#define ET_CANT_ROBOTS		"CANTIDAD_ROBOTS"
#define ET_DISP_ROBOT		"DISP_ROBOT_"
#define ET_PILAS_ROBOT		"PILAS_ROBOT_"


#define TIEMPO_TRABAJO    100

#endif /* DEFINICIONES_H_ */
