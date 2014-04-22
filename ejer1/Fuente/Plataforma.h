/*
 * Plataforma.h
 *
 *  Created on: 20/04/2014
 *      Author: migue
 */

#ifndef PLATAFORMA_H_
#define PLATAFORMA_H_

#include "Definiciones.h"

#include "SemRobots.h"
#include "MemoriaCompartida.h"


class Plataforma {
public:
	Plataforma(int numeroRobot = -1);

	/**
	 * Retorna true si logra activar un dispositvo
	 */
	bool activarDispositivoAlAzar();

	/**
	 * Para robot de Frecuencia
	 */

	bool seguirTrabajando();

	bool detectarFrecuencia();

	bool sacarDispositivo(int& numDispositivo);

	/**
	 * Para robot de Armado
	 */

	bool plataformaLlena();

	void esperar();

	bool colocarDispositivo(int numDispositivo);

	void inicializar();

	virtual ~Plataforma();
private:

	EstRobotFrec::EstadoRobotFrec estadoRobotFrec();
	EstRobotArmar::EstadoRobotArmar estadoRobotArmar();

	void estadoRobotArmar(EstRobotArmar::EstadoRobotArmar estado);
	void estadoRobotFrec(EstRobotFrec::EstadoRobotFrec estado);


	//
	void waitMutex()		{ _mutex->wait(0); }
	void signalMutex()	{ _mutex->signal(0); }

	void waitRobotFrec() 		{ _semsFrec->wait(_posRobotActual); 	}
	void signalRobotFrec() 	{ _semsFrec->signal(_posRobotActual); 	}

	void waitRobotArmar() 	{ _semsArmar->wait(_posRobotActual);	}
	void signalRobotArmar() 	{ _semsArmar->signal(_posRobotActual); 	}

	// para lugares de la plataforma
	void colocarEnLugar(int posicion, const LugarPlataforma& lugar);
	void verLugar(int posicion, LugarPlataforma& lugar);

	// para robots de frecuencia
	bool armadoresTerminaron();
	bool hayDispositivosActivos();
	bool primSacarDispositivo(int& numeroDispositivo);


	bool reservarLugar();
	bool primColocarDispositivo(int numDipositivo);

	int _numeroRobot;

	SemRobots *_mutex, *_semsArmar, *_semsFrec;
	SalidaPorPantalla *_salida;

	int _capacidadPlataforma, _cantRobots;


	// para manejo de memoria compartida

	MemoriaCompartida *_memoriaLugares;
	int _posRobotActual;
	int _posEstArmar;
	int _posEstFrec;
	int _posLugares;


	// para manejo de plataforma

	int _capacidad;
	int _posOcupados;
	int _posLibres;
	int _posActivados;
	int _posArmFinalizados;

	int capacidad();

	// retorna valor actual o, suma cantidad parametro retornado el valor posterior
	int lugaresLibres(int x = 0) { return variableMemComp(_posLibres, x); }
	int lugaresOcupados(int x = 0) { return variableMemComp(_posOcupados, x); }
	int lugaresActivados(int x = 0) { return variableMemComp(_posActivados, x); }
	int armadoresFinalizados(int x = 0) { return variableMemComp(_posArmFinalizados, x); }

	int variableMemComp(int posicion, int x);
};

#endif /* PLATAFORMA_H_ */