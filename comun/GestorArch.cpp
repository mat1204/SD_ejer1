/*
 * GestorArch.cpp
 *
 *  Created on: 28/04/2014
 *      Author: migue
 */

#include "GestorArch.h"
#include "SalidaPorPantalla.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <errno.h>

extern int errno;

GestorArch::GestorArch() {
	SalidaPorPantalla::instancia().dormirTrasImprimir(false);

}

GestorArch::~GestorArch() {
	SalidaPorPantalla::instancia().dormirTrasImprimir(true);
}

void GestorArch::crearArchivo(const char* ruta) {
	if (mknod(ruta, 0660, 0) == -1) {

		if (errno == EEXIST) {
			SalidaPorPantalla::instancia().error("Ya existe archivo con la ruta: ", ruta);
		}
		else {
			SalidaPorPantalla::instancia().error("No se pudo crear archivo con ruta: ", ruta);
			exit(EXIT_FAILURE);
		}

	}
	else {
		SalidaPorPantalla::instancia().mostrar("Se creo el archivo: ", ruta);
	}

}

void GestorArch::destruirArchivo(const char* ruta) {

	std::string cmd("rm ");
	cmd += ruta;

	if (system(cmd.c_str()) == -1) {
		SalidaPorPantalla::instancia().error("No se pudo eliminar archivo con ruta: ", ruta);
	}
	else {
		SalidaPorPantalla::instancia().mostrar("Se elimino el archivo: ", ruta);
	}
}
