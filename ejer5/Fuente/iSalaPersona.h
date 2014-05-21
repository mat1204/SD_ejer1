/*
 * iSalaPersona.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef ISALAPERSONA_H_
#define ISALAPERSONA_H_

class iSalaPersona {
public:

	virtual bool hayLugar() = 0;

	virtual void esperarPorLugar() = 0;

	virtual bool hacerCola(const int numPersona) = 0;

	virtual void subirCableCarril() = 0;

	virtual ~iSalaPersona() {}
};

#endif /* ISALAPERSONA_H_ */
