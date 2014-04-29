/*
 * Plataforma.cpp
 *
 *  Created on: 20/04/2014
 *      Author: migue
 */

#include "Plataforma.h"
#include "ArchConfiguracion.h"
#include "../../comun/SalidaPorPantalla.h"
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
				_cantRobots * (sizeof(EstRobotFrec::EstadoRobotFrec) + sizeof(EstRobotArmar::EstadoRobotArmar)) +
				4 * sizeof(int);
	}

	_capacidad = _capacidadPlataforma;


	_posRobotActual = numeroRobot;
	_memoriaLugares = new MemoriaCompartida(RUTA_ARCH_COLA, 'a', totalMemoria);


	// Creacion de indices
	_posOcupados = 0;
	_posLibres = _posOcupados + sizeof(int);
	_posActivados = _posLibres + sizeof(int);
	_posArmFinalizados = _posActivados + sizeof(int);

	_posEstArmar = _posArmFinalizados + sizeof(int);

	_posEstFrec = _posEstArmar + (_cantRobots * sizeof(EstRobotArmar::EstadoRobotArmar));
	_posLugares = _posEstFrec + (_cantRobots * sizeof(EstRobotFrec::EstadoRobotFrec));


	// creacion de semaforos
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


EstRobotFrec::EstadoRobotFrec Plataforma::estadoRobotFrec() {
	EstRobotFrec::EstadoRobotFrec estado;

	int posicion = _posEstFrec + _posRobotActual * sizeof(estado);

	_memoriaLugares->leer(posicion, (void*) &estado, sizeof(estado));

	return estado;
}
EstRobotArmar::EstadoRobotArmar Plataforma::estadoRobotArmar() {
	EstRobotArmar::EstadoRobotArmar estado;

	int posicion = _posEstArmar + _posRobotActual * sizeof(estado);

	_memoriaLugares->leer(posicion, (void*) &estado, sizeof(estado));

	return estado;
}

void Plataforma::estadoRobotArmar(EstRobotArmar::EstadoRobotArmar estado) {
	int posicion = _posEstArmar + _posRobotActual * sizeof(estado);
	_memoriaLugares->escribir(posicion, (void*) &estado, sizeof(estado));
	if (estado == EstRobotArmar::FINALIZADO) {
		armadoresFinalizados(1);
		SalidaPorPantalla::instancia().mostrar("Armador Finalizao");
	}
}

void Plataforma::estadoRobotFrec(EstRobotFrec::EstadoRobotFrec estado) {
	int posicion = _posEstFrec + _posRobotActual * sizeof(estado);
	_memoriaLugares->escribir(posicion, (void*) &estado, sizeof(estado));
}

void Plataforma::inicializar() {

	// Inicializacion de variables
	int valor = 0;
	_memoriaLugares->escribir(_posOcupados, (void*) &valor, sizeof(int));

	_memoriaLugares->escribir(_posActivados, (void*) &valor, sizeof(int));

	_memoriaLugares->escribir(_posArmFinalizados, (void*) &valor, sizeof(int));

	valor = _capacidad;
	_memoriaLugares->escribir(_posLibres, (void*) &valor, sizeof(int));


	// Inicializacion de estados de robots
	int aux = _posRobotActual;
	for (int i = 0; i < _cantRobots ; i++) {
		_posRobotActual = i;
		estadoRobotArmar(EstRobotArmar::OCUPADO);
		estadoRobotFrec(EstRobotFrec::OCUPADO);
	}

	_posRobotActual = aux;

	LugarPlataforma lugar;

	lugar.lugar = EstadoLugarPlataforma::VACIO;
	lugar.numDispositivo = 0;

	for (int i = 0; i < _capacidadPlataforma ; i++) {
		colocarEnLugar(i, lugar);
	}


	// inicializacion de semaforos

	_semsArmar->inicializar(0);
	_semsFrec->inicializar(0);

	_mutex->inicializar(1);
}

void Plataforma::destruir() {
	_semsArmar->destruir();
	_semsFrec->destruir();

	_mutex->destruir();

	_memoriaLugares->destruir();
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
	return (lugaresActivados() > 0);

	/*
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
	*/
}


bool Plataforma::primSacarDispositivo(int& numDisp) {
	bool encontrado = false;
	int i = 0;

	LugarPlataforma lugar;
	int tamLugar = sizeof(lugar);

	while (!encontrado && i < _capacidad) {
		_memoriaLugares->leer(i, (void*) &lugar, tamLugar);
		if (lugar.lugar == EstadoLugarPlataforma::ENCENDIDO) {
			encontrado = true;
			numDisp = lugar.numDispositivo;
			lugar.numDispositivo = 0;

			lugaresOcupados(-1);
			lugaresLibres(1);
		}
		++i;
	}

	return encontrado;
}

bool Plataforma::primColocarDispositivo(int numDispotivo) {
	bool colocado = false;
	int i = 0;

	LugarPlataforma lugar;
	int tamLugar = sizeof(lugar);

	while (!colocado && i < _capacidad) {
		_memoriaLugares->leer(i, (void*) &lugar, tamLugar);

		if (lugar.lugar == EstadoLugarPlataforma::RESERVADO) {
			colocado = true;

			lugar.lugar = EstadoLugarPlataforma::OCUPADO;
			lugar.numDispositivo = numDispotivo;
			_memoriaLugares->escribir(i, (void*) &lugar, tamLugar);

			lugaresOcupados(1);
			lugaresLibres(-1);

		}

		++i;
	}

	return colocado;
}

bool Plataforma::reservarLugar() {

	bool reservado = false;
	int i = 0;


	LugarPlataforma lugar;
	while (!reservado && i < _capacidad) {
		verLugar(i, lugar);

		if (lugar.lugar == EstadoLugarPlataforma::VACIO) {
			lugar.lugar = EstadoLugarPlataforma::RESERVADO;
			reservado = true;
			colocarEnLugar(i, lugar);
		}
	}

	return reservado;
}

int Plataforma::variableMemComp(int posicion, int x) {
	int valor;

	_memoriaLugares->leer(posicion, (void*) &valor, sizeof(int));

	if ( x != 0 ) {
		valor += x;
		_memoriaLugares->escribir(posicion, (void*) &valor, sizeof(int));
	}

	return valor;
}


void Plataforma::mostrarVariables() {
	SalidaPorPantalla::instancia().agregarAlMsj("Lugares libres: ", lugaresLibres());
	SalidaPorPantalla::instancia().agregarAlMsj(", ocupados: ", lugaresOcupados());
	SalidaPorPantalla::instancia().agregarAlMsj(", activados: ", lugaresActivados());
	SalidaPorPantalla::instancia().agregarAlMsj(", Armadores Finalizados: ", armadoresFinalizados());

	SalidaPorPantalla::instancia().mostrarMsj();
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
	if (lugaresOcupados() == 0) {
		if (armadoresFinalizados() == _cantRobots) {
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

		waitMutex();
	}
//	else {
//		signalMutex();
//	}

	detectada = hayDispositivosActivos();

	if (detectada == false) {
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
		signalMutex();

		signalRobotArmar();

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

		signalRobotArmar();

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
 *
 * Para robot de Armado
 *
 */

bool Plataforma::plataformaLlena() {
	waitMutex();

	mostrarVariables();

	EstRobotFrec::EstadoRobotFrec est = estadoRobotFrec();

	if (est == EstRobotFrec::OCUPADO) {
		estadoRobotArmar(EstRobotArmar::ESPERANDO);
		signalMutex();

		signalRobotFrec();

		waitRobotArmar();
		waitMutex();
	}

	estadoRobotArmar(EstRobotArmar::OCUPADO);

	bool llena = (lugaresLibres() == 0);

	if (llena == false) {
		if (reservarLugar()) {
			estadoRobotArmar(EstRobotArmar::ARMANDO);
		}
	}

	signalMutex();
}

void Plataforma::esperar() {
	waitMutex();
	estadoRobotArmar(EstRobotArmar::ESPERANDO);
	signalMutex();

	signalRobotFrec();
	waitRobotArmar();

	waitMutex();
	estadoRobotArmar(EstRobotArmar::OCUPADO);
	signalMutex();
}

bool Plataforma::colocarDispositivo(int numDispositivo) {
	waitMutex();

	bool colocado;

	colocado = primColocarDispositivo(numDispositivo);

	estadoRobotArmar(EstRobotArmar::ESPERANDO);

	signalMutex();

	signalRobotFrec();

	waitRobotArmar();

	return colocado;
}


