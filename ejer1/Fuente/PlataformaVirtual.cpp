/*
 * PlataformaVirtual.cpp
 *
 *  Created on: 23/04/2014
 *      Author: migue
 */

#include "PlataformaVirtual.h"

#include "Definiciones.h"

#include <sstream>
#include <stdlib.h>

PlataformaVirtual::PlataformaVirtual(int numRobot) {
	_numRobot = numRobot;
	_idRobot = idRobotFrec(_numRobot);
	_idComp = idRobotFrecComp(_numRobot);

	_modo = MdRobot::DET_FRECUENCIA;

	iniciarComponente();
}

PlataformaVirtual::PlataformaVirtual(int numRobot, int pilas, int disp) {
	_numRobot = numRobot;
	_idRobot = idRobotArmar(_numRobot);
	_idComp = idRobotArmarComp(_numRobot);

	_pilas = pilas;
	_disp = disp;

	_modo = MdRobot::ARMADOR;

	iniciarComponente();
}

void PlataformaVirtual::iniciarComponente() {
	std::stringstream ss;

	ss << _numRobot;
	const char *ptra= "A", *ptrf = "F";
	const char* arg;

	if (_modo == MdRobot::ARMADOR)
		arg = ptra;
	else
		arg = ptrf;


	int pid = fork();

	if (pid == 0) {
		execl("./comp", "Componente",ss.str().c_str(), arg,  NULL);
		SalidaPorPantalla::instancia().error("No inicio proceso componente");
		exit(EXIT_FAILURE);
	}
}

PlataformaVirtual::~PlataformaVirtual() {
	if (_modo == MdRobot::ARMADOR) {
		prepararMsj(MtdPlataforma::ARMADOR_FINALIZO);
		_cola.enviar(_msj);
	}
}

bool PlataformaVirtual::detectarFrecuencia() {
	prepararMsj(MtdPlataforma::DETERCAR_FREC);
	enviarYEsperarResp();

	return _msj.resultado.booleano;
}

bool PlataformaVirtual::sacarDispositivo(int& numDispositivo) {
	prepararMsj(MtdPlataforma::SACAR_DISP);
	enviarYEsperarResp();

	numDispositivo = _msj.numDispositivo;

	return _msj.resultado.booleano;
}

bool PlataformaVirtual::seguirTrabajando() {
	prepararMsj(MtdPlataforma::SEGUIR_TRABAJANDO_FREC);
	enviarYEsperarResp();

	return _msj.resultado.booleano;
}

bool PlataformaVirtual::plataformaLlena(){
	prepararMsj(MtdPlataforma::PLATAFORMA_LLENA);
	enviarYEsperarResp();

	return _msj.resultado.booleano;
}

void PlataformaVirtual::esperar() {
	prepararMsj(MtdPlataforma::ESPERAR);
	enviarYEsperarResp();
}

bool PlataformaVirtual::colocarDispositivo(int numDispositvo) {
	prepararMsj(MtdPlataforma::COLOCAR_DISP);
	_msj.numDispositivo = numDispositvo;
	enviarYEsperarResp();

	return _msj.resultado.booleano;
}

void PlataformaVirtual::prepararMsj(MtdPlataforma::MetodoPlataforma metodo) {
	_msj._tipo = _idComp;
	_msj.idRobot = _idRobot;
	_msj.numRobot = _numRobot;
	_msj.numDispositivo = 0;
	_msj.metodo = metodo;
}


void PlataformaVirtual::enviarYEsperarResp() {
	_cola.enviar(_msj);
	_cola.recibir(_msj, _idRobot);
}
