/*
 * PlataformaVirtual.h
 *
 *  Created on: 23/04/2014
 *      Author: migue
 */

#ifndef PLATAFORMAVIRTUAL_H_
#define PLATAFORMAVIRTUAL_H_

#include "iPlataformaPoner.h"
#include "iPlataformaSacar.h"
#include "ColaComponentes.h"


class PlataformaVirtual :public iPlataformaPoner, public iPlataformaSacar {
public:
	PlataformaVirtual(int numRobot);

	PlataformaVirtual(int numRobot, int pilas, int disp);

	virtual bool detectarFrecuencia();

	virtual bool sacarDispositivo(int& numDispositivo);

	virtual bool seguirTrabajando();

	virtual bool plataformaLlena();

	virtual void esperar();

	virtual bool colocarDispositivo(int numDispositvo);


	virtual ~PlataformaVirtual();

private:

	void prepararMsj(MtdPlataforma::MetodoPlataforma metodo);
	void enviarYEsperarResp();

	void iniciarComponente();

	int _numRobot;
	int _idRobot;
	int _idComp;
	ColaComponentes _cola;
	MensajeCola _msj;
	int _pilas;
	int _disp;

	MdRobot::ModoRobot _modo;
};

#endif /* PLATAFORMAVIRTUAL_H_ */
