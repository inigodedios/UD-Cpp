/*
 * Persona.cpp
 *
 *  Created on: 2 jun. 2021
 *      Author: aidagomezbuenoberezo
 */

#include "Persona.h"

#include <iostream>
#include <string.h>

using namespace std;

Persona::Persona() {
	this->id = 0;
}

Persona::Persona(int id){
	this->id = id;
}

Persona::Persona(const Persona& p){
	this->id = p.id;
}

void Persona::setId(int id){
	this->id = id;
}

int Persona::getId() const{
	return this->id;
}

void Persona::imprimir(){
	cout << "ID: " << this->id << endl;
//	cout << "[Id: " << this->id << "]" << endl;
}

Persona::~Persona() {
}

