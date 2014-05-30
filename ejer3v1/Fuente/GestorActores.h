/*
 * GestorActores.h
 *
 *  Created on: 22/05/2014
 *      Author: migue
 */

#ifndef GESTORACTORES_H_
#define GESTORACTORES_H_

#include "Definiciones.h"

class GestorActores {
public:
	GestorActores();
	virtual ~GestorActores();

	void inicializar();
	void destruir();

	/**
	 * retorna el numero del nuevo productor
	 */
	int agregarProductor(const stDireccionHost& dirProductor);

	/**
	 * retorna el numero del nuevo consumidor
	 */
	int agregarConsumidor(const stDireccionHost& dirConsumidor);

	int cantProductoresTotales();

	int cantConsumidoresTotales();

	int numProximoConsumidor();

	void direccionProductor(int numProd, stDireccionHost& dir);

	void direccionConsumidor(int numCons, stDireccionHost& dir);

	bool faltanProductores();

	bool faltanConsumidores();

private:
	Semaforo _mutex, _semNvProd, _semNvCons;

	void waitMutex() { _mutex.wait(); }
	void signalMutex() { _mutex.signal(); }

	int tamanioMemoriaComp();

	MemoriaCompartida _mem;

	int productores(int x = 0);
	int consumidores(int x = 0);

	int variable(int pos, int x);

	int _cantProductores, _cantConsumidores;

	int prodEsperando(int x = 0);
	int consEsperando(int x = 0);

	void direccion(int posTipo, int i, stDireccionHost& dir);
	void guardarDireccion(int posTipo, int i,const stDireccionHost& dir);

	int _posVars;
	int _posDirs;

	int _posDirProd, _posDirCons;
};

#endif /* GESTORACTORES_H_ */
