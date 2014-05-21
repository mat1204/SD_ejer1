/*
 * AreaPersonas.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef AREAPERSONAS_H_
#define AREAPERSONAS_H_

#include "Definiciones.h"

class AreaPersonas {
public:
	AreaPersonas(char id);

	virtual ~AreaPersonas();

	void inicializar();

	void destruir();

	bool hayLugar();

	bool salaVacia();

	bool salaLlena();

	bool hacerCola(const int numPersona);

	bool sacarPersona(int& numPersona);

	int capacidad();

	int esperandoPorLleno(int x = 0, bool asignar = false);

	int esperandoPorVacio(int x = 0, bool asignar = false);

	int lugaresOcupados();


	void mostrarEstado();

private:

	int posSacar(int x = 0, bool asignar = false);
	int posPoner(int x = 0, bool asignar = false);
	int ocupados(int x = 0, bool asignar = false);

	int variable(int pos, int x = 0, bool asignar = false);

	void leerLugar(int pos, NumeroPersonaSala& numPersn);

	void escribirLugar(int pos, const NumeroPersonaSala& numPersn);

	int _posVars, _posLugares;

	MemoriaCompartida* _area;
};

#endif /* AREAPERSONAS_H_ */
