/*
 * Plataforma.cpp
 *
 *  Created on: 20/04/2014
 *      Author: migue
 */

#include "Plataforma.h"
#include "ArchConfiguracion.h"
#include <stdlib.h>

/**
 *
 *
 *
 *  esquema de memoria para la plataforma
 *
 *  --------------------------------------------
 * 	| EstRobotsArmar | EstRobotsFrec | Lugares |
 *  --------------------------------------------
 *
 */


Plataforma::Plataforma(int numeroRobot) {
	_numeroRobot = numeroRobot;
	_salida = &SalidaPorPantalla::instancia();

	int totalMemoria;

	{
		ArchConfiguracion config;

		if (config.leer(ET_CAPCIDAD_PLAT, _capacidadPlataforma) == false) {
			_salida->error("No se pudo leer capacidad de plataforma");
			exit(EXIT_FAILURE);
		}

		if (config.leer(ET_CANT_ROBOTS, _cantRobots) == false) {
			_salida->error("No se pudo leer cantidad de robots");
			exit(EXIT_FAILURE);
		}

		totalMemoria = _capacidadPlataforma * sizeof(LugarPlataforma) +
				_cantRobots * (sizeof(EstRobotFrec::EstadoRobotFrec) + sizeof(EstRobotArmar::EstadoRobotArmar));
	}

	_capacidad = _capacidadPlataforma;
	_ocupados = 0;
	_libres = 0;


	_posRobotActual = numeroRobot;
	_memoriaLugares = new MemoriaCompartida(totalMemoria);

	_posEstArmar = 0;
	_posEstFrec = _cantRobots * sizeof(EstRobotArmar::EstadoRobotArmar);
	_posLugares = _posEstFrec + (_cantRobots * sizeof(EstRobotFrec::EstadoRobotFrec));


	_semsArmar = new SemRobots(_cantRobots, ID_SEMS_ARMAR);
	_semsFrec = new SemRobots(_cantRobots, ID_SEMS_FREC);
	_mutex = new SemRobots(_cantRobots, ID_SEM_MUTEX);

}

Plataforma::~Plataforma() {
	delete _memoriaLugares;

	delete _mutex;
	delete _semsArmar;
	delete _semsFrec;
}


int Plataforma::estadoRobotFrec() {
	EstRobotFrec::EstadoRobotFrec estado;

	int posicion = _posEstFrec + _posRobotActual * sizeof(estado);

	_memoriaLugares->leer(posicion, (void*) &estado, sizeof(estado));

	return estado;
}
int Plataforma::estadoRobotArmar() {
	EstRobotArmar::EstadoRobotArmar estado;

	int posicion = _posEstArmar + _posRobotActual * sizeof(estado);

	_memoriaLugares->leer(posicion, (void*) &estado, sizeof(estado));

	return estado;
}

void Plataforma::estadoRobotArmar(EstRobotArmar::EstadoRobotArmar estado) {
	int posicion = _posEstArmar + _posRobotActual * sizeof(estado);
	_memoriaLugares->escribir(posicion, (void*) &estado, sizeof(estado));
}

void Plataforma::estadoRobotFrec(EstRobotFrec::EstadoRobotFrec estado) {
	int posicion = _posEstFrec + _posRobotActual * sizeof(estado);
	_memoriaLugares->escribir(posicion, (void*) &estado, sizeof(estado));
}

void Plataforma::inicializar() {
	for (int i = 0; i < _cantRobots ; i++) {
		estadoRobotArmar(EstRobotArmar::OCUPADO);
		estadoRobotFrec(EstRobotFrec::OCUPADO);
	}

	LugarPlataforma lugar;

	lugar.lugar = EstadoLugarPlataforma::VACIO;
	lugar.numDispositivo = 0;

	for (int i = 0; i < _capacidadPlataforma ; i++) {
		colocarEnLugar(i, lugar);
	}


	// inicializacion de semaforos

	_semsArmar->inicializar(1);
	_semsFrec->inicializar(0);

	_mutex->inicializar(1);
}

void Plataforma::colocarEnLugar(int pos, const LugarPlataforma& lugar) {
	int posicion = _posLugares + pos * sizeof(lugar);
	_memoriaLugares->escribir(posicion, (void*) &lugar, sizeof(lugar));
}

void Plataforma::verLugar(int pos, LugarPlataforma& lugar) {
	int posicion = _posLugares + pos * sizeof(lugar);
	_memoriaLugares->leer(posicion, (void*) &lugar, sizeof(lugar));
}


bool Plataforma::hayDispositivosActivos() {
	bool detectado = false;
	int i = 0;

	LugarPlataforma lugar;
	int tamLugar = sizeof(lugar);

	while (!detectado && i < _capacidad) {
		_memoriaLugares->leer(i, (void*) &lugar, tamLugar);

		detectado = (lugar.lugar == EstadoLugarPlataforma::ENCENDIDO);

		++i;
	}

	return detectado;
}


bool Plataforma::sacarDispositivo(int& numDisp) {
	bool encontrado = false;
	int i = 0;

	LugarPlataforma lugar;
	int tamLugar = sizeof(lugar);

	while (!encontrado && i < _capacidad) {
		_memoriaLugares->leer(i, (void*) &lugar, tamLugar);
		encontrado = (lugar.lugar == EstadoLugarPlataforma::ENCENDIDO);
		++i;
	}

	return encontrado;
}

/**
 *
 *
 * Metodos con los usos de IPCs
 *
 *
 */

/**
 * Para robot de Frec
 */

bool Plataforma::seguirTrabajando() {
	waitMutex();

	bool seguir = true;

	// Si plataforma vacia ...
	if (_ocupados == 0) {
		if (armadoresTerminaron()) {
			estadoRobotFrec(EstRobotFrec::FINALIZADO);
			seguir = false;
		}
	}

	signalMutex();

	return seguir;
}

bool Plataforma::detectarFrecuencia() {
	bool detectada = false;

	waitMutex();

	EstRobotArmar::EstadoRobotArmar est = estadoRobotArmar();

	if (est == EstRobotArmar::ARMANDO || est == EstRobotArmar::OCUPADO) {
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
		signalMutex();
		waitRobotFrec();
	}
	else {
		signalMutex();
	}

	detectada = hayDispositivosActivos();

	if (detectada == false) {
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
		signalMutex();
		waitRobotFrec();
	}
	else {
		signalMutex();
	}

	return detectada;
}

bool Plataforma::sacarDispositivo(int& numDispositivo) {
	waitMutex();

	EstRobotArmar::EstadoRobotArmar est = estadoRobotArmar();

	if (est == EstRobotArmar::ARMANDO) {
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
		signalMutex();
		waitRobotFrec();

		waitMutex();
		estadoRobotFrec(EstRobotFrec::OCUPADO);
	}

	bool sacado = sacarDispositivo(numDispositivo);

	// si no se saco dispositivo
	if ( sacado == false) {
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
		signalMutex();
		signalRobotArmar();

		waitRobotFrec();

		waitMutex();
		estadoRobotFrec(EstRobotFrec::OCUPADO);
	}
	else {
		signalMutex();
	}

	return sacado;
}

/**
 * Para robot de Armado
 */

bool Plataforma::plataformaLlena() {

}

void Plataforma::esperar() {

}

bool Plataforma::colocarDispositivo(int numDispositivo) {

}
