/*
 * iPlataformaSacar.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef IPLATAFORMASACAR_H_
#define IPLATAFORMASACAR_H_

class iPlataformaSacar {
public:

	/**
	 * Detecta la frecuencia de un dispositvo en la plataforma, retornando TRUE
	 * si se detecto algun dispositivo encendido en la plataforma.
	 */
	virtual bool detectarFrecuencia() = 0;

	/**
	 *  Intenta sacar un dispositivo activo de la plataforma, retornando TRUE
	 *  si efectivamente lo saco y guardanddo el numero de dispositivo retirado
	 *  en el parametro pasado.
	 */
	virtual bool sacarDispositivo(int& numDispositivo) = 0;

	/**
	 *
	 */
	virtual bool seguirTrabajando() = 0;

	virtual ~iPlataformaSacar(){}
};

#endif /* IPLATAFORMASACAR_H_ */
