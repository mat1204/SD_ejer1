/*
 * ComponenteRobot.h
 *
 *  Created on: 20/04/2014
 *      Author: migue
 */

#ifndef COMPONENTEROBOT_H_
#define COMPONENTEROBOT_H_

#include "ColaMensajes.h"

#include "Definiciones.h"
#include "ColaComponentes.h"
#include "Plataforma.h"

class ComponenteRobot {
public:
	ComponenteRobot(int numeroDeRobot, MdRobot::ModoRobot tipo);
	virtual ~ComponenteRobot();

	int correr();

private:

	int iniciarParaArmado();

	int iniciarParaFrecuencia();

	void esperarMsj();
	void enviarRespuesta();


	// para robot de frecuencia

	void procDetectarFrecuencia();
	void procSeguirTrabajando();
	void procSacarDispositivo();


	// para robot de armado

	void procPlataformaLlena();
	void procEsperar();
	void procColocarDispositivo();
	void procFinDeArmador();

	bool _seguirTrabajando;

	Plataforma _plataforma;

	MdRobot::ModoRobot _tipo;

	int _numeroRobot;
	int _idRobot;
	int _idComponente;

	MensajeCola _ultimoMsj, _respuesta;
	ColaComponentes _cola;
};

#endif /* COMPONENTEROBOT_H_ */
