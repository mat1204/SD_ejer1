/*
 * PlataformaReal.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef PLATAFORMAREAL_H_
#define PLATAFORMAREAL_H_

#include "Definiciones.h"
#include "ColaMensajes.h"
#include "SalidaPorPantalla.h"

class PlataformaReal {
public:
	PlataformaReal(int capacidad, int cantRobots);

	virtual ~PlataformaReal();

	int iniciar();

private:

	void esperarMensaje();


	void colocarDispositivo();

	void sacarDispositivo();

	void plataformaLlena();

	void hayDispositivosActivos();

	void detectarFrecuencia();

	void reservarLugar();

	void estadoRobot();

	void modificarRobot();

	void robotsFinalizados();


	void prepararEnvio(int idRobot, int resultado);
	void prepararEnvio(int idRobot, bool resultado);
	
	void mostrarEstadoPlataforma();

	void activarDispositivosAlAzar();

	MensajeCola _ultimoMsjRcv, _msjAEnviar;

	ColaMensajes _cola;

	LugarPlataforma* _lugares;
	int _capacidad;
	int _ocupados;
	int _reservados;
	int _activados;

	int _sacados, _colocados;

	int _cantRobots;

	EstRobotArmar::EstadoRobotArmar* _estadosArmar;
	EstRobotFrec::EstadoRobotFrec* _estadosFrec;

	SalidaPorPantalla* _salida;
};

#endif /* PLATAFORMAREAL_H_ */
