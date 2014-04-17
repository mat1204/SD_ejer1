/*
 * GestorPedidos.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: knoppix
 */

#include "GestorPedidos.h"
#include "ArchConfiguracion.h"

#include <unistd.h>
#include <stdlib.h>

#include <string.h>

GestorPedidos::GestorPedidos(int numeroConsumidor) {
	_salida = &SalidaPorPantalla::instancia();

	ArchConfiguracion config;

	if (config.leer(ET_CANT_CONSUMIDORES, _cantConsumidores) == false) {
		_salida->error("Error al leer Cantidad de Consumidores");
		exit(EXIT_FAILURE);
	}

	_numConsumidor = numeroConsumidor;
}

GestorPedidos::~GestorPedidos() {

}

void GestorPedidos::sacarPedido(stPedido& pedido) {
	stMensaje msj;
	_cola.recibir(msj, _numConsumidor);

	memcpy(&pedido, &msj.pedido, TAM_PEDIDO);
}

void GestorPedidos::gestionarPedido(const stPedido& pedido) {
	stMensaje msj;
	memcpy(&msj.pedido, &pedido, TAM_PEDIDO);

	for (int i=0 ; i < _cantConsumidores ; ++i) {
		msj._mtype = i+1;
		_cola.enviar(msj);
	}
}
