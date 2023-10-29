/*
 * Persona.h
 *
 *  Created on: 2 jun. 2021
 *      Author: aidagomezbuenoberezo
 */

#ifndef PERSONA_H_
#define PERSONA_H_

class Persona {
private:
	int id;
public:
	Persona();
	Persona(int);
	Persona(const Persona&);
	void setId(int);
	int getId() const;
	virtual void imprimir();
	virtual ~Persona();
};

#endif /* PERSONA_H_ */
