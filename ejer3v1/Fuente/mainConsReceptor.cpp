/*
 * mainConsReceptor.cpp
 *
 *  Created on: 26/05/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "ColaComponentes.h"

/**
 * argv[1]: N° de consumidor
 *
 * argv[2]: fd del socket abierto con la conexion
 */

int main(int argc, char** argv) {

	SalidaPorPantalla *sp = &SalidaPorPantalla::instancia();

	sp->etiqueta("ConsReceptor");

	if (argc < 3) {
		sp->error("Se debe ingregar numero de consumidor y fd del socket abierto");
		return EXIT_FAILURE;
	}

	int numConsumidor = atoi(argv[1]);
	Socket sock(argv[2]);

	int idConsumidor = IdConsumidor(numConsumidor);

	stPaquete paq;
	ColaComponentes cola;

	ArchConfiguracion config;
	int cantProd;
	if (config.leer(ET_CANT_PRODUCTORES, cantProd) == false ) {
		cantProd = 0;
	}

	for (int i = 0; i < (10*cantProd) ; ++i) {

		sp->mostrar("Esperando recibir paquete");
		sock.recibir((void*) &paq, sizeof(paq));


		if (paq._tipo == TpPaquete::MENSAJE_COLA) {

			if (paq._datos._msj._mtype == idConsumidor) {
				sp->mostrar("Colocando paquete en la cola, N°pedido ", paq._datos._msj.pedido.num);
				cola.enviar(paq._datos._msj);
			}
			else {
				sp->error("Numero de destino consumidor incorrecto: ", paq._datos._msj._mtype);
			}

		}
		else {
			sp->error("Se recibio un paquete de tipo incorrecto");
		}

	}

	return 0;
}

