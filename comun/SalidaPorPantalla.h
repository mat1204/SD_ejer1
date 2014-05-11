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



#define FUENTE_ROJO			31
#define FUENTE_AZUL			34
#define FUENTE_VERDE		32
#define FUENTE_CYAN			36
#define FUENTE_AMARILLA		33
#define FUENTE_MAGENTA		35


#define FONDO_NEGRO			40
#define FONDO_BLANCO		47
#define FONDO_AMARILLO		43


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
	void error(const char* msj, const char* msj2);
	void error(const char* msj, int x);

	void agregarAlMsj(int x);
	void agregarAlMsj(const std::string& texto);
	void agregarAlMsj(const char* texto);
	void agregarAlMsj(const char* texto, int x);

	const std::string convertirAString(const float x);

	void mostrarMsj();

	void color(int colorFuente);

	static SalidaPorPantalla& instancia();

private:
	void imprimir();

	void imprimirError();

	SalidaPorPantalla();

	static SalidaPorPantalla _instancia;

	char _buffer[500];
	std::string _identificador;
	int _id;

	bool _esperaTrasImprimir;

	std::stringstream _ss;

	std::string _FILTRO;
	bool _filtrar;

	// para el uso del color
	bool _usarColor;
	int _fuenteColor;
};

#endif /* SALIDAPORPANTALLA_H_ */
