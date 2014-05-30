/*
 * GestorActores.cpp
 *
 *  Created on: 22/05/2014
 *      Author: migue
 */

#include "GestorActores.h"

#define CANT_VARS		4

#define POS_PROD		0
#define POS_CONS		1

#define POS_PROD_ESP	2
#define POS_CONS_ESP	3


typedef struct {
	int var[CANT_VARS];
} Variables;

GestorActores::GestorActores() :
	_mem(RUTA_MEM_COMP, ID_MEM_COMP , tamanioMemoriaComp()),
	_mutex(RUTA_SEMAFOROS,1, ID_SEM_MUTEX),
	_semNvCons(RUTA_SEMAFOROS, 1, ID_SEM_NV_CONS),
	_semNvProd(RUTA_SEMAFOROS, 1, ID_SEM_NV_PROD)
{


}

int GestorActores::tamanioMemoriaComp() {
	ArchConfiguracion config;

	config.leer(ET_CANT_CONSUMIDORES, _cantConsumidores);
	config.leer(ET_CANT_PRODUCTORES, _cantProductores);

	int total;

	total = sizeof(Variables) +	 ( sizeof(stDireccionHost) * ( _cantConsumidores + _cantProductores) );

	_posVars = 0;
	_posDirs = sizeof(Variables);

	_posDirProd = 0;
	_posDirCons = _cantProductores * sizeof(stDireccionHost);

	return total;
}

GestorActores::~GestorActores() {

}

void GestorActores::inicializar() {
	Variables vars;
	for (int i = 0; i < CANT_VARS ; ++i ) {
		vars.var[i] = 0;
	}

	_mem.escribir(_posVars, (void*) &vars, sizeof(vars));

	_mutex.inicializar(1);
	_semNvCons.inicializar(0);
	_semNvProd.inicializar(0);
}

void GestorActores::destruir() {
	_mem.destruir();

	_mutex.destruir();
	_semNvCons.destruir();
	_semNvProd.destruir();
}


void GestorActores::direccionProductor(int numProd, stDireccionHost& dir) {

	waitMutex();

	while (numProd >= productores()) {

		prodEsperando(1);

		signalMutex();

		_semNvProd.wait();

		waitMutex();
	}

	direccion(_posDirProd, numProd, dir);

	signalMutex();
}

void GestorActores::direccionConsumidor(int numCons, stDireccionHost& dir) {

	waitMutex();

	while (numCons >= consumidores()) {

		consEsperando(1);

		signalMutex();

		_semNvCons.wait();

		waitMutex();
	}

	direccion(_posDirCons, numCons, dir);

	signalMutex();
}


int GestorActores::agregarProductor(const stDireccionHost& dirProductor) {
	int nvProd;

	waitMutex();

	// los num de productor son desde 0 en adelante
	nvProd = productores(1) - 1;

	this->guardarDireccion(_posDirProd, nvProd, dirProductor);

	while (prodEsperando() > 0){
		prodEsperando(-1);
		_semNvProd.signal();
	}

	signalMutex();

	return nvProd;
}


int GestorActores::agregarConsumidor(const stDireccionHost& dirConsumidor) {
	int nvCons;

	waitMutex();

	// los num de productor son desde 0 en adelante
	nvCons = consumidores(1) - 1;

	this->guardarDireccion(_posDirCons, nvCons, dirConsumidor);

	while (consEsperando() > 0) {
		consEsperando(-1);
		_semNvCons.signal();
	}

	signalMutex();

	return nvCons;
}



void GestorActores::guardarDireccion(int posTipo, int i, const stDireccionHost& dir) {
	int posicionReal = _posDirs + posTipo + ( i * sizeof(stDireccionHost) );
	_mem.escribir(posicionReal, (const void*)&dir, sizeof(dir));
}

void GestorActores::direccion(int posTipo, int i, stDireccionHost& dir) {
	int posicionReal = _posDirs + posTipo + ( i * sizeof(stDireccionHost) );
	_mem.leer(posicionReal, (void*)&dir, sizeof(dir));
}

int GestorActores::variable(int pos, int x) {
	Variables vars;

	_mem.leer(_posVars, (void*) &vars, sizeof(vars));

	if (x != 0) {
		vars.var[pos] += x;
		_mem.escribir(_posVars, (void*) &vars, sizeof(vars));
	}


	return vars.var[pos];
}

int GestorActores::cantConsumidoresTotales() {
	return _cantConsumidores;
}

int GestorActores::cantProductoresTotales() {
	return _cantProductores;
}

int GestorActores::numProximoConsumidor() {
	waitMutex();

	int res = consumidores();

	signalMutex();

	return res;
}

int GestorActores::productores(int x) {
	return variable(POS_PROD, x);
}
int GestorActores::consumidores(int x) {
	 return variable(POS_CONS, x);
}

int GestorActores::prodEsperando(int x) {
	return variable(POS_PROD_ESP, x);
}

int GestorActores::consEsperando(int x) {
	return variable(POS_CONS_ESP, x);
}


bool GestorActores::faltanProductores() {
	waitMutex();
	bool res = (productores() < _cantProductores);
	signalMutex();

	return res;
}

bool GestorActores::faltanConsumidores() {
	waitMutex();
	bool res = (consumidores() < _cantConsumidores);
	signalMutex();

	return res;
}
