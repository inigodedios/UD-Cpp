/*
 * Usuario.cpp
 *
 *  Created on: 2 jun. 2021
 *      Author: aidagomezbuenoberezo
 */

#include "Usuario.h"

#include <iostream>
#include <string.h>

using namespace std;


Usuario::Usuario():Persona() {
	this->nick = new char[1];
	this->nick[0] = '\0';
	this->password = new char[1];
	this->password[0] = '\0';
}

Usuario::Usuario(int id, char* n, char* pw):Persona(id){
//	this->setId(111);
    this->nick = new char[strlen(n) + 1];
	strcpy(this->nick, n);
	this->password = new char[strlen(pw) + 1];
	strcpy(this->password, pw);
}

Usuario::Usuario(const Usuario &u){
	this->setId(u.getId());
	this->nick = new char[strlen(u.nick) + 1];
	strcpy(this->nick, u.nick);
	this->password = new char[strlen(u.password) + 1];
	strcpy(this->password, u.password);
}

void Usuario::setNick(const char* n){
    this->nick = new char[strlen(nick) + 1];
    strcpy(this->nick, nick);
}

char* Usuario::getNick() const{
	return this->nick;
}

void Usuario::setPassword(const char* pw){
    this->password = new char[strlen(pw) + 1];
    strcpy(this->password, pw);
}

char* Usuario::getPassword() const{
	return this->password;
}

void Usuario::imprimir(){
	cout << "NICK: " << this->nick << endl;
	cout << "PASSWORD: " << this->password << endl;
}

Usuario::~Usuario() {
	delete[] this->nick;
	delete[] this->password;
}

