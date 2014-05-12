/*
 * SalaVirtual.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef SALAVIRTUAL_H_
#define SALAVIRTUAL_H_

#include "iSalaCableCarril.h"
#include "iSalaPersona.h"

class SalaVirtual : public iSalaCableCarril, public iSalaPersona {
public:
	SalaVirtual(int numPersona);

	virtual ~SalaVirtual();
};

#endif /* SALAVIRTUAL_H_ */
