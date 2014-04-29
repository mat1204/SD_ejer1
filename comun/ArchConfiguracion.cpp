/*
 * ArchConfiguracion.cpp
 *
 *  Created on: 09/04/2014
 *      Author: migue
 */

#include "ArchConfiguracion.h"
#include "SalidaPorPantalla.h"

#include <string.h>
#include <sstream>
#include <stdlib.h>

#define NOMBRE_ARCHIVO "./config.cfg"

ArchConfiguracion::ArchConfiguracion(bool escritura) : _ruta(NOMBRE_ARCHIVO) {

	_archActualizado = true;

	if (escritura) {
		std::string cmd("rm ");
		cmd += NOMBRE_ARCHIVO;
		system(cmd.c_str());

		_archivo.open(_ruta.c_str(), std::fstream::in | std::fstream::out | std::fstream::app | std::fstream::binary);
	}
	else {
		_archivo.open(_ruta.c_str(), std::fstream::in | std::fstream::binary);
		if (_archivo.is_open() == false) {
			SalidaPorPantalla::instancia().error("No se pudo abrir archivo de configuracion");
		}
		else
			levantar();
	}
}


void ArchConfiguracion::escribir(const std::string& etiqueta, const void* datos, size_t tam) {

	metaDato mDato;

	mDato.ptr = new char[tam];
	memcpy((void*)mDato.ptr, datos, tam);
	mDato.tam = tam;

	MapaDatos::iterator it;
	it = _datos.find(etiqueta);

	if (it == _datos.end()) {
		parDatos par(etiqueta, mDato);

		_datos.insert(par);
	}
	else {
		delete[] it->second.ptr;
		it->second = mDato;
	}

	_archActualizado = false;
}

void ArchConfiguracion::escribir(const char* etiqueta, const void* datos, size_t tam) {
	std::string setiqueta(etiqueta);
	escribir(setiqueta, datos,tam);
}

ArchConfiguracion::~ArchConfiguracion() {
	this->serializar();

	if (_archivo.is_open())
		_archivo.close();
}

bool ArchConfiguracion::leer(const char* etiqueta, void* datos, size_t tam) {
	std::string setiqueta(etiqueta);
	return leer(setiqueta, datos, tam);
}

bool ArchConfiguracion::leer(const std::string& etiqueta, void* datos, size_t tam) {

	itMapaDatos it = _datos.find(etiqueta);

	if (it != _datos.end()) {
		if (tam <= it->second.tam) {
			memcpy(datos, (void*) it->second.ptr , tam);
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void ArchConfiguracion::serializar() {

	if (_archActualizado == false) {

		MapaDatos::iterator it;
		it = _datos.begin();

		TamDatoArch tam;
		_archivo.seekp(0, std::ios_base::beg);
		for (; it != _datos.end() ; ++it) {

			tam = it->first.length();
			_archivo.write((char*) &tam ,sizeof(TamDatoArch));
			_archivo.write(it->first.c_str(), it->first.length() );

			_archivo.write((char*) &it->second.tam ,sizeof(TamDatoArch));
			_archivo.write(it->second.ptr , it->second.tam);
		}

		_archivo.flush();

		_archActualizado = true;
	}

}

void ArchConfiguracion::levantar() {
	if (_archivo.is_open()) {

		TamDatoArch longitud;

		std::string etiqueta;
		char _buffer[200];

		char* ptrAux;

		while(_archivo.eof() == false) {
			//leo tamanio de la etiqueta
			_archivo.read((char*)&longitud, sizeof(longitud));

			if (longitud > 0) {

				//leo la etiqueta
				_archivo.read(_buffer, longitud);

				_buffer[longitud] = '\0';

				etiqueta = _buffer;

				// leo tamanio del dato
				_archivo.read((char*)&longitud, sizeof(longitud));
				_archivo.read(_buffer, longitud);

				if (longitud > 0) {
					ptrAux = new char[longitud];
					memcpy(ptrAux, _buffer, longitud);

					metaDato mDato;
					mDato.ptr = ptrAux;
					mDato.tam = longitud;

					parDatos par(etiqueta, mDato);
					_datos.insert(par);
				}
			}

		}
	}
}

bool ArchConfiguracion::leer(const char* etiqueta, int& valor) {
	return leer(etiqueta, &valor, sizeof(int));
}

void ArchConfiguracion::guardar(const char* etiqueta, int valor) {
	escribir(etiqueta, (void *) &valor, sizeof(int));
}

void ArchConfiguracion::guardar(const std::string& etiqueta, int valor) {
	escribir(etiqueta, (void*) &valor, sizeof(int));
}


const std::string ArchConfiguracion::armarEtiqueta(const std::string& snombre, int numero) {
	std::stringstream ss;
	ss << snombre;
	ss << numero;

	return ss.str();
}

bool ArchConfiguracion::lecturaValida() {
	return _archivo.is_open();
}

const char* nombreArchivo() {
	return NOMBRE_ARCHIVO;
}
