/*
 * mainConsumidor.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#include <unistd.h>
#include <stdlib.h>
#include <sstream>

#include "Definiciones.h"
#include "GestorPedidos.h"

/**
 *
 * argv[1] : numero de Consumidor
 *
 */

int main(int argc, char** argv) {
	SalidaPorPantalla* salida = &SalidaPorPantalla::instancia();

	if (argc < 2) {
		salida->mostrar("Se necesita numero de consumidor");
		exit(EXIT_SUCCESS);
	}

	int numConsumidor = atoi(argv[1]);


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


