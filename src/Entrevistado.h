/*
 * Entrevistado.h
 *
 *  Created on: 2 jun. 2021
 *      Author: aidagomezbuenoberezo
 */

#ifndef ENTREVISTADO_H_
#define ENTREVISTADO_H_

#include "Persona.h"

class Entrevistado: public Persona {
private:
	int edad;
public:
	Entrevistado();
	Entrevistado(int,int);
	Entrevistado(const Entrevistado&);
	void setEdad(int);
	int getEdad() const;
	void imprimir();
	virtual ~Entrevistado();
};

#endif /* ENTREVISTADO_H_ */
