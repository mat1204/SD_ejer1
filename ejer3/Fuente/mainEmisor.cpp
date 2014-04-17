/*
 * mainEmisor.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#include "SalidaPorPantalla.h"
#include "GestorPedidos.h"

int main(int argc, char** argv) {

	SalidaPorPantalla* salida = SalidaPorPantalla::instancia();

	if (argc != 2) {
		salida->mostrar("Se necesita numero de productor");
		exit(EXIT_SUCCESS);
	}

	int numProductor;

	std::stringstream ss;
	ss << argv[1];
	ss >> numProductor;

	iSolicitar* prod = &GestorPedidos();

	int cantPedidos = 10;
	int i = 0;

	stPedido pedido;
	while ( i < cantPedidos) {

		pedido.num = i*100 + 7*i + 3*i;

		salida->mostrar("Ingresando pedido n°", pedido.num);

		prod->gestionarPedido(pedido);

		usleep(TIEMPO_TRABAJO);

		++i;
	}


	return 0;
}

