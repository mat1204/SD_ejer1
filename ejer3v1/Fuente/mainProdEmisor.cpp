/*
 * mainProdEmisor.cpp
 *
 *  Created on: 20/05/2014
 *      Author: migue
 */

#include "Definiciones.h"

#include "ColaComponentes.h"

#include <string.h>

/**
 * argv[1]: fd del socket
 *
 * argv[2]: numero del productor
 *
 * argv[3]: numero del consumidor a enviar mensajes
 *
 */
int main(int argc, char** argv){

	if (argc < 4) {
		SalidaPorPantalla::instancia().error("Se debe ingregar fd del socket abierto, numero de productor y numero de consumidor a enviar msjs");
		return EXIT_FAILURE;
	}

	Socket sock(argv[1]);
	int numProd = atoi(argv[2]);
	int numCons = atoi(argv[3]);

	int idProd = IdProductor(numProd);
	int idCons = IdConsumidor(numCons);

	SalidaPorPantalla::instancia().etiqueta("ProdEmisor", numProd);
	SalidaPorPantalla* sp = &SalidaPorPantalla::instancia();

	sp->mostrar("ProdEmisor iniciado");

	ColaComponentes cola;

	stPaquete paq;

	int paqEnviados = 0;

	sp->mostrar("Enviando mensajes");

	while (paqEnviados < 10) {

		cola.recibir(paq._datos._msj, idCons + DESVIO_NUM_PROD);

		paq._datos._msj._mtype -= DESVIO_NUM_PROD;
		paq._tipo = TpPaquete::MENSAJE_COLA;

		sp->mostrar("Por enviar msj con N°pedido ", paq._datos._msj.pedido.num);
		sleep(10);
		sp->mostrar("enviando msj con N°pedido ", paq._datos._msj.pedido.num);
		sock.enviar((void*) &paq, sizeof(paq));

		paqEnviados++;
	}

	return 0;
}
