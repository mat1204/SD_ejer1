/*
 * mainConsReceptor.cpp
 *
 *  Created on: 20/05/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "ColaComponentes.h"

#include <string.h>

/**
 *
 *  No recibe argumentos
 *
 */


#include "Definiciones.h"

void lanzarReceptor(const char* sfd, int numConsumidor);

void lanzarConsumidorReal(int numConsumidor);


int main(int argc, char** argv) {

	SalidaPorPantalla* sp = &SalidaPorPantalla::instancia();
	sp->etiqueta("ConsumidorServ");
	sp->color(FUENTE_AZUL);

	ArchConfiguracion config;
	int cantProd;

	config.leer(ET_CANT_PRODUCTORES, cantProd);


	Socket sockServ, sockRecepcion;

	if (sockServ.conectar(NOMBRE_SERVIDOR_IDS, PUERTO_SERVIDOR) != 0 ) {
		sp->error("No se pudo conectar con servidor");
		return EXIT_FAILURE;
	}
	else {
		sp->mostrar("Me conecte con el servidor");
	}

	stPaquete paq;

	paq._tipo = TpPaquete::IDENTIFICACION;
	paq._datos._id.tipo = TpActor::CONSUMIDOR;

	/**
	 * Enviando Paquete de identificacion
	 */
	sp->mostrar("Enviando mensaje de identificacion al servidor");
	sockServ.enviar((void*) &paq, sizeof(paq));

	/**
	 * Esperando respuesta de identificacion
	 */
	sp->mostrar("Esperando respuesta de identificacion del servidor");
	sockServ.recibir((void*) &paq, sizeof(paq));

	if (paq._tipo != TpPaquete::IDENTIFICACION) {
		sp->error("No se recibio el paquete de identificacion esperado");
		exit(EXIT_FAILURE);
	}

	int numConsumidor = paq._datos._id.id;


	/**
	 *
	 * Lanzado Consumidor Real
	 *
	 */
	sp->mostrar("Lanzado proceso Consumidor REAL");
	lanzarConsumidorReal(numConsumidor);


	/**
	 * Esperando recibir parametros de conexion de repcepcion
	 */
	sp->mostrar("esperando recibir parametros de conexion");
	sockServ.recibir((void*) &paq, sizeof(paq));

	if (paq._tipo != TpPaquete::DIRECION_HOST) {
		sp->error("No se recibio paquete de Dirrecion de host");
		exit(EXIT_FAILURE);
	}

	int puertoDeEscucha = paq._datos._dir.puerto;

	sp->mostrar("Preparandome para recibir conexiones");
	sockRecepcion.enlazar(puertoDeEscucha, 10);

	// Enviado paquete vacio, solo para confirmar que consumidor esta escuchado
	sp->mostrar("Confirmando al servidor que esto eschando conexciones");
	sockServ.enviar((void*) &paq, sizeof(paq));

	Socket sockCli;

	sp->mostrar("Escuchando conexiones...");
	int i = 0;
	while ( i < cantProd) {

		sockCli = sockRecepcion.aceptarConexion();

		if (sockCli.socketValido()) {
			sp->mostrar("Se establecio una conexion");
			lanzarReceptor(sockCli.descriptorAString(), numConsumidor);
			sockCli.cerrar();
			++i;
		}
		else {
			sp->error("No se pudo establecer una sockServconexion, pero sigo escuchando");
		}

	}

	sockRecepcion.cerrar();

	return 0;
}

void lanzarReceptor(const char* sfd, int numConsumidor) {

	int pid;
	std::stringstream ss;

	ss << numConsumidor;

	pid = fork();

	if (pid == 0) {
		execl("./recep","ConsReceptor",  ss.str().c_str(), sfd, NULL);
		SalidaPorPantalla::instancia().error("Error al iniciar proceso Receptor");
		exit(EXIT_FAILURE);
	}

}

void lanzarConsumidorReal(int numConsumidor) {
	std::stringstream ss;

	ss << numConsumidor;

	if (fork() == 0) {
		execl("./cons", "Consumidor", ss.str().c_str(), NULL);
		SalidaPorPantalla::instancia().error("Error al iniciar proceso Consumidor");
		exit(EXIT_FAILURE);
	}
}

