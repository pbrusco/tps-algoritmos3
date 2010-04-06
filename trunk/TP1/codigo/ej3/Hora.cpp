#include <iostream>
#include <fstream>
#include <cassert>
#include <math.h>
#include "Hora.h"



Hora::Hora(){
	hh = 0;
	mm = 0;
	ss = 0;
}


Hora::Hora(short horas, short minutos, short segundos){
	hh = horas;
	mm = minutos;
	ss = segundos;
}

Hora::Hora(string s){

	hh = (int)((s[0]-'0') * 10) + (int)(s[1] -'0');
	mm = (int)((s[3]-'0') * 10) + (int)(s[4] -'0');
	ss = (int)((s[6]-'0') * 10) + (int)(s[7] -'0');
}


Hora::~Hora(){}

Hora::Hora(const Hora& hora1){

	hh = hora1.horas();
	mm = hora1.minutos();
	ss = hora1.segundos();
}


short Hora::horas() const					{return hh;}


short Hora::minutos() const					{return mm;}


short Hora::segundos() const				{return ss;}


void Hora::setHora(short hora)				{hh = hora;}


void Hora::setMinutos(short min)			{mm = min;}


void Hora::setSegundos(short seg)			{ss = seg;}


Hora& Hora::operator=(const Hora& hora1){
	hh = hora1.horas();
	mm = hora1.minutos();
	ss = hora1.segundos();
	return *this;
}


bool Hora::operator==(const Hora& hora1) const		{return hh == hora1.horas() && mm == hora1.minutos() && ss == hora1.segundos();}


bool Hora::operator<(const Hora& hora1) const{

	return ((hh < hora1.horas()) || (hh == hora1.horas() && mm < hora1.minutos()) 
							     || (hh == hora1.horas() && mm == hora1.minutos() && ss < hora1.segundos()));
}


bool Hora::operator<=(const Hora& hora1) const		{return (*this == hora1 || *this < hora1);}



void Hora::cargarHora(istream& is){
//OJO: Sale inmediatamente luego de cargar los segundos!!


	int n;
	is >> n;	
	setHora(n);

	assert(is.peek() == (int) ':');
	is.ignore(1);
	
	is >> n;
	setMinutos(n);
	
	assert(is.peek() == (int) ':');
	is.ignore(1);

	is >> n;
	setSegundos(n);
}

void Hora::imprimir(ostream& os) const{
	
	if(horas() > 9){
		os << horas();
	}
	else{
		os << '0' << horas();
	}
	
	os << ':';
	
	if(minutos() > 9){
		os << minutos();
	}
	else{
		os << '0' << minutos();
	}
	
	os << ':';
	
	if(segundos() > 9){
		os << segundos();
	}
	else{
		os << '0' << segundos();
	}
	
}


