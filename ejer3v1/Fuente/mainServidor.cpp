/*
 * mainServidor.cpp
 *
 *  Created on: 21/05/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "ColaDirecciones.h"

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void lanzarAsistidor(const char* skcfd, int numProceso);

void recogerResultadoAsistidor(int) {
	int estado;
	int resWait =  waitpid(0, &estado, WNOHANG);

	if (resWait == -1) {
		SalidaPorPantalla::instancia().error("error al recibir resultado de asistidor");
	}
	else if (resWait == 0) {
		SalidaPorPantalla::instancia().mostrar("no se recibio resultado de ningun asistidor");
	}
	else {
		if (estado == 0) {
			SalidaPorPantalla::instancia().mostrar("Asistidor termino correctamente");
		}
		else {
			SalidaPorPantalla::instancia().mostrar("Asistidor termino con algun ERROR");
		}
	}

}

int main(int argc, char** argv) {

	signal(SIGCHLD, recogerResultadoAsistidor);


	SalidaPorPantalla* sp = &SalidaPorPantalla::instancia();
	sp->etiqueta("Servidor");
	sp->color(FUENTE_ROJO);

	ColaDirecciones colaDirs;

	Socket skcServidor;
	sp->mostrar("Enlanzado... ");
	skcServidor.enlazar(PUERTO_SERVIDOR);

	Socket skcCliente;
	stDireccionHost nuevaDir;

	int numProceso = 1000;

	sp->mostrar("Esperando conexiones");

	for (;;) {

		sp->mostrar("Escuchando conexion...");
		skcCliente = skcServidor.aceptarConexion(nuevaDir._dir);

		if (skcCliente.socketValido()) {

			sp->mostrar("Se acepto una conexion, lanzando proceso Asistidor");

			colaDirs.enviar(nuevaDir, numProceso);
			lanzarAsistidor(skcCliente.descriptorAString(), numProceso);
			sp->mostrar("Proceso asistidor lanzador, fd socket: ", skcCliente.descriptorAString());

			skcCliente.cerrar();

			++numProceso;
		}
		else {
			sp->mostrar("Se rechazo una conexion");
		}
	}

	return 0;
}


void lanzarAsistidor(const char* skcfd, int numProceso) {
	int pid;
	pid = fork();

	std::stringstream ssNumProc;
	ssNumProc << numProceso;

	if (pid == 0) {

		execl("./asist", "asistidor", skcfd, ssNumProc.str().c_str(), NULL);
		SalidaPorPantalla::instancia().error("No se pudo iniciar proceso Asistidor");
		exit(EXIT_FAILURE);

	}

}
