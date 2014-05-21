/*
 * Sala.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef SALA_H_
#define SALA_H_

#include "Definiciones.h"
#include "Mutex.h"
#include "AreaPersonas.h"

class Sala {
public:
	Sala(LgSala::LugarSala lugar);

	void inicializar();
	void destruir();

	bool hayLugar();

	void esperarPorLugar();

	bool salaVacia();

	bool sacarPersona(int& numPersona);

	bool hacerCola(const int numPersona);

	virtual ~Sala();

	void mostrarEstado();

private:
	AreaPersonas *_area;
	Mutex *_mtx;
	Mutex *_semLleno, *_semVacio;

	LgSala::LugarSala _lugar;
};

#endif /* SALA_H_ */
