/*
 * PlataformaVirtual.h
 *
 *  Created on: 02/04/2014
 *      Author: migue
 */

#ifndef PLATAFORMAVIRTUAL_H_
#define PLATAFORMAVIRTUAL_H_

#include "iPlataformaPoner.h"
#include "iPlataformaSacar.h"

#include "SalidaPorPantalla.h"

#include "SemRobots.h"
#include "ColaMensajes.h"

class PlataformaVirtual: public iPlataformaPoner, public iPlataformaSacar {
public:
	PlataformaVirtual(int cantRobots, int idRobot , int pilas = 0, int dispositivos = 0);
	virtual ~PlataformaVirtual();

	// Para robot de Poner
	virtual bool plataformaLlena();

	virtual void esperar();

	virtual bool colocarDispositivo(int numDispositvo);

	// Robots de Sacar
	virtual bool detectarFrecuencia();

	virtual bool sacarDispositivo(int& numDispositivo);

	virtual bool seguirTrabajando();

private:

	void armarMsj(MensajeCola& msj,int metodo);

	void liberarRobotsArmadores();

	void enviarYEsperar(MensajeCola& msj);


	void esperarPorRobotFrec();

	void esperarPorRobotArmar(EstRobotArmar::EstadoRobotArmar estado);


	int estadoRobotFrec();
	int estadoRobotArmar();

	void estadoRobotFrec(EstRobotFrec::EstadoRobotFrec nvEstado);
	void estadoRobotArmar(EstRobotArmar::EstadoRobotArmar nvEstado);

	void signalArmar();
	void waitArmar();

	void signalFrec();
	void waitFrec();

	bool robotsArmarFinalizados();

	SemRobots _semsArmar, _semsFrec;
	ColaMensajes _colaMsj;

	int _cantRobots;
	int _idRobot;
	int _numRobot;

	SalidaPorPantalla* _salida;

	// Atributos para robot de Armar
	int _cantDispositvos;

	// Atributos para robot de frecuencia
	bool _seguirTrabajando;
	bool _armarFinalizado;
};

#endif /* PLATAFORMAVIRTUAL_H_ */
