/*
 * mainProductor.cpp
 *
 *  Created on: 13/05/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "SalaVirtual.h"

void lanzarPersona(const char* numPersona);


int main(int argc, char** argv) {
	SalidaPorPantalla::instancia().etiqueta("Productor");
	SalidaPorPantalla::instancia().color(FUENTE_AZUL);

	SalaVirtual sP(ID_PRODUCTOR_0, TpAgente::PERSONA, LgSala::PIE);

	iSalaPersona *salaPie = &sP;

	int cantPersonas;

	ArchConfiguracion config;

	config.leer(ET_PERSONAS_PROD, cantPersonas);

	int i = 0;

	SalidaPorPantalla::instancia().mostrar("Cantidad de personas a producir: ", cantPersonas);
	std::stringstream ss;

	while (i < cantPersonas) {
		if (salaPie->hayLugar()) {

			ss.str("");
			ss << i;
			SalidaPorPantalla::instancia().mostrar("Por lanzar persona...");
			lanzarPersona(ss.str().c_str());

			++i;
		}
		else {
			SalidaPorPantalla::instancia().mostrar("Esperando por lugar");
			salaPie->esperarPorLugar();
		}
	}

	return 0;
}


void lanzarPersona(const char* numPersona) {
	int pid;

	pid = fork();

	if (pid == 0) {
		execl("./pers", "Persona" , numPersona, NULL);
		SalidaPorPantalla::instancia().error("No se pudo iniciar proceso Persona.");
		exit(EXIT_FAILURE);
	}
	else {
		SalidaPorPantalla::instancia().mostrar("Persona Lanzada");
	}

}
