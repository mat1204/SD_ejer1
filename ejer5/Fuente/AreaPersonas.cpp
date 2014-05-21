/*
 * AreaPersonas.cpp
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#include "AreaPersonas.h"
#include <string.h>

#include <iostream>

using namespace std;

#define CANT_VARS	5

#define POS_PTR_SACAR 	0
#define POS_PTR_PONER	1
#define POS_OCUPADOS	2
#define POS_ESP_LLENO	3
#define POS_ESP_VACIO	4

typedef struct {
	int var[CANT_VARS];
} Variables;


AreaPersonas::AreaPersonas(char id) {
	int totalMem = sizeof(Variables) + sizeof(NumeroPersonaSala) * TAM_SALA_ESP;
	_area = new MemoriaCompartida(RUTA_MEM_COMP, id, totalMem);

	_posVars = 0;
	_posLugares = sizeof(Variables);
}

AreaPersonas::~AreaPersonas() {
	delete _area;
}

void AreaPersonas::inicializar() {
	Variables vars;

	for (int i = 0; i < CANT_VARS; ++i) {
		vars.var[i] = 0;
	}

	_area->escribir(_posVars,(const void*) &vars, sizeof(Variables));
}

void AreaPersonas::destruir() {
	_area->destruir();
}

bool AreaPersonas::hacerCola(const int numPersona) {
	if (ocupados() >= TAM_SALA_ESP)
		return false;

	int posicionPoner = posPoner();

	escribirLugar(posicionPoner, numPersona);

	if (posicionPoner >= (TAM_SALA_ESP - 1)) {
		posPoner(0, true);
	}
	else {
		posPoner(1);
	}

	ocupados(1);

	return true;
}

bool AreaPersonas::sacarPersona(int& numPersona) {
	if (ocupados() <= 0)
		return false;

	int posicionSacar = posSacar();

	leerLugar(posicionSacar, numPersona);


	if (posicionSacar >= (TAM_SALA_ESP - 1) ) {
		posSacar(0, true);
	}
	else {
		posSacar(1);
	}

	ocupados(-1);

	return true;
}


bool AreaPersonas::hayLugar() {
	return (ocupados() < TAM_SALA_ESP);
}

bool AreaPersonas::salaVacia() {
	return (ocupados() == 0);
}


int AreaPersonas::posSacar(int x, bool asignar) {
	return variable(POS_PTR_SACAR, x ,asignar);
}

int AreaPersonas::posPoner(int x, bool asignar) {
	return variable(POS_PTR_PONER, x, asignar);
}

int AreaPersonas::ocupados(int x, bool asignar) {
	return variable(POS_OCUPADOS, x, asignar);
}


int AreaPersonas::variable(int pos, int x, bool asignar) {
	Variables vars;

	_area->leer(_posVars, (void*) &vars, sizeof(Variables));

	if (asignar) {
		vars.var[pos] = x;
		_area->escribir(_posVars, (const void*) &vars, sizeof(Variables));
	}
	else if ( x != 0 ) {
		vars.var[pos] += x;
		_area->escribir(_posVars, (const void*) &vars, sizeof(Variables));
	}

	return vars.var[pos];
}


void AreaPersonas::leerLugar(int pos, NumeroPersonaSala& numPersn ) {
	int posMem = _posLugares + sizeof(NumeroPersonaSala) * pos;
	_area->leer(posMem, (void*) &numPersn, sizeof(NumeroPersonaSala));
}


void AreaPersonas::escribirLugar(int pos, const NumeroPersonaSala& numPersn) {
	int posMem = _posLugares + sizeof(NumeroPersonaSala) * pos;
	_area->escribir(posMem, (void*) &numPersn, sizeof(NumeroPersonaSala));
}

bool AreaPersonas::salaLlena() {
	return (ocupados() == TAM_SALA_ESP);
}

int AreaPersonas::esperandoPorLleno(int x, bool asignar) {
	return variable(POS_ESP_LLENO, x, asignar);
}

int AreaPersonas::esperandoPorVacio(int x, bool asignar) {
	return variable(POS_ESP_VACIO, x, asignar);
}

int AreaPersonas::lugaresOcupados() {
	return ocupados();
}

void AreaPersonas::mostrarEstado() {

	const int posicionSacar = posSacar(), posicionPoner = posPoner();

	cout << endl;

	cout << "Lugares Ocupados: " << ocupados() << endl;
	cout << "Esp por Lleno: " << esperandoPorLleno() << endl;

	//cout << "Esp por Vacio: " << esperandoPorVacio() << endl;

	cout << endl;

	bool mostrar = false;

	bool ordenInvertido = (posicionSacar < posicionPoner);

	for (int i = 0; i < TAM_SALA_ESP ; ++i) {

		if (ordenInvertido) {
			if (i == posicionSacar)
				mostrar = true;

			if (i == posicionPoner)
				mostrar = false;
		}
		else {
			if (i == posicionPoner)
				mostrar = true;

			if (i == posicionSacar)
				mostrar = false;
		}

		NumeroPersonaSala numPer;

		if (mostrar) {
			leerLugar(i, numPer);
			cout << i << "): Persona n°" << numPer;
		}
		else {
			cout << i << "): VACIO";
		}

		if (i == posicionPoner && posicionPoner == posicionSacar) {
			cout << " <<-- ambos Ptrs (sacar y Poner)";
		}
		else if (i == posicionPoner) {
			cout << " <-- ptr Poner";
		}
		else if (i == posicionSacar) {
			cout << " <-- ptr Sacar";
		}

		cout << endl;

	}

	cout << endl;
}
