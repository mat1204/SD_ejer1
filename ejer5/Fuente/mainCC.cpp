/*
 * mainCC.cpp
 *
 *  Created on: 13/05/2014
 *      Author: migue
 */

#include "Definiciones.h"
#include "SalaVirtual.h"
#include <vector>

int main(int argc, char** argv) {

	if (argc != 2 ) {
		SalidaPorPantalla::instancia().error("Se debe ingresar numero de cable carril");
		return EXIT_FAILURE;
	}


	std::stringstream ss;

	ss << argv[1];

	int numCC;

	ss >> numCC;

	SalidaPorPantalla* sal = &SalidaPorPantalla::instancia();

	sal->color(FUENTE_ROJO);
	sal->etiqueta("CableCarril", numCC);

	SalaVirtual sc(numCC, TpAgente::CABLE_CARRIL, LgSala::CIMA);
	SalaVirtual sp(numCC, TpAgente::CABLE_CARRIL, LgSala::PIE);

	iSalaCableCarril *salaPie = &sp, *salaCima = &sc;

	iSalaCableCarril *salaActual;

	std::vector<int> lugares;
	int numPersona;



	std::string sPie("Pie"), sCima("Cima");
	std::string *sSalaProxima, *sSalaActual;

	salaActual = salaCima;
	sSalaProxima = &sPie;
	sSalaActual = &sCima;
	while (true) {


		while (salaActual->salaVacia() == false) {
			if (salaActual->sacarPersona(numPersona)) {
				sal->mostrar("Subiendo persona n°", numPersona);
				salaActual->subirPersona(numPersona);

				sal->agregarAlMsj("Se subio la persona n°");
				sal->agregarAlMsj(numPersona);

				sal->agregarAlMsj(", en la zona del ");
				sal->agregarAlMsj(sSalaActual->c_str());

				sal->mostrarMsj();

				lugares.push_back(numPersona);
			}

		}

		sal->agregarAlMsj("llendo a la zona de \"");
		sal->agregarAlMsj(sSalaProxima->c_str());
		sal->agregarAlMsj("\" de la Montaña con ");
		sal->agregarAlMsj(lugares.size());
		sal->agregarAlMsj(" personas");
		sal->mostrarMsj();

		usleep(TIEMPO_TRABAJO * 3);

		sal->agregarAlMsj("Arrive a la zona de \"");
		sal->agregarAlMsj(sSalaProxima->c_str());
		sal->agregarAlMsj("\" de la Montaña");
		sal->mostrarMsj();

		int i = 0;
		while ( i < lugares.size() ) {
			salaActual->bajarPersona(lugares[i]);
			sal->mostrar("Se bajo persona n°", lugares[i]);
			++i;
		}
		lugares.clear();

		// bajar montaña

		usleep(TIEMPO_TRABAJO);

		if (salaActual == salaPie) {
			salaActual = salaCima;
			sSalaProxima = &sPie;
			sSalaActual = &sCima;
		}
		else if (salaActual == salaCima) {
			salaActual = salaPie;
			sSalaProxima = &sCima;
			sSalaActual = &sPie;
		}

	}

	return 0;
}
