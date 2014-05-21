/*
 * CompPersona.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef COMPPERSONA_H_
#define COMPPERSONA_H_

#include "Definiciones.h"

#include "Sala.h"
#include "ColaComponentes.h"
#include "ColaBloqueos.h"

class CompPersona {
public:

	CompPersona(int numPersona);

	virtual ~CompPersona();

	int correr();

private:

	void esperarMsj();

	void enviarResp();


	void procHayLugar();

	void procEsperarPorLugar();

	void procHacerCola();

	void procSubirCableCarril();

	void esperarACableCarril(int numCableCarril);


	void enviarACC(int numCC);

	int _idComp, _idPersona;

	stMensaje _ultimoMsj, _msjResp;

	Sala _salaPie, _salaCima;
	Sala *_salaActual;

	ColaComponentes _cola;
	ColaBloqueos _colaBlq;

	bool _seguirTrabajando;
	bool _enviarResp;
};

#endif /* COMPPERSONA_H_ */
