/*
 * iPlataformaPoner.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef IPLATAFORMAPONER_H_
#define IPLATAFORMAPONER_H_

class iPlataformaPoner {
public:

	/**
	 * Pregunta si la plataforma se encuentra llena retornando FALSE si es cierto.
	 * Si la plataforma no se encuentra llena, se intentara reservar lugar si no esta llena,
	 * pero si no se pudo reservar algun lugar se retorna TRUE.
	 */
	virtual bool plataformaLlena() = 0;

	/**
	 * Se espera hasta que se desocupe algun lugar en la plataforma.
	 */
	virtual void esperar() = 0;

	/**
	 * Se intenta colocar un Dispositvo en la plataforma, retornado TRUE si efectivamente
	 * se pudo realizar.
	 */
	virtual bool colocarDispositivo(int numDispositvo) = 0;

	virtual ~iPlataformaPoner() {}

};

#endif /* IPLATAFORMAPONER_H_ */
