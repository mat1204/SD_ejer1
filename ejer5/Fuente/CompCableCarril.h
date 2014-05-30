/*
 * CompCableCarril.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef COMPCABLECARRIL_H_
#define COMPCABLECARRIL_H_

#include "Definiciones.h"

#include "Sala.h"
#include "ColaComponentes.h"
#include "ColaBloqueos.h"

class CompCableCarril {
public:
	CompCableCarril(int numCableCarril);

	virtual ~CompCableCarril();

	int correr();

private:

	void esperarMsj();

	void enviarResp();

	void liberarPersona(NumeroPersonaSala numPersona);



	void procSalaVacia();

	void procSacarPersona();

	void procSubirPersona();

	void procBajarPersona();

	stMensaje _ultimoMsj, _msjResp;

	Sala _salaCima, _salaPie;

	Sala *_salaActual;

	ColaComponentes _cola;
	ColaBloqueos _colaBlq;
	int _numCC, _idComp, _idCC;

	bool _seguirTrabajando;
	bool _enviarResp;
};

#endif /* COMPCABLECARRIL_H_ */
