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
#include <iostream>

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
		SalidaPorPantalla::instancia().mostrar("Armador Finalizado");
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
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
	}

	_posRobotActual = aux;

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

	while (!encontrado && i < _capacidad) {

		verLugar(i, lugar);

		if (lugar.lugar == EstadoLugarPlataforma::ENCENDIDO) {
			encontrado = true;
			numDisp = lugar.numDispositivo;

			lugar.lugar = EstadoLugarPlataforma::VACIO;
			lugar.numDispositivo = 0;

			colocarEnLugar(i, lugar);

			lugaresOcupados(-1);
			lugaresActivados(-1);
			lugaresLibres(1);
		}
		++i;
	}

	return encontrado;
}

bool Plataforma::primColocarDispositivo(int numDispotivo) {
	bool colocado = false;


	LugarPlataforma lugar;
	int tamLugar = sizeof(lugar);


	int i = 0;
	while (!colocado && i < _capacidad) {
		//_memoriaLugares->leer(i, (void*) &lugar, tamLugar);
		verLugar(i , lugar);

		if (lugar.lugar == EstadoLugarPlataforma::RESERVADO) {
			colocado = true;

			lugar.lugar = EstadoLugarPlataforma::OCUPADO;
			lugar.numDispositivo = numDispotivo;
			//_memoriaLugares->escribir(i, (void*) &lugar, tamLugar);
			colocarEnLugar(i, lugar);

			lugaresOcupados(1);
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

			lugaresLibres(-1);
		}

		++i;
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

	waitMutex();
	EstRobotFrec::EstadoRobotFrec estActual = estadoRobotFrec();

	EstRobotArmar::EstadoRobotArmar estArmador = estadoRobotArmar();


	/**
	 * Condicion necesario por si plataforma esta llena, quiere decir que se quedo ocupado,
	 * no paso el turno al robot de armar y ademas hasta este punto no habia ningun
	 * dispositivo encendido. Pero se salta la condicion y sigue trabajando si el armador
	 * ha finalizado.
	 */
	if (estActual == EstRobotFrec::ESPERANDO && estArmador != EstRobotArmar::FINALIZADO) {
		signalMutex();

		SalidaPorPantalla::instancia().mostrar("Esperando turno (al inicio)");
		waitRobotFrec();

		waitMutex();
	}

	//waitMutex();

	estadoRobotFrec(EstRobotFrec::OCUPADO);

	estArmador = estadoRobotArmar();

	if (estArmador == EstRobotArmar::ARMANDO || estArmador == EstRobotArmar::OCUPADO) {
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
		signalMutex();
		SalidaPorPantalla::instancia().mostrar("Armador ocupado");
		waitRobotFrec();

		// se despierta
		waitMutex();
		estadoRobotFrec(EstRobotFrec::OCUPADO);
	}


	bool activos = hayDispositivosActivos();

	bool plataformaLlena = (lugaresLibres() == 0);

	if (activos) {
		SalidaPorPantalla::instancia().mostrar("HAY dispositivos activos");
		signalMutex();
	}
	else if (plataformaLlena == false) {
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
		signalMutex();

		SalidaPorPantalla::instancia().mostrar("NO hay dispositivos activos");


		/*
		 * Si el armador no finalizo le paso el turno
		 */
		if (estArmador != EstRobotArmar::FINALIZADO)
			signalRobotArmar();

	}
	else {
		SalidaPorPantalla::instancia().mostrar("Plataforma llena y NO hay dispositivos activos");
		estadoRobotFrec(EstRobotFrec::OCUPADO);
		signalMutex();
	}


	return activos;

}

bool Plataforma::sacarDispositivo(int& numDispositivo) {
	waitMutex();

	bool sacado = primSacarDispositivo(numDispositivo);

	estadoRobotFrec(EstRobotFrec::ESPERANDO);

	signalRobotArmar();

	signalMutex();

	return sacado;
}


/**
 *
 * Para robot de Armado
 *
 */

bool Plataforma::plataformaLlena() {
	SalidaPorPantalla::instancia().mostrar("Esperando turno (al inicio)");
	waitRobotArmar();

	waitMutex();

	estadoRobotArmar(EstRobotArmar::OCUPADO);

	EstRobotFrec::EstadoRobotFrec est = estadoRobotFrec();

	if (est == EstRobotFrec::OCUPADO) {
		estadoRobotArmar(EstRobotArmar::ESPERANDO);
		signalMutex();

		SalidaPorPantalla::instancia().mostrar("Robot Frecuencia Ocupado");
		waitRobotArmar();

		// se desperto
		waitMutex();
		estadoRobotArmar(EstRobotArmar::OCUPADO);
	}

	bool llena;

	do {

		llena = (this->lugaresLibres() == 0);

		if (llena == false) {
			reservarLugar();
			signalMutex();
		}
		else {
			estadoRobotArmar(EstRobotArmar::ESPERANDO);
			signalMutex();

			SalidaPorPantalla::instancia().mostrar("Plataforma llena, pasando a frec");
			signalRobotFrec();
			waitRobotArmar();

			// se desperto
			waitMutex();
			estadoRobotArmar(EstRobotArmar::OCUPADO);
		}

	}
	while (llena);

	return llena;
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

	bool colocado = primColocarDispositivo(numDispositivo);

	estadoRobotArmar(EstRobotArmar::ESPERANDO);

	signalRobotFrec();

	signalMutex();

	return colocado;
}

bool Plataforma::activarDispositivo(int posicion) {
	if (posicion >= _capacidad)
		return false;

	LugarPlataforma lugar;

	waitMutex();

	verLugar(posicion, lugar);
	bool activado = false;

	if (lugar.lugar == EstadoLugarPlataforma::OCUPADO) {
		lugar.lugar = EstadoLugarPlataforma::ENCENDIDO;

		this->colocarEnLugar(posicion, lugar);
		activado = true;

		lugaresActivados(1);

		_salida->mostrar("Activado dispositivo en la posicion ", posicion);
	}

	signalMutex();

	return activado;
}

int Plataforma::capacidad() {
	return _capacidad;
}

void Plataforma::mostrarLugares() {
	waitMutex();

	LugarPlataforma lugar;

	std::cout << "Libres: " << lugaresLibres() << std::endl;
	std::cout << "Ocupados: " << lugaresOcupados() << std::endl;
	std::cout << "Activados: " << lugaresActivados() << std::endl;
	std::cout << "Armadores finalizados: " << armadoresFinalizados() << std::endl;
	std::cout << std::endl;


	for ( int i = 0; i < _capacidad ; ++i ) {
		std::cout << i << " - ";

		verLugar(i, lugar);

		switch (lugar.lugar) {
			case EstadoLugarPlataforma::ENCENDIDO:
				std::cout << "(+) ; ENCENDIDO";	 break;

			case EstadoLugarPlataforma::OCUPADO:
				std::cout << "(0) ; OCUPADO";	 break;

			case EstadoLugarPlataforma::RESERVADO:
				std::cout << "(R) ; RESERVADO";	 break;

			case EstadoLugarPlataforma::VACIO:
				std::cout << "( ) ; VACIO";	 break;

			default:
				signalMutex();
				std::cout << "??INVALIDO"; break;
		}
		std::cout << std::endl;
	}

	signalMutex();
}

void Plataforma::mostrarRobots() {
	waitMutex();

	EstRobotArmar::EstadoRobotArmar estA;
	EstRobotFrec::EstadoRobotFrec estF;

	int aux = _posRobotActual;

	for ( int i = 0; i < _cantRobots ; ++i) {
		_posRobotActual = i;

		estA = estadoRobotArmar();
		estF = estadoRobotFrec();

		std::cout << "Robot-" << i << " ";


		std::cout << "Armador: ";

		switch (estA) {
			case EstRobotArmar::ARMANDO:
				std::cout << "ARMANDO";	break;
			case EstRobotArmar::ESPERANDO:
				std::cout << "ESPERANDO"; 	break;

			case EstRobotArmar::FINALIZADO:
				std::cout << "**FINALIZADO**"; 	break;

			case EstRobotArmar::OCUPADO:
				std::cout << "OCUPADO"; 	break;

			default:
				std::cout << "??INVALIDO";	break;
		}

		std::cout << ";\t Frecuencia: ";

		switch (estF) {
			case EstRobotFrec::ESPERANDO:
				std::cout << "ESPERANDO"; break;

			case EstRobotFrec::FINALIZADO:
				std::cout << "**FINALIZADO**"; break;

			case EstRobotFrec::OCUPADO:
				std::cout << "OCUPADO"; break;

			default:
				std::cout << "??INVALIDO";	break;
		}


		std::cout << std::endl;
	}

	_posRobotActual = aux;
	signalMutex();
}


void Plataforma::finDeArmador() {
	waitMutex();
	estadoRobotArmar(EstRobotArmar::FINALIZADO);
	signalMutex();
}
