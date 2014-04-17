/*
 * PlataformaReal.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#include "PlataformaReal.h"
#include "Definiciones.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


PlataformaReal::PlataformaReal(int capacidad, int cantRobots) {
	_capacidad = capacidad;
	_ocupados = 0;
	_reservados = 0;
	_activados = 0;

	_sacados = 0;
	_colocados = 0;

	_cantRobots = cantRobots;

	SalidaPorPantalla::instancia().etiqueta("PLATAFORMA", -1);

	if (_capacidad > 0 && _cantRobots > 0) {
		_lugares = new LugarPlataforma[_capacidad];

		_estadosArmar = new EstRobotArmar::EstadoRobotArmar[_cantRobots];
		_estadosFrec = new EstRobotFrec::EstadoRobotFrec[_cantRobots];

		for ( int i = 0; i < _capacidad ; i++) {
			_lugares[i].lugar = EstadoLugarPlataforma::VACIO;
		}

		for (int i = 0; i < _cantRobots ; i++) {
			_estadosArmar[i] = EstRobotArmar::OCUPADO;
			_estadosFrec[i] = EstRobotFrec::OCUPADO;
		}

		SalidaPorPantalla::instancia().mostrar("Se inicializo correctamente la plataforma.");

	}
	else {
		SalidaPorPantalla::instancia().error("Error en la cantidad de lugares de la plataforma y el numero de robots, debe ser >0.");
		exit(2);
	}

	_salida = &SalidaPorPantalla::instancia();

}

PlataformaReal::~PlataformaReal() {
	delete[] _lugares;
	delete[] _estadosArmar;
	delete[] _estadosFrec;
}

int PlataformaReal::iniciar() {
	_salida->mostrar("inicia plataforma con cantaidad de robots:", _cantRobots);
	_salida->mostrar("Capacidad de la plataforma: ", _capacidad);


	for (;;) {

		esperarMensaje();

		MtdPlataforma::MetodoPlataforma metodo = _ultimoMsjRcv.metodo;

//		_salida->agregarAlMsj("Se recibio Mensaje del Robot");
//		_salida->agregarAlMsj(_ultimoMsjRcv.numRobot);
//		_salida->mostrarMsj();

		switch (metodo) {
			case MtdPlataforma::RESERVAR_LUGAR: 	reservarLugar(); 			break;
			case MtdPlataforma::SACAR_DISP: 		sacarDispositivo(); 		break;

			case MtdPlataforma::COLOCAR_DISP: 	colocarDispositivo(); 		break;
			case MtdPlataforma::DETERCAR_FREC: 	detectarFrecuencia();		break;
			case MtdPlataforma::PLATAFORMA_LLENA: plataformaLlena();			break;

			case MtdPlataforma::ESTADO_ROBOT_ARMAR: estadoRobot(); 			break;
			case MtdPlataforma::ESTADO_ROBOT_FREC: estadoRobot(); 			break;
			case MtdPlataforma::HAY_DISP_ACTIVOS: hayDispositivosActivos(); 	break;

			case MtdPlataforma::ROBOT_ARMAR: modificarRobot(); 				break;
			case MtdPlataforma::ROBOT_FREC: modificarRobot(); 				break;

			case MtdPlataforma::ROBOTS_FINALIZADOS: robotsFinalizados(); 	break;

			default: break;
		};

		activarDispositivosAlAzar();
	}
	return 0;
}


void PlataformaReal::esperarMensaje() {
	_cola.recibir(_ultimoMsjRcv, ID_PLATAFORMA);
	//SalidaPorPantalla::instancia().mostrar("Se recibio un mensaje en la plataforma");
}

void PlataformaReal::colocarDispositivo() {

	_salida->mostrar("Se recibio mensaje de COLOCAR_DISP de Robot-", _ultimoMsjRcv.numRobot);

	bool colocado = false;
	int i = 0;

	while (!colocado && i < _capacidad) {
		if ( _lugares[i].lugar == EstadoLugarPlataforma::RESERVADO ) {
			colocado = true;
			_lugares[i].lugar = EstadoLugarPlataforma::OCUPADO;
			_lugares[i].numDispositivo = _ultimoMsjRcv.numDispositivo;

			_salida->agregarAlMsj("Se coloco Dispositivo de robot-");
			_salida->agregarAlMsj(_ultimoMsjRcv.numRobot);
			_salida->agregarAlMsj(", n°");
			_salida->agregarAlMsj(_ultimoMsjRcv.numDispositivo);
			_salida->mostrarMsj();

			++_ocupados;
			--_reservados;
			++_colocados;

		}
		else
			i++;
	}


	prepararEnvio(_ultimoMsjRcv.idRobot, colocado);
	_cola.enviar(_msjAEnviar);
	mostrarEstadoPlataforma();
}

void PlataformaReal::sacarDispositivo() {

	_salida->mostrar("Se recibio mensaje de SACAR_DISPOSITIVO del robot-", _ultimoMsjRcv.numRobot);

	bool encontrado = false;
	int i = 0;

	while (!encontrado && i < _capacidad) {
		if (_lugares[i].lugar == EstadoLugarPlataforma::ENCENDIDO) {
			encontrado = true;

			prepararEnvio(_ultimoMsjRcv.idRobot, 0);
			_msjAEnviar.numDispositivo = _lugares[i].numDispositivo;
			_lugares[i].lugar = EstadoLugarPlataforma::VACIO;

			_cola.enviar(_msjAEnviar);

			--_ocupados;
			--_activados;
			++_sacados;

			_salida->agregarAlMsj("Saco un dispositivo el robot-");
			_salida->agregarAlMsj(_ultimoMsjRcv.numRobot);
			_salida->agregarAlMsj(", n°");
			_salida->agregarAlMsj(_msjAEnviar.numDispositivo);
			_salida->mostrarMsj();
		}
		else {
			i++;
		}
	}

	mostrarEstadoPlataforma();

}

void PlataformaReal::plataformaLlena() {
	_salida->mostrar("Se recibio mensaje de PLATAFORMA_LLENA del robot-", _ultimoMsjRcv.numRobot);

	bool resultado = (_capacidad == _ocupados);

	prepararEnvio(_ultimoMsjRcv.idRobot, resultado);

	_cola.enviar(_msjAEnviar);
}

void PlataformaReal::hayDispositivosActivos() {
	_salida->mostrar("Se recibio mensaje de HAY_DISP_ACTIVOS del robot-", _ultimoMsjRcv.numRobot);

	bool hayActivos = false;

	int i = 0;

	while (!hayActivos && i < _capacidad) {
		if (_lugares[i].lugar == EstadoLugarPlataforma::ENCENDIDO)
			hayActivos = true;
		else
			i++;
	}

	if (hayActivos) {
		_salida->mostrar("Se envia mensaje de HAY dispositivos activos al robot-", _ultimoMsjRcv.numRobot);
	}
	else {
		_salida->mostrar("Se envia mensaje de NO HAY dispositivos activos al robot-", _ultimoMsjRcv.numRobot);
	}

	prepararEnvio(_ultimoMsjRcv.idRobot, hayActivos);
	_cola.enviar(_msjAEnviar);
}

void PlataformaReal::detectarFrecuencia() {
	_salida->mostrar("Se recibio Mensaje de DETECTAR_FRECUENCIA del robot-", _ultimoMsjRcv.numRobot);
	hayDispositivosActivos();
}

void PlataformaReal::reservarLugar() {
	_salida->mostrar("Se recibio mensaje de RESERVAR_LUGAR del robot-", _ultimoMsjRcv.numRobot);

	bool encontrado = false;

	int pos = 0;

	while (!encontrado && pos < _capacidad) {

		if (_lugares[pos].lugar == EstadoLugarPlataforma::VACIO) {
			encontrado = true;
			_lugares[pos].lugar = EstadoLugarPlataforma::RESERVADO;
			//_lugares[pos].numDispositivo = _ultimoMsjRcv.numDispositivo;

			++_reservados;

			_salida->agregarAlMsj("Se reservo el lugar ");
			_salida->agregarAlMsj(pos);
			_salida->mostrarMsj();

		}
		else {
			pos++;
		}
	}

	prepararEnvio(_ultimoMsjRcv.idRobot, encontrado);
	_cola.enviar(_msjAEnviar);

	mostrarEstadoPlataforma();
}

void PlataformaReal::estadoRobot() {

	int pos = _ultimoMsjRcv.numRobot;

	if (pos >= _cantRobots) {
		_salida->error("Error al acceder a estado de robot que no existe");
		return;
	}

	if (_ultimoMsjRcv.metodo == MtdPlataforma::ESTADO_ROBOT_ARMAR) {
		_salida->mostrar("Se recibio Mensaje de ESTADO_ROBOT_ARMAR del robot-", _ultimoMsjRcv.numRobot);

		prepararEnvio(_ultimoMsjRcv.idRobot, (int)_estadosArmar[pos]);
	}
	else {
		_salida->mostrar("Se recibio Mensaje de ESTADO_ROBOT_FREC del robot-", _ultimoMsjRcv.numRobot);

		prepararEnvio(_ultimoMsjRcv.idRobot, (int)_estadosFrec[pos]);
	}

	_cola.enviar(_msjAEnviar);
}

void PlataformaReal::modificarRobot() {

	int pos = _ultimoMsjRcv.numRobot;

	if (pos >= _cantRobots) {
		_salida->error("Error al acceder a estado de robot que no existe");
		return;
	}

	if (_ultimoMsjRcv.metodo == MtdPlataforma::ROBOT_ARMAR) {
		_salida->mostrar("Se recibio mensaje de MODIFICAR ROBOT_ARMAR del robot-", _ultimoMsjRcv.numRobot);
		_estadosArmar[pos] = (EstRobotArmar::EstadoRobotArmar) _ultimoMsjRcv.resultado.entero;

	}
	else {
		_salida->mostrar("Se recibio mensaje de MODIFICAR ROBOT_FREC del robot-", _ultimoMsjRcv.numRobot);
		_estadosFrec[pos] = (EstRobotFrec::EstadoRobotFrec) _ultimoMsjRcv.resultado.entero;
	}

	// No se tiene que porque enviar mensaje de confirmación
	//_cola.enviar(_msjAEnviar);
}



void PlataformaReal::prepararEnvio(int idRobot, int resultado) {
	_msjAEnviar._tipo = idRobot;
	_msjAEnviar.resultado.entero = resultado;
}

void PlataformaReal::activarDispositivosAlAzar() {
	if (random() <= (RAND_MAX / 2)) {
		for (int i = 0; i < _capacidad ; i++) {
			if (_lugares[i].lugar == EstadoLugarPlataforma::OCUPADO) {
				if (random() <= (RAND_MAX / 2)) {
					_lugares[i].lugar = EstadoLugarPlataforma::ENCENDIDO;

					_salida->agregarAlMsj("Se activo dispositivo n°");
					_salida->agregarAlMsj(_lugares[i].numDispositivo);
					_salida->mostrarMsj();
					++_activados;
				}
			}
		}
	}
}

void PlataformaReal::prepararEnvio(int idRobot, bool resultado) {
	_msjAEnviar._tipo = idRobot;
	_msjAEnviar.resultado.booleano = resultado;
}

void PlataformaReal::mostrarEstadoPlataforma() {
		_salida->agregarAlMsj("Estado- LIBRES: ");
		_salida->agregarAlMsj(_capacidad - _ocupados);
		_salida->agregarAlMsj(", OCUPADOS: ");
		_salida->agregarAlMsj(_ocupados);
		_salida->agregarAlMsj(", RESERVADOS: ");
		_salida->agregarAlMsj(_reservados);
		_salida->agregarAlMsj(", ACTIVOS: ");
		_salida->agregarAlMsj(_activados);
		_salida->agregarAlMsj(", COLOCADOS: ");
		_salida->agregarAlMsj(_colocados);
		_salida->agregarAlMsj(", SACADOS: ");
		_salida->agregarAlMsj(_sacados);
		_salida->mostrarMsj();
}

void PlataformaReal::robotsFinalizados() {
	_salida->mostrar("Se recibio mensaje de ROBOTS_FINALIZADOS del robot-", _ultimoMsjRcv.numRobot);

	bool finalizados = true;

	int i = 0;

	while (finalizados && i < _cantRobots ) {
		finalizados = _estadosArmar[i] == EstRobotArmar::FINALIZADO;
		++i;
	}

	prepararEnvio(_ultimoMsjRcv.idRobot, finalizados);
	_cola.enviar(_msjAEnviar);
}

void liberarRobotFrecuencia(int numRobot) {

}
