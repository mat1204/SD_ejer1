/*
 * mainEmisor.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#include "SalidaPorPantalla.h"
#include "GestorPedidos.h"

#include <stdlib.h>

/**
 * argv[1] : numero de productor
 */

int main(int argc, char** argv) {

	SalidaPorPantalla* salida = &SalidaPorPantalla::instancia();

	if (argc != 2) {
		salida->mostrar("Se necesita numero de productor");
		exit(EXIT_SUCCESS);
	}

	int numProductor;

	std::stringstream ss;
	ss << argv[1];
	ss >> numProductor;

	salida->etiqueta("Productor-", numProductor);

	GestorPedidos a;

	iSolicitar* prod = &a;

	int cantPedidos = 10;
	int i = 1;

	stPedido pedido;
	while ( i <= cantPedidos) {

		pedido.num = numProductor*100 + 8*i + 3*i;

		salida->mostrar("Ingresando pedido n°", pedido.num);

		prod->gestionarPedido(pedido);

		usleep(TIEMPO_TRABAJO);

		++i;
	}


	return 0;
}

