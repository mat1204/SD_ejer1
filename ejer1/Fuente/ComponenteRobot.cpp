/*
 * ComponenteRobot.cpp
 *
 *  Created on: 20/04/2014
 *      Author: migue
 */

#include "ComponenteRobot.h"
#include <stdlib.h>

ComponenteRobot::ComponenteRobot(int numeroRobot, MdRobot::ModoRobot tipo) : _plataforma(numeroRobot) {
	_numeroRobot = numeroRobot;
	_tipo = tipo;

	_seguirTrabajando = true;

	if (tipo == MdRobot::ARMADOR) {
		_idComponente = idRobotArmarComp(numeroRobot);
	}
	else if (tipo == MdRobot::DET_FRECUENCIA) {
		_idComponente = idRobotFrecComp(numeroRobot);
	}
	else {
		SalidaPorPantalla::instancia().error("No se reconoce tipo de robot en constructor ComponenteRobot");
		exit(EXIT_FAILURE);
	}
}

ComponenteRobot::~ComponenteRobot() {

}


int ComponenteRobot::iniciarParaFrecuencia() {
	while(_seguirTrabajando) {
		esperarMsj();

		MtdPlataforma::MetodoPlataforma metodo = _ultimoMsj.metodo;

		switch (metodo) {
			case MtdPlataforma::PLATAFORMA_LLENA: procPlataformaLlena(); break;
			case MtdPlataforma::ESPERAR: procEsperar(); break;
			case MtdPlataforma::COLOCAR_DISP: procColocarDispositivo(); break;
			default: break;
		}

		enviarRespuesta();
	}

	return 0;

	return 0;
}

int ComponenteRobot::iniciarParaArmado() {

	while(_seguirTrabajando) {
		esperarMsj();

		MtdPlataforma::MetodoPlataforma metodo = _ultimoMsj.metodo;

		switch (metodo) {
			case MtdPlataforma::DETERCAR_FREC: procDetectarFrecuencia(); break;
			case MtdPlataforma::SACAR_DISP: procSacarDispositivo(); break;
			case MtdPlataforma::SEGUIR_TRABAJANDO_FREC: procSeguirTrabajando(); break;
			default: break;
		}

		enviarRespuesta();
	}

	return 0;
}

void ComponenteRobot::esperarMsj() {
	_cola.recibir(_ultimoMsj, _idComponente);
}

void ComponenteRobot::enviarRespuesta() {
	_respuesta._tipo = _ultimoMsj.idRobot;
	_cola.enviar(_respuesta);
}


void ComponenteRobot::procDetectarFrecuencia() {
	_respuesta.resultado.booleano = _plataforma.detectarFrecuencia();
}
void ComponenteRobot::procSeguirTrabajando() {
	_respuesta.resultado.booleano = _plataforma.seguirTrabajando();
	_seguirTrabajando = _respuesta.resultado.booleano;
}
void ComponenteRobot::procSacarDispositivo() {
	int numDisp;
	_respuesta.resultado.booleano = _plataforma.sacarDispositivo(numDisp);
	_respuesta.numDispositivo = numDisp;
}


void ComponenteRobot::procPlataformaLlena(){
	_respuesta.resultado.booleano = _plataforma.plataformaLlena();
}
void ComponenteRobot::procEsperar() {
	_plataforma.esperar();
}
void ComponenteRobot::procColocarDispositivo() {
	_respuesta.resultado.booleano = _plataforma.colocarDispositivo(_ultimoMsj.numDispositivo);
	_respuesta.numDispositivo = _ultimoMsj.numDispositivo;
}
