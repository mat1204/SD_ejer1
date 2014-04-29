/*
 * ComponenteRobot.cpp
 *
 *  Created on: 20/04/2014
 *      Author: migue
 */

#include "ComponenteRobot.h"
#include <stdlib.h>

SalidaPorPantalla* salida;

ComponenteRobot::ComponenteRobot(int numeroRobot, MdRobot::ModoRobot tipo) : _plataforma(numeroRobot) {
	_numeroRobot = numeroRobot;
	_tipo = tipo;
	std::string capacidad;

	salida = &SalidaPorPantalla::instancia();

	_seguirTrabajando = true;

	if (tipo == MdRobot::ARMADOR) {
		salida->etiqueta("CompArmado", _numeroRobot);
		_idComponente = idRobotArmarComp(numeroRobot);
	}
	else if (tipo == MdRobot::DET_FRECUENCIA) {
		salida->etiqueta("CompFrec", _numeroRobot);
		_idComponente = idRobotFrecComp(numeroRobot);
	}
	else {
		SalidaPorPantalla::instancia().error("No se reconoce tipo de robot en constructor ComponenteRobot");
		exit(EXIT_FAILURE);
	}

	salida->mostrar("Componente iniciado");
}

ComponenteRobot::~ComponenteRobot() {

}

int ComponenteRobot::correr() {
	if (_tipo == MdRobot::ARMADOR)
		return iniciarParaArmado();
	else if (_tipo == MdRobot::DET_FRECUENCIA)
		return iniciarParaFrecuencia();
	else {
		SalidaPorPantalla::instancia().error("No se reconoce modo de Robot");
		return -1;
	}
}

int ComponenteRobot::iniciarParaArmado() {
	while(_seguirTrabajando) {
		esperarMsj();

		salida->mostrar("Se recibio mensaje de robot-", _ultimoMsj.numRobot);

		MtdPlataforma::MetodoPlataforma metodo = _ultimoMsj.metodo;

		switch (metodo) {
			case MtdPlataforma::PLATAFORMA_LLENA: procPlataformaLlena(); break;
			case MtdPlataforma::ESPERAR: procEsperar(); break;
			case MtdPlataforma::COLOCAR_DISP: procColocarDispositivo(); break;
			default:salida->error("Metodo de Plataforma no reconocido."); break;
		}

		enviarRespuesta();
	}

	return 0;
}

int ComponenteRobot::iniciarParaFrecuencia() {

	while(_seguirTrabajando) {
		esperarMsj();

		MtdPlataforma::MetodoPlataforma metodo = _ultimoMsj.metodo;

		switch (metodo) {
			case MtdPlataforma::DETERCAR_FREC: procDetectarFrecuencia(); break;
			case MtdPlataforma::SACAR_DISP: procSacarDispositivo(); break;
			case MtdPlataforma::SEGUIR_TRABAJANDO_FREC: procSeguirTrabajando(); break;
			default: salida->error("Metodo de Plataforma no reconocido."); break;
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
	SalidaPorPantalla::instancia().mostrar("llamando proceso DetectarFrecuencia()");

	_respuesta.resultado.booleano = _plataforma.detectarFrecuencia();

	if (_respuesta.resultado.booleano) {
		SalidaPorPantalla::instancia().mostrar("Frecuencia detectada");
	}
	else {
		SalidaPorPantalla::instancia().mostrar("Frecuencia detectada");
	}

}
void ComponenteRobot::procSeguirTrabajando() {
	_respuesta.resultado.booleano = _plataforma.seguirTrabajando();
	_seguirTrabajando = _respuesta.resultado.booleano;

	if (_seguirTrabajando == false) {
		SalidaPorPantalla::instancia().mostrar("No seguir trabajando");
	}
}
void ComponenteRobot::procSacarDispositivo() {
	int numDisp;
	_respuesta.resultado.booleano = _plataforma.sacarDispositivo(numDisp);
	_respuesta.numDispositivo = numDisp;

	if (_respuesta.resultado.booleano) {
		SalidaPorPantalla::instancia().mostrar("Se saco dispositivo n°", numDisp);
	}
}

void ComponenteRobot::procPlataformaLlena(){

	SalidaPorPantalla::instancia().mostrar("llamando proceso PlataformaLlena()");

	_respuesta.resultado.booleano = _plataforma.plataformaLlena();


	if (_respuesta.resultado.booleano) {
		SalidaPorPantalla::instancia().mostrar("Plataforma llena");
	}
	else
		SalidaPorPantalla::instancia().mostrar("Plataforma no llena y con lugar reservado");
}

void ComponenteRobot::procEsperar() {
	_plataforma.esperar();
}

void ComponenteRobot::procColocarDispositivo() {
	SalidaPorPantalla::instancia().mostrar("llamando proceso ColocarDispositivo()");

	_respuesta.resultado.booleano = _plataforma.colocarDispositivo(_ultimoMsj.numDispositivo);
	_respuesta.numDispositivo = _ultimoMsj.numDispositivo;
}
