/*
 * iSalaCableCarril.h
 *
 *  Created on: 12/05/2014
 *      Author: migue
 */

#ifndef ISALACABLECARRIL_H_
#define ISALACABLECARRIL_H_

class iSalaCableCarril {
public:

	virtual bool salaVacia() = 0;

	virtual bool sacarPersona(int& numPersona) = 0;

	virtual void subirPersona(const int numPersona) = 0;

	virtual void bajarPersona(const int numPersona) = 0;

	virtual ~iSalaCableCarril() {}
};

#endif /* ISALACABLECARRIL_H_ */
