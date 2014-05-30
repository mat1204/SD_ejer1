/*
 * mainPersona.cpp
 *
 *  Created on: 13/05/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "SalaVirtual.h"

#include <iostream>

int tiempoDePaseo();

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "Se debe ingresar el numero de persona" << std::endl;
		return 0;
	}


	int numPersona;
	std::stringstream ss;

	ss << argv[1];
	ss >> numPersona;

	SalidaPorPantalla *sal = &SalidaPorPantalla::instancia();

	sal->etiqueta("Persona", numPersona);
	sal->color(FUENTE_VERDE);


	SalaVirtual sP(numPersona, TpAgente::PERSONA, LgSala::PIE);
	SalaVirtual sC(numPersona, TpAgente::PERSONA, LgSala::CIMA);

	iSalaPersona *salaPie = &sP, *salaCima = &sC;

	sal->mostrar("Llegando para realizar paseo por la Montaña");
	usleep(FRANDOM * TIEMPO_TRABAJO );

	sal->mostrar("Haciendo cola al Pie de la Montaña");
	salaPie->hacerCola(numPersona);

	// subiendo al cable carril
	usleep(TIEMPO_TRABAJO + FRANDOM * TIEMPO_TRABAJO );

	sal->mostrar("Subiendo al cable carril para ir a la Cima");
	salaPie->subirCableCarril();


	sal->mostrar("Realizando paseo...");
	usleep(tiempoDePaseo());
	sal->mostrar("Paseo Finalizado");

	while (salaCima->hayLugar() == false) {
		sal->mostrar("Esperando por lugar en la Cima.");
		salaCima->esperarPorLugar();
	}

	sal->mostrar("Haciendo cola en la Cima de la Montaña");
	salaCima->hacerCola(numPersona);

	// subiendo al cable carril
	usleep(TIEMPO_TRABAJO / 5 + FRANDOM * TIEMPO_TRABAJO);

	sal->mostrar("Subiendo cable carril para ir al Pie de la montaña.");
	salaCima->subirCableCarril();

	// Persona se va...

	return 0;
}

#define LIM_INF		TIEMPO_TRABAJO
#define LIM_SUP		(10 * TIEMPO_TRABAJO)



int tiempoDePaseo() {

	int res = LIM_INF + (LIM_SUP - LIM_INF) * FRANDOM;

	return res;
}
