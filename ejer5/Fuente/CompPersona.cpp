/*
 * CompPersona.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#include "CompPersona.h"

extern void mostrarDatos(stMensaje& msj);

CompPersona::CompPersona(int numPersona) :
 _salaPie(LgSala::PIE), _salaCima(LgSala::CIMA)
{
	_numPersona = numPersona;
	_idComp = IdPersonaComp(numPersona);
	_idPersona = IdPersona(numPersona);

	_seguirTrabajando = true;
	_enviarResp = false;

	//SalidaPorPantalla::instancia().mostrar("Componente inciado");
	SalidaPorPantalla::instancia().imprimirMensajes(false);

	_numCCaSubir = -1;
}

CompPersona::~CompPersona() {

}

int CompPersona::correr() {
	MtdSala::MetodoSala metodo;

	while (_seguirTrabajando) {
		_enviarResp = false;
		esperarMsj();

		metodo = _ultimoMsj.metodo;

		switch(metodo) {
		case MtdSala::HAY_LUGAR: procHayLugar();
			break;

		case MtdSala::ESPERAR_POR_LUGAR: procEsperarPorLugar();
			break;

		case MtdSala::HACER_COLA: procHacerCola();
			break;

		case MtdSala::SUBIR_CC: procSubirCableCarril();
			break;

		case MtdSala::CERRAR: _seguirTrabajando = false;
			break;

		default: SalidaPorPantalla::instancia().error("Metodo No reconocido");
			mostrarDatos(_ultimoMsj);
			break;
		}

		enviarResp();
	}


	return 0;
}


void CompPersona::esperarMsj() {
	_cola.recibir(_ultimoMsj, _idComp);

	if (_ultimoMsj.lugar == LgSala::CIMA) {
		_salaActual = &_salaCima;
	}
	else if (_ultimoMsj.lugar == LgSala::PIE) {
		_salaActual = &_salaPie;
	}
}

void CompPersona::enviarResp() {

	if (_enviarResp) {
		_msjResp._mtype = _ultimoMsj._idEmisor;
		_msjResp._idEmisor = _idComp;

		_cola.enviar(_msjResp);
	}
	else if( _seguirTrabajando == true ) {
		SalidaPorPantalla::instancia().error("No se puede enviar respuesta");
	}
}


void CompPersona::procHayLugar() {
	_msjResp.resultado.booleano = _salaActual->hayLugar();
	_enviarResp = true;
}

void CompPersona::procEsperarPorLugar() {
	_salaActual->esperarPorLugar();
	_enviarResp = true;
}

void CompPersona::procHacerCola() {
	stMensajeBloqueo msjCC;
	_msjResp.resultado.booleano = _salaActual->hacerCola(_ultimoMsj.numPersona);

	if (_msjResp.resultado.booleano) {
		// espero msj de cable carril
		SalidaPorPantalla::instancia().mostrar("esperando msj de CC...");


		_colaBlq.recibir(msjCC, _idComp);
		_msjResp.numCC = msjCC.numCC;

		_enviarResp = true;
	}
	else {
		SalidaPorPantalla::instancia().error("no hizo cola en la sala de espera");
	}
}

void CompPersona::procSubirCableCarril() {

	enviarACC(_ultimoMsj.numCC);

	stMensajeBloqueo msjCC;

	_colaBlq.recibir(msjCC, _idComp);

	_enviarResp = true;
}

void CompPersona::enviarACC(int numCC) {
	stMensajeBloqueo msjCC;
	msjCC._mtype = IdCablaCarrilComp(numCC);
	msjCC.numCC = -1;
	msjCC.numPersona = _numPersona;

	_colaBlq.enviar(msjCC);
}
