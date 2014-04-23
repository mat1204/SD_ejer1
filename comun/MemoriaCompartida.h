/*
 * MemoriaCompartida.h
 *
 *  Created on: 20/04/2014
 *      Author: migue
 */

#ifndef MEMORIACOMPARTIDA_H_
#define MEMORIACOMPARTIDA_H_

#include "SalidaPorPantalla.h"

class MemoriaCompartida {
public:
	MemoriaCompartida(const char* ruta, char id, int tamanio);

	void leer(int posicion, void* dato, int tamDato) const;
	void escribir(int posicion, void* dato, int tamDato);

	void inicializar();

	void destruir();

	int tamanio() const;

	virtual ~MemoriaCompartida();
private:

	int _idMemoria;
	int _tamanio;

	SalidaPorPantalla *_salida;
	char* _memoria;
};

#endif /* MEMORIACOMPARTIDA_H_ */
