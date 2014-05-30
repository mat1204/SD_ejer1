/*
 * ColaDirecciones.cpp
 *
 *  Created on: 26/05/2014
 *      Author: migue
 */

#include "ColaDirecciones.h"

typedef struct {
	long _destino;
	stDireccionHost _dir;
} stMsjDir;

#define TAM_MSJ_COLA_DIRS	(sizeof(stMsjDir) - sizeof(long))

ColaDirecciones::ColaDirecciones(bool crear) :
	_colaReal(RUTA_COLA_DIRS, ID_COLA_DIRS, crear)
{

}

ColaDirecciones::~ColaDirecciones() {

}

void ColaDirecciones::destruir() {
	_colaReal.destruir();
}

void ColaDirecciones::enviar(const stDireccionHost& dir,int destino) {
	stMsjDir msj;
	msj._destino = destino;
	memcpy((void*)&msj._dir,(const void*)&dir, sizeof(stDireccionHost));
	_colaReal.enviar((const void*) &msj, sizeof(stMsjDir));
}

void ColaDirecciones::recibir(stDireccionHost& dir, int receptor) {
	stMsjDir msj;
	_colaReal.recibir((void*) &msj, sizeof(stMsjDir), receptor);
	memcpy((void*)&dir, (const void*)&msj._dir, sizeof(stDireccionHost));
}
