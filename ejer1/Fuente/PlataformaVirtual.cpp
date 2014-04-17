/*
 * PlataformaVirtual.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#include "PlataformaVirtual.h"
#include "Definiciones.h"

PlataformaVirtual::PlataformaVirtual(int cantRobots, int idRobot, int pilas, int dispositivos) :
	_semsArmar(cantRobots, ID_SEMS_ARMAR),
	_semsFrec(cantRobots,
			ID_SEMS_FREC) {

	_numRobot = numeroDeRobot(idRobot);
	_idRobot = idRobot;
	_cantRobots = cantRobots;

	_armarFinalizado = false;
	_seguirTrabajando = true;

	if ( dispositivos >= (pilas/2) )
		_cantDispositvos = pilas /2;
	else
		_cantDispositvos = dispositivos;

	_salida = &SalidaPorPantalla::instancia();
}

PlataformaVirtual::~PlataformaVirtual() {

}


bool PlataformaVirtual::plataformaLlena() {
	MensajeCola msj;

	// Se espera hasta que se desocupe el robot de frecuencia
	if (estadoRobotFrec() == EstRobotFrec::OCUPADO) {
		estadoRobotArmar(EstRobotArmar::ESPERANDO);
		waitArmar();
		estadoRobotArmar(EstRobotArmar::OCUPADO);
	}

	armarMsj(msj, (int) MtdPlataforma::PLATAFORMA_LLENA);
	enviarYEsperar(msj);

	bool platLlena = msj.resultado.booleano;

	if (platLlena == false) {

		//esperarPorRobotFrec();

		armarMsj(msj, (int) MtdPlataforma::RESERVAR_LUGAR);
		enviarYEsperar(msj);

		bool reservado = msj.resultado.booleano;

		// retorna un booleano indicando si se pudo reservar el lugar
		if (reservado) {
			estadoRobotArmar(EstRobotArmar::ARMANDO);

			// retorna plataforma no llena y lugar reservado
			return false;
		}
	}

	// retorna plataforma llena por lo que no se puo reservar
	return true;
}

void PlataformaVirtual::esperar() {
	MensajeCola msj;

	SalidaPorPantalla::instancia().mostrar("Se \"Espera\" hasta que haya lugar en la plataforma");

	estadoRobotArmar(EstRobotArmar::ESPERANDO);

	signalFrec();
	waitFrec();

	estadoRobotArmar(EstRobotArmar::OCUPADO);

}

bool PlataformaVirtual::colocarDispositivo(int numDispositvo) {
	MensajeCola msj;

	//esperarPorRobotFrec();

	if (estadoRobotFrec() == EstRobotFrec::OCUPADO) {
		estadoRobotArmar(EstRobotArmar::ESPERANDO);
		waitArmar();
		estadoRobotArmar(EstRobotArmar::ARMANDO);
	}


	armarMsj(msj, MtdPlataforma::COLOCAR_DISP);
	msj.numDispositivo = numDispositvo;
	enviarYEsperar(msj);

	bool colocado = msj.resultado.booleano;

	estadoRobotArmar(EstRobotArmar::ESPERANDO);

	signalFrec();
	waitArmar();

	if (colocado) {
		--_cantDispositvos;
		if (_cantDispositvos == 0) {
			estadoRobotArmar(EstRobotArmar::FINALIZADO);
			signalFrec();
		}
	}

	return colocado;
}

bool PlataformaVirtual::detectarFrecuencia() {
	MensajeCola msj;

	if (!_armarFinalizado && estadoRobotArmar() == EstRobotArmar::ARMANDO ) {
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
		//_semsFrec.wait(_numRobot);
		waitFrec();
		estadoRobotFrec(EstRobotFrec::OCUPADO);
	}

	armarMsj(msj, MtdPlataforma::HAY_DISP_ACTIVOS);
	enviarYEsperar(msj);

	bool frecDetectada = msj.resultado.booleano;

	if (frecDetectada == false) {

		estadoRobotFrec(EstRobotFrec::ESPERANDO);

		if (_armarFinalizado == false) {
			signalArmar();
			waitFrec();
		}
		else if (robotsArmarFinalizados()) {
			_seguirTrabajando = false;
			estadoRobotFrec(EstRobotFrec::FINALIZADO);
		}
	}

	estadoRobotFrec(EstRobotFrec::OCUPADO);

	return frecDetectada;
}

bool PlataformaVirtual::sacarDispositivo(int& numDispositivo) {
	MensajeCola msj;

	//esperarPorRobotArmar(EstRobotArmar::ARMANDO);

	if (!_armarFinalizado && estadoRobotArmar() == EstRobotArmar::ARMANDO) {
		estadoRobotFrec(EstRobotFrec::ESPERANDO);
		waitFrec();
		estadoRobotFrec(EstRobotFrec::OCUPADO);
	}

//	armarMsj(msj, (int) MtdPlataforma::SACAR_DISP);
//	enviarYEsperar(msj);
//
	bool sacado = false;

	// Si hay dispositovos activos entonces ...

	armarMsj(msj, MtdPlataforma::SACAR_DISP);
	enviarYEsperar(msj);

	sacado = msj.resultado.booleano;
	numDispositivo = msj.numDispositivo;

	liberarRobotsArmadores();


	if (sacado) {
		SalidaPorPantalla::instancia().agregarAlMsj("Se saco Dispositivo N°");
		SalidaPorPantalla::instancia().agregarAlMsj(numDispositivo);
		SalidaPorPantalla::instancia().mostrarMsj();

		estadoRobotFrec(EstRobotFrec::ESPERANDO);

		if (_armarFinalizado == false) {
			signalArmar();
			waitFrec();
		}

		estadoRobotFrec(EstRobotFrec::OCUPADO);

	}
	else {
		SalidaPorPantalla::instancia().mostrar("No se saco ningun dispositivo.");
	}

	return sacado;
}

void PlataformaVirtual::armarMsj(MensajeCola& msj,int metodo) {
	msj._tipo = ID_PLATAFORMA;

	msj.metodo = (MtdPlataforma::MetodoPlataforma) metodo;
	msj.numRobot = _numRobot;
	msj.idRobot = _idRobot;
}

void PlataformaVirtual::liberarRobotsArmadores() {

	MensajeCola msj;

	armarMsj(msj,(int) MtdPlataforma::PLATAFORMA_LLENA);
	enviarYEsperar(msj);

	// Si plataforma llena entonces ...
	if (msj.resultado.booleano) {

		for (int i = 0; i  < _cantRobots ; i++) {
			armarMsj(msj, MtdPlataforma::ESTADO_ROBOT_ARMAR);
			enviarYEsperar(msj);

			if (msj.resultado.entero == EstRobotArmar::ESPERANDO && (i != _idRobot) )
				//_semsArmar.signal(i);
				signalArmar();
		}
	}
}

void PlataformaVirtual::enviarYEsperar(MensajeCola& msj) {
	_colaMsj.enviar(msj);
	SalidaPorPantalla::instancia().mostrar("Se envio mensaje a la Plataforma por robot_", _numRobot);
	_colaMsj.recibir(msj, _idRobot);
	SalidaPorPantalla::instancia().mostrar("Se recibio mensaje de la Plataforma");
}

void PlataformaVirtual::esperarPorRobotFrec() {
	MensajeCola msj;
	armarMsj(msj, MtdPlataforma::ESTADO_ROBOT_FREC);

	enviarYEsperar(msj);

	if (msj.resultado.entero == EstRobotFrec::OCUPADO) {
		waitArmar();
	}
}

void PlataformaVirtual::esperarPorRobotArmar(EstRobotArmar::EstadoRobotArmar estado) {
	MensajeCola msj;
	armarMsj(msj, MtdPlataforma::ESTADO_ROBOT_ARMAR);

	enviarYEsperar(msj);

	if (msj.resultado.entero == estado) {
		this->waitFrec();
	}
}


int PlataformaVirtual::estadoRobotFrec() {
	MensajeCola msj;

	armarMsj(msj, MtdPlataforma::ESTADO_ROBOT_FREC);
	enviarYEsperar(msj);

	return msj.resultado.entero;
}

int PlataformaVirtual::estadoRobotArmar() {
	MensajeCola msj;

	armarMsj(msj, MtdPlataforma::ESTADO_ROBOT_ARMAR);
	enviarYEsperar(msj);

	_armarFinalizado = (msj.resultado.entero == EstRobotArmar::FINALIZADO);

	return msj.resultado.entero;
}


void PlataformaVirtual::estadoRobotFrec(EstRobotFrec::EstadoRobotFrec nvEstado){
	MensajeCola msj;

	armarMsj(msj, MtdPlataforma::ROBOT_FREC);
	msj.resultado.entero = nvEstado;

	_colaMsj.enviar(msj);
}

void PlataformaVirtual::estadoRobotArmar(EstRobotArmar::EstadoRobotArmar nvEstado) {
	MensajeCola msj;

	armarMsj(msj, MtdPlataforma::ROBOT_ARMAR);
	msj.resultado.entero = nvEstado;

	if (nvEstado == EstRobotArmar::FINALIZADO)
		_salida->mostrar("Armado FINALIZADO");

	_colaMsj.enviar(msj);
}


void PlataformaVirtual::signalArmar() {
	_salida->mostrar("por hacer SIGNAL de semaforo");
	_semsArmar.signal(_numRobot);
}

void PlataformaVirtual::waitArmar(){
	_salida->mostrar("por hacer WAIT de semaforo");
	_semsArmar.wait(_numRobot);
}

void PlataformaVirtual::signalFrec() {
	_salida->mostrar("por hacer SIGNAL de semaforo");
	_semsFrec.signal(_numRobot);
}

void PlataformaVirtual::waitFrec() {
	_salida->mostrar("por hacer WAIT de samforo");
	_semsFrec.wait(_numRobot);
}

bool PlataformaVirtual::seguirTrabajando() {
	return _seguirTrabajando;
}

bool PlataformaVirtual::robotsArmarFinalizados() {
	MensajeCola msj;
	armarMsj(msj, MtdPlataforma::ROBOTS_FINALIZADOS);
	enviarYEsperar(msj);

	return msj.resultado.booleano;
}
