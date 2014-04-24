/*
 * SalidaPorPantalla.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef SALIDAPORPANTALLA_H_
#define SALIDAPORPANTALLA_H_

#include <string>
#include <sstream>

class SalidaPorPantalla {
public:
	virtual ~SalidaPorPantalla();

	void etiqueta(const char* etiqueta, int numero = -1);

	void mostrar(const char* mensaje);

	void mostrar(const std::string& mensaje);

	void mostrar(const char* msj, int x);

	void mostrar(const char* msj, const char* msj2);

	void error(const std::string& msj);
	void error(const char* msj);
	void error(const char* msj, int x);

	void agregarAlMsj(int x);
	void agregarAlMsj(const std::string& texto);
	void agregarAlMsj(const char* texto);
	void agregarAlMsj(const char* texto, int x);

	void mostrarMsj();

	static SalidaPorPantalla& instancia();

private:

	void imprimir();

	void imprimirError();

	SalidaPorPantalla();

	static SalidaPorPantalla _instancia;

	char _buffer[500];
	std::string _identificador;
	int _id;

	std::stringstream _ss;

	std::string _FILTRO;
	bool _filtrar;
};

#endif /* SALIDAPORPANTALLA_H_ */
