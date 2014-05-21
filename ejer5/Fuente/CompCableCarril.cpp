/*
 * CompCableCarril.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#include "CompCableCarril.h"

void mostrarDatos(stMensaje& msj) {
	SalidaPorPantalla::instancia().dormirTrasImprimir(false);

	SalidaPorPantalla::instancia().mostrar("Metodo numero: ", msj.metodo);
	SalidaPorPantalla::instancia().mostrar("Emisor: ", msj._idEmisor);
	SalidaPorPantalla::instancia().mostrar("Destino: ", msj._mtype);
	SalidaPorPantalla::instancia().mostrar("Lugar: ", msj.lugar);
	SalidaPorPantalla::instancia().mostrar("Numero Persona: ", msj.numPersona);
	SalidaPorPantalla::instancia().mostrar("Numero CC: ", msj.numCC);

	SalidaPorPantalla::instancia().dormirTrasImprimir(true);
}

CompCableCarril::CompCableCarril(int numCableCarril) :
	_salaPie(LgSala::PIE), _salaCima(LgSala::CIMA)
{

	_idComp = IdCablaCarrilComp(numCableCarril);
	_idCC = IdCableCarril(numCableCarril);

	_seguirTrabajando = true;
	_enviarResp = false;
}

CompCableCarril::~CompCableCarril() {

}


int CompCableCarril::correr() {
	MtdSala::MetodoSala metodo;

	while (_seguirTrabajando) {
		_enviarResp = false;
		esperarMsj();

		metodo = _ultimoMsj.metodo;

		switch (metodo) {
		case MtdSala::SALA_VACIA: procSalaVacia();
			break;

		case MtdSala::SACAR_PERSONA_COLA: procSacarPersona();
			break;

		case MtdSala::SUBIR_PERSONA: procSubirPersona();
			break;

		case MtdSala::BAJAR_PERSONA: procBajarPersona();
			break;

		case MtdSala::CERRAR: _seguirTrabajando = false;
			break;

		default: SalidaPorPantalla::instancia().error("Metodo NO reconocido");
			mostrarDatos(_ultimoMsj);
			break;
		}

		enviarResp();
	}


	return 0;
}

void CompCableCarril::esperarMsj() {
	_cola.recibir(_ultimoMsj, _idComp);

	if (_ultimoMsj.lugar == LgSala::PIE) {
		_salaActual = &_salaPie;
	}
	else if (_ultimoMsj.lugar == LgSala::CIMA) {
		_salaActual = &_salaCima;
	}
}

void CompCableCarril::enviarResp() {
	if (_enviarResp) {
		_msjResp._mtype = _ultimoMsj._idEmisor;
		_msjResp._idEmisor = _idComp;

		_cola.enviar(_msjResp);
	}
	else {
		SalidaPorPantalla::instancia().error("NO se envio respuesta");
	}
}

void CompCableCarril::procSalaVacia() {
	_msjResp.resultado.booleano = _salaActual->salaVacia();
	_enviarResp = true;
}

void CompCableCarril::procSacarPersona() {
	int numPersona;
	bool res = _salaActual->sacarPersona(numPersona);

	if (res) {
	SalidaPorPantalla::instancia().mostrar("Sacando de la cola persona n°", numPersona);
	liberarPersona(numPersona);
	}
	else {
		SalidaPorPantalla::instancia().error("no se saco persona de la cola");
	}

	_msjResp.numPersona = numPersona;
	_msjResp.resultado.booleano = res;

	_enviarResp = true;
}

void CompCableCarril::procSubirPersona() {
	stMensaje msjPersona;

	// esperando recibir mensaje de persona
	//_cola.recibir(msjPersona, _idComp);
	_colaBlq.recibir(_idComp);

	_enviarResp = true;
}

void CompCableCarril::procBajarPersona() {
	SalidaPorPantalla::instancia().mostrar("Bajando persona n°", _ultimoMsj.numPersona);
	liberarPersona(_ultimoMsj.numPersona);

	_enviarResp = true;
}


void CompCableCarril::liberarPersona(NumeroPersonaSala numPersona) {
	_colaBlq.enviar(IdPersonaComp(numPersona));
}
