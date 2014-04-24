/*
 * ArchConfiguracion.h
 *
 *  Created on: 09/04/2014
 *      Author: migue
 */

#ifndef ARCHCONFIGURACION_H_
#define ARCHCONFIGURACION_H_

#include <string>
#include <fstream>
#include <map>

typedef size_t TamDatoArch;

typedef struct {
	char* ptr;
	TamDatoArch tam;
} metaDato;


typedef std::map<std::string, metaDato> MapaDatos;

typedef std::map<std::string, metaDato>::iterator itMapaDatos;

typedef std::pair<std::string, metaDato> parDatos;

class ArchConfiguracion {
public:
	ArchConfiguracion(bool escritura = false);

	void escribir(const char* etiqueta, const void* datos, size_t tam);

	void escribir(const std::string& etiqueta, const void* datos, size_t tam);

	bool leer(const char* etiqueta, void* datos, size_t tam);

	bool leer(const std::string& etiqueta, void* datos, size_t);

	bool leer(const char* etiqueta, int& valor);

	void guardar(const char* etiqueta, int valor);

	void guardar(const std::string& etiqueta, int valor);

	void serializar();

	const std::string armarEtiqueta(const std::string& snombre, int numero);

	bool lecturaValida();

	virtual ~ArchConfiguracion();
private:

	void levantar();

	std::string _ruta;
	std::fstream _archivo;

	MapaDatos _datos;

	bool _archActualizado;
};

#endif /* ARCHCONFIGURACION_H_ */
