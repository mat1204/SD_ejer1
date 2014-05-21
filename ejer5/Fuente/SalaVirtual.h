/*
 * SalaVirtual.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef SALAVIRTUAL_H_
#define SALAVIRTUAL_H_

#include "Definiciones.h"
#include "iSalaCableCarril.h"
#include "iSalaPersona.h"

#include "ColaComponentes.h"

class SalaVirtual : public iSalaCableCarril, public iSalaPersona {
public:
	SalaVirtual(int numero,TpAgente::TipoAgente tipo, LgSala::LugarSala lugar);

	virtual ~SalaVirtual();

	/**
	 * Metodos para la sala de Cable Carril
	 */

	virtual bool salaVacia();

	virtual bool sacarPersona(int& numPersona);

	virtual void subirPersona(const int numPersona);

	virtual void bajarPersona(const int numPersona);


	/**
	 * Metodos para la Sala de Persona
	 */

	virtual bool hayLugar();

	virtual void esperarPorLugar();

	virtual bool hacerCola(const int numPersona);

	virtual void subirCableCarril();

private:

	void enviarYEspRes();

	void iniciarComponente();

	// atributos para la persona

	int _numCC_aSubir;

	// atributos para el cable Carril


	// atributos para ambos
	int _numero, _id, _idComp;
	ColaComponentes _cola;

	TpAgente::TipoAgente _tipo;
	LgSala::LugarSala _lugar;

	stMensaje _msj;

	static bool _compLanzado;
};

#endif /* SALAVIRTUAL_H_ */
