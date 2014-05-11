/*
 * EstacionVirtual.cpp
 *
 *  Created on: 24/04/2014
 *      Author: migue
 */

#include "EstacionVirtual.h"
#include <sstream>
#include <string.h>

EstacionVirtual::EstacionVirtual(int numEstacion) : _colaComp() {

	_numEstacion = numEstacion;
	_idEstVirtual = IdEstVirtual(_numEstacion);
	_idComp = IdEstComp(_numEstacion);

	iniciarComponente();
}

EstacionVirtual::~EstacionVirtual() {

}


void EstacionVirtual::obtenerPiezaEstAnt(stPieza& pieza) {
	stMensaje msj;

	msj._tipo = _idComp;
	msj._idEmisor = _idEstVirtual;

	msj.metodo = MtdEstacion::OBTENER_PIEZA_EST_ANT;

	_colaComp.enviar(msj);
	_colaComp.recibir(msj, _idEstVirtual);

	memcpy((void*) &pieza, (void*) &msj.pieza, sizeof(stPieza));
}

void EstacionVirtual::esperarEstSig(const stPieza& piezaAEnviar) {
	stMensaje msj;

	msj._tipo = _idComp;
	msj._idEmisor = _idEstVirtual;

	msj.metodo = MtdEstacion::ESPERAR_EST_SIG;

	memcpy((void*) &msj.pieza, (void*) &piezaAEnviar, sizeof(stPieza));

	_colaComp.enviar(msj);
	_colaComp.recibir(msj, _idEstVirtual);
}


int EstacionVirtual::solicitarMateriales() {
	return 100;
}

void EstacionVirtual::iniciarComponente() {
	int pid;

	std::stringstream ss;
	ss << _numEstacion;
	const char* arg = ss.str().c_str();
	pid = fork();

	if (pid == 0) {
		execl("./comp","Componente", arg, NULL);
		SalidaPorPantalla::instancia().error("No se pudo iniciar proceso Componente");
	}
}
