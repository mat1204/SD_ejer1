/*
 * SalaVirtual.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#include "SalaVirtual.h"

bool SalaVirtual::_compLanzado = false;

SalaVirtual::SalaVirtual(int numero,TpAgente::TipoAgente tipo, LgSala::LugarSala lugar) {
	_numero = numero;
	_tipo = tipo;

	if (_tipo == TpAgente::CABLE_CARRIL) {
		_id = IdCableCarril(numero);
		_idComp = IdCablaCarrilComp(numero);
	}
	else if (_tipo == TpAgente::PERSONA) {
		_id = IdPersona(numero);
		_idComp = IdPersonaComp(numero);
	}
	else {
		SalidaPorPantalla::instancia().error("No se reconoce tipo de agente");
		exit(EXIT_FAILURE);
	}

	_lugar = lugar;

	iniciarComponente();
}


SalaVirtual::~SalaVirtual() {
}


void SalaVirtual::iniciarComponente() {

	if (_compLanzado)
		return;

	std::stringstream ss;

	int pid;

	const char* arg_ejec = NULL;

	if (_tipo == TpAgente::CABLE_CARRIL) {
		arg_ejec = "./compCC";
	}
	else if (_tipo == TpAgente::PERSONA) {
		arg_ejec = "./compPer";
	}
	else {
		SalidaPorPantalla::instancia().error("No se reconoce tipo de agente para iniciar componente");
		exit(EXIT_FAILURE);
	}

	ss << _numero;

	pid = fork();

	if (pid == 0) {
		execl(arg_ejec, "Componente", ss.str().c_str(), NULL);
		SalidaPorPantalla::instancia().error("No se pudo iniciar proceso componente");
		exit(EXIT_FAILURE);
	}
	else {
		SalidaPorPantalla::instancia().mostrar("proceso componente lanzado");
	}

	SalidaPorPantalla::instancia().mostrar("Componente iniciado");
	_compLanzado = true;
}

bool SalaVirtual::salaVacia() {
	_msj.metodo = MtdSala::SALA_VACIA;
	enviarYEspRes();

	return _msj.resultado.booleano;
}

bool SalaVirtual::sacarPersona(int& numPersona) {
	_msj.metodo = MtdSala::SACAR_PERSONA_COLA;

	enviarYEspRes();

	numPersona = _msj.numPersona;

	return _msj.resultado.booleano;
}

void SalaVirtual::subirPersona(const int numPersona) {
	_msj.metodo = MtdSala::SUBIR_PERSONA;
	_msj.numPersona = numPersona;

	enviarYEspRes();
}

void SalaVirtual::bajarPersona(const int numPersona) {
	_msj.metodo = MtdSala::BAJAR_PERSONA;
	_msj.numPersona = numPersona;

	enviarYEspRes();
}

bool SalaVirtual::hayLugar() {

	_msj.metodo = MtdSala::HAY_LUGAR;

	enviarYEspRes();

	return _msj.resultado.booleano;
}

void SalaVirtual::esperarPorLugar() {
	_msj.metodo = MtdSala::ESPERAR_POR_LUGAR;

	enviarYEspRes();
}

bool SalaVirtual::hacerCola(const int numPersona) {
	_msj.numPersona = numPersona;
	_msj.metodo = MtdSala::HACER_COLA;

	enviarYEspRes();

	_numCC_aSubir = _msj.numCC;

	return _msj.resultado.booleano;
}

void SalaVirtual::subirCableCarril() {
	_msj.metodo = MtdSala::SUBIR_CC;
	_msj.numCC = _numCC_aSubir;

	enviarYEspRes();
}

void SalaVirtual::enviarYEspRes() {
	_msj._mtype = _idComp;
	_msj._idEmisor = _id;

	_msj.numPersona = _numero;
	_msj.numCC = _numero;

	_msj.lugar = _lugar;

	_cola.enviar(_msj);
	_cola.recibir(_msj, _id);
}
