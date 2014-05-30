/*
 * mainProdServidor.cpp
 *
 *  Created on: 20/05/2014
 *      Author: migue
 */

/**
 * argv[1] :
 * argv[2] :
 */

#include "Definiciones.h"

void lanzarEmisor(const char* sfdSocket, int numProductor, int numConsmidor);
void lanzarProductorReal(const int numProductor);

int main(int argc, char** argv) {

	SalidaPorPantalla *sp = &SalidaPorPantalla::instancia();
	sp->etiqueta("ProdServidor");
	sp->color(FUENTE_MAGENTA);

	Socket sockServ;

	sp->mostrar("Conectandose al servidor");
	if (sockServ.conectar(NOMBRE_SERVIDOR_IDS, PUERTO_SERVIDOR) != 0) {
		sp->mostrar("No me pude conectar con el servidor");
		return EXIT_FAILURE;
	}
	else {
		sp->mostrar("Me conecte con el servidor");
	}

	stPaquete paq;

	paq._tipo = TpPaquete::IDENTIFICACION;
	paq._datos._id.tipo = TpActor::PRODUCTOR;

	/**
	 * Enviando identificacion
	 */
	sp->mostrar("Enviando identificacion");
	sockServ.enviar((const void*) &paq, sizeof(stPaquete));

	/**
	 * Esperando respuesta de identificacion
	 */
	sp->mostrar("Esperando respuesta de indentificacion");
	sockServ.recibir((void*) &paq, sizeof(paq));

	if (paq._tipo != TpPaquete::IDENTIFICACION) {
		sp->error("Se esperaba mensaje de Identificacion");
		return EXIT_FAILURE;
	}

	int numProd = paq._datos._id.id;
	int idProductor = IdProductor(numProd);

	/**
	 *
	 * lanzando un productor real con el numero de productor obtenido
	 *
	 */
	sp->mostrar("lanzando proceso Productor REAL");
	lanzarProductorReal(numProd);


	ArchConfiguracion config;
	int cantConsumidores;

	config.leer(ET_CANT_CONSUMIDORES, cantConsumidores);

	sp->mostrar("Esperando recibir direcciones de Consumidores");

	Socket sockConexion;

	for (int i = 0; i < cantConsumidores ; ++i) {

		sockServ.recibir((void*) &paq, sizeof(paq));

		if (paq._tipo == TpPaquete::DIRECION_HOST) {
			sp->mostrar("Se recibio direccion de Consumidor, lanzando consumidor");

			sockConexion.conectar(paq._datos._dir._dir, paq._datos._dir.puerto);
			lanzarEmisor(sockConexion.descriptorAString(), numProd, paq._datos._dir.numActor);
			sockConexion.cerrar();
		}
		else {
			sp->error("No se recibio paquete con la direccion de host esperado");
		}

	}

	sockServ.cerrar();

	return 0;
}

void lanzarEmisor(const char* sfdSocket, int numProductor, int numConsumidor) {
	std::stringstream ssNumProd, ssNumCons;
	ssNumProd << numProductor;
	ssNumCons << numConsumidor;

	if (fork() == 0) {
		execl("./emisor", "Emisor", sfdSocket, ssNumProd.str().c_str(), ssNumCons.str().c_str(), NULL);
		SalidaPorPantalla::instancia().error("No se puede iniciar proceso ProductorEmisor");
		exit(EXIT_FAILURE);
	}
}


void lanzarProductorReal(const int numProductor) {
	std::stringstream ss;
	ss << numProductor;

	if (fork() == 0) {
		execl("./prod" , "Productor", ss.str().c_str(), NULL);
		SalidaPorPantalla::instancia().error("No se puede iniciar proceso Consumidor");
		exit(EXIT_FAILURE);
	}
}
