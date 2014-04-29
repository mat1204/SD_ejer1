/*
 * GestorArch.h
 *
 *  Created on: 28/04/2014
 *      Author: migue
 */

#ifndef GESTORARCH_H_
#define GESTORARCH_H_

class GestorArch {
public:
	GestorArch();

	void crearArchivo(const char* ruta);

	void destruiArchivo(const char* ruta);

	virtual ~GestorArch();
};

#endif /* GESTORARCH_H_ */
