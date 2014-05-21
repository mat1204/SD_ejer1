/*
 * SalidaPorPantalla.cpp
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#include "SalidaPorPantalla.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>

SalidaPorPantalla SalidaPorPantalla::_instancia;

SalidaPorPantalla::SalidaPorPantalla() : _identificador("SIN-ETIQUETA"), _id(-1) {
	_filtrar = false;
	_FILTRO = "PLATAFORMA";
	_esperaTrasImprimir = true;

	_usarColor = false;
	_imprimir = true;

}

SalidaPorPantalla::~SalidaPorPantalla() {
	_esperaTrasImprimir = false;
	mostrar("PROCESO FINALIZADO");
}

SalidaPorPantalla& SalidaPorPantalla::instancia() {
	return _instancia;
}

void SalidaPorPantalla::mostrar(const char* mensaje) {
	if (_imprimir == false)
		return;

	if (_filtrar && _identificador != _FILTRO)
		return;


	if (_usarColor) {
		if (_id != -1)
			sprintf(_buffer, "%c[%d;%dm%s-%i : %s %c[%dm\n\n ", 27, 1, _fuenteColor, _identificador.c_str(), _id, mensaje, 27 ,0);
		else
			sprintf(_buffer, "%c[%d;%dm%s : %s %c[%dm\n\n", 27, 1, _fuenteColor, _identificador.c_str(), mensaje, 27, 0);
	}
	else {
		if (_id != -1)
			sprintf(_buffer, "%s-%i : %s\n\n", _identificador.c_str(), _id, mensaje);
		else
			sprintf(_buffer, "%s : %s\n\n", _identificador.c_str(), mensaje);
	}
	imprimir();

	if (_esperaTrasImprimir)
		sleep(2);
}

void SalidaPorPantalla::mostrar(const std::string& mensaje) {
	this->mostrar(mensaje.c_str());
}

void SalidaPorPantalla::error(const char* msj) {
	if (_id != -1)
		sprintf(_buffer, "*****************************%s-%i : %s\n", _identificador.c_str(), _id, msj);
	else
		sprintf(_buffer, "*****************************%s : %s\n", _identificador.c_str(), msj);

	perror(_buffer);
}

void SalidaPorPantalla::error(const std::string& msj) {
	this->error(msj.c_str());
}

void SalidaPorPantalla::error(const char* msj, int x) {
	_ss << msj;
	_ss << x;
	this->error(_ss.str());
	_ss.str("");
}

void SalidaPorPantalla::error(const char* msj, const char* msj2) {
	_ss << msj;
	_ss << msj2;
	this->error(_ss.str());
	_ss.str("");
}

void SalidaPorPantalla::imprimir() {
	write(fileno(stdout), _buffer, strlen(_buffer));
}

void SalidaPorPantalla::etiqueta(const char* nombre, int numero) {
	_identificador = nombre;
	_id = numero;
}

void SalidaPorPantalla::imprimirError() {
	write(fileno(stderr), _buffer, strlen(_buffer));
}


void SalidaPorPantalla::agregarAlMsj(int x) {
	_ss << x;
}

void SalidaPorPantalla::agregarAlMsj(const std::string& texto) {
	_ss << texto;
}

void SalidaPorPantalla::agregarAlMsj(const char* texto, int x) {
	_ss << texto;
	_ss << x;
}


void SalidaPorPantalla::agregarAlMsj(const char* texto) {
	_ss << texto;
}

void SalidaPorPantalla::mostrarMsj() {
	//_ss << std::endl;
	this->mostrar(_ss.str());
	_ss.str("");
}


void SalidaPorPantalla::mostrar(const char* msj, int x) {
	_ss << msj;
	_ss << x;
	mostrarMsj();
}


void SalidaPorPantalla::mostrar(const char* msj, const char* msj2) {
	_ss << msj;
	_ss << msj2;
	mostrarMsj();
}

const std::string SalidaPorPantalla::convertirAString(const float x) {
	char aux[50];
	sprintf(aux, "%f", x);
	std::string res(aux);
	return res;
}

void SalidaPorPantalla::color(int colorFuente) {
	this->_fuenteColor = colorFuente;

	_usarColor = true;
}

void SalidaPorPantalla::dormirTrasImprimir(bool dormir) {
	_esperaTrasImprimir = dormir;
}

void SalidaPorPantalla::imprimirMensajes(bool imprimir) {
	_imprimir = imprimir;
}
