/*
 * Usuario.h
 *
 *  Created on: 2 jun. 2021
 *      Author: aidagomezbuenoberezo
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include "Persona.h"

class Usuario: public Persona {
private:
	char* nick;
	char* password;
public:
	Usuario();
	Usuario(int id,char*, char*);
	Usuario(const Usuario&);
	void setNick(const char*);
	char* getNick() const;
	void setPassword(const char*);
	char* getPassword() const;
	void imprimir();
	virtual ~Usuario();
};

#endif /* USUARIO_H_ */
