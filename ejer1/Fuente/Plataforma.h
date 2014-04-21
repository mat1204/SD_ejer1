/*
 * Plataforma.h
 *
 *  Created on: 20/04/2014
 *      Author: migue
 */

#ifndef PLATAFORMA_H_
#define PLATAFORMA_H_

#include "SemRobots.h"
#include "MemoriaCompartida.h"

class Plataforma {
public:
	Plataforma(int numeroRobot = -1);

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

	int estadoRobotFrec();
	int estadoRobotArmar();

	void estadoRobotArmar(EstRobotArmar::EstadoRobotArmar estado);
	void estadoRobotFrec(EstRobotFrec::EstadoRobotFrec estado);


	void waitMutex()		{ _mutex->wait(0); }
	void signalMutex()	{ _mutex->signal(0); }

	void waitRobotFrec() 		{ _semsFrec->wait(_posRobotActual); 	}
	void signalRobotFrec() 	{ _semsFrec->signal(_posRobotActual); 	}

	void waitRobotArmar() 	{ _semsArmar->wait(_posRobotActual);	}
	void signalRobotArmar() 	{ _semsArmar->signal(_posRobotActual); 	}

	void colocarEnLugar(int posicion, const LugarPlataforma& lugar);
	void verLugar(int posicion, LugarPlataforma& lugar);

	bool armadoresTerminaron();
	bool hayDispositivosActivos();
	bool sacarDispositivo(int& numeroDispositivo);

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
	int _ocupados;
	int _libres;
};

#endif /* PLATAFORMA_H_ */
