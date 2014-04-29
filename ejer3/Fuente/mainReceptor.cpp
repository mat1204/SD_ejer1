/*
 * mainReceptor.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#include <unistd.h>
#include <stdlib.h>
#include <sstream>

#include "SalidaPorPantalla.h"
#include "Definiciones.h"
#include "GestorPedidos.h"

int main(int argc, char** argv) {
	SalidaPorPantalla* salida = &SalidaPorPantalla::instancia();

	if (argc != 2) {
		salida->mostrar("Se necesita numero de consumidor");
		exit(EXIT_SUCCESS);
	}

	int numConsumidor;

	std::stringstream ss;
	ss << argv[1];
	ss >> numConsumidor;

	salida->etiqueta("Consumidor-", numConsumidor);

	GestorPedidos a(numConsumidor);

	iProcesar* cons = &a;

	stPedido pedido;
	while (true) {

		cons->sacarPedido(pedido);

		usleep(TIEMPO_TRABAJO);

		salida->mostrar("Se proceso pedido n°", pedido.num);
	}

	return 0;
}


