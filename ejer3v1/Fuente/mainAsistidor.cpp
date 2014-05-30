/*
 * mainAsistidor.cpp
 *
 *  Created on: 22/05/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "GestorActores.h"
#include "ColaDirecciones.h"

/**
 * argv[1] : string del fd del socket abierto
 *
 * argv[2] : numero de proceso (virtual)
 */

int atenderProductor(Socket& sock, stDireccionHost& dir);
int atenderConsumidor(Socket& sock, stDireccionHost& dir);

int main(int argc, char** argv) {

	SalidaPorPantalla *sp = &SalidaPorPantalla::instancia();
	sp->etiqueta("Asistidor");
	sp->color(FUENTE_VERDE);

	sp->mostrar("File descriptor socket: ", argv[1]);
	Socket sock(argv[1]);
	sp->mostrar("File descriptor socket (int): ", sock.descriptor());


	int numProceso = atoi(argv[2]);

	ColaDirecciones colaDirs;

	stDireccionHost dirExtremo;
	sp->mostrar("Esperando recibir direccion por parte del Servidor");
	colaDirs.recibir(dirExtremo, numProceso);

	stPaquete paq;

	//Recibiendo mensaje de identificacion
	sp->mostrar("Esperando identificacion ... ");
	sock.recibir((void*) &paq, sizeof(stPaquete));

	if (paq._tipo != TpPaquete::IDENTIFICACION) {
		sp->error("Se esperaba mensaje de Identificacion");
		exit(EXIT_FAILURE);
	}

	int retorno;

	// seguir con la autenticacion normal
	if (paq._datos._id.tipo == TpActor::CONSUMIDOR) {
		retorno = atenderConsumidor(sock, dirExtremo);
	}
	else if (paq._datos._id.tipo == TpActor::PRODUCTOR) {
		retorno = atenderProductor(sock, dirExtremo);
	}
	else {
		sp->error("No se reconcio el tipo de actor en la identificacion");
		retorno = EXIT_FAILURE;
	}

	sock.cerrar();

	return retorno;
}

/**
 * Comunicacion
 *
 *  -> envia identificacion
 *
 *  repeitr
 * 		-> direccion de consumidor
 */
int atenderProductor(Socket& sock, stDireccionHost& dirOtroExtremo) {
	SalidaPorPantalla* sp = &SalidaPorPantalla::instancia();
	GestorActores gestor;
	stPaquete paq;

	if (gestor.faltanProductores() == false) {
		sp->mostrar("Ya se registraron todos lo productores");
		sp->mostrar("Finalizando ...");
		return 0;
	}


	int numProd = gestor.agregarProductor(dirOtroExtremo);
	sp->etiqueta("AsistProd", numProd);


	paq._tipo = TpPaquete::IDENTIFICACION;
	paq._datos._id.id = numProd;
	paq._datos._id.tipo = TpActor::PRODUCTOR;

	sp->mostrar("Enviando respuesta de identificacion");
	sock.enviar((void*) &paq, sizeof(stPaquete));

	stDireccionHost dirAEnviar;

	/**
	 * 	enviando direcciones de todos los consumidores al productor
	 */
	for (int i = 0 ; i < gestor.cantConsumidoresTotales() ; ++i) {

		gestor.direccionConsumidor(i, dirAEnviar);

		paq._tipo = TpPaquete::DIRECION_HOST;
		dirAEnviar.puerto = PuertoConsumidor(i);
		dirAEnviar.numActor = i;

		memcpy((void*)& paq._datos._dir, (const void*)&dirAEnviar, sizeof(stDireccionHost));

		sp->mostrar("Enviando direccion del Consumidor");
		sock.enviar((void*) &paq, sizeof(paq));
	}


	return 0;
}


/**
 * Comunicacion
 *
 *  -> enviar de identificacion
 *
 *	-> enviar de parametros de conexion
 *
 *	<- recibir confirmacion de escucha de conexiones por parte del otro extremo
 *
 */
int atenderConsumidor(Socket& sock, stDireccionHost& dirOtroExtremo) {
	SalidaPorPantalla* sp = &SalidaPorPantalla::instancia();
	GestorActores gestor;
	stPaquete paq;

	int numCons = gestor.numProximoConsumidor();

	paq._tipo = TpPaquete::IDENTIFICACION;
	paq._datos._id.id = numCons;
	paq._datos._id.tipo = TpActor::CONSUMIDOR;

	sp->etiqueta("AsistConsumidor", numCons);

	if (gestor.faltanConsumidores() == false) {
		sp->mostrar("Ya se registraron todos los Consumidores");
		sp->mostrar("Finalizando ...");
		return 0;
	}

	sp->mostrar("Enviando respuesta de identificacion");
	sock.enviar((void*) &paq, sizeof(stPaquete));


	paq._tipo = TpPaquete::DIRECION_HOST;
	paq._datos._dir.puerto = PuertoConsumidor(numCons);

	sp->mostrar("Enviando datos de conexion");
	sock.enviar((void*) &paq, sizeof(paq));

	// recibir confirmacion de consumidor de que ya esta escuchando conexciones
	sock.recibir((void*) &paq, sizeof(paq));
	sp->mostrar("Confirmacion de Consumidor en espera de conexiones.");

	gestor.agregarConsumidor(dirOtroExtremo);

	sock.cerrar();
	return 0;
}
