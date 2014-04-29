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



GestorArch::GestorArch() {
}

GestorArch::~GestorArch() {
}

void GestorArch::crearArchivo(const char* ruta) {
	if (mknod(ruta, 0660, 0) == -1) {
		SalidaPorPantalla::instancia().error("No se pudo crear archivo con ruta: ", ruta);
	}
}

void GestorArch::destruiArchivo(const char* ruta) {
	std::string cmd("rm ");
	cmd += ruta;

	if (system(cmd.c_str()) == -1) {
		SalidaPorPantalla::instancia().error("No se pudo eliminar archivo con ruta: ", ruta);
	}
}
