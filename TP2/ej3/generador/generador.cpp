#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>//pair
#include <set>
#include <time.h>

#include "../carcel.h"

using namespace std;

void generarEntrada(int cantCarceles, ostream& os, int pe, int pl);
void generarCarcel(int n, ostream& os, int pe, int pl);
void generarEjes(int n,carcel& c,int porcentaje);
void generarLlaves(int n, carcel& c,int porcentaje);
int numeroAlAzar(int desde, int hasta, int x);
set<pair<int,int> > ejesAlAzar(int desde, int hasta, int cant);
set<pair<int,int> > llavesAlAzar(int desde, int hasta, int cant);
void guardar(carcel& c, ostream& os);



int main(){

	srand(time(NULL));

	ofstream os;
	os.open("entrada");

	generarEntrada(100,os,30/* %ejes */,40/* %llaves */);

	os.close();

	

	return 0;
}

void generarEntrada(int cantCarceles, ostream& os, int pe, int pl){

	int n = 5;
	for(int i = 0; i<cantCarceles; i++){
		generarCarcel(n+i,os,pe,pl);
	}
	os << -1 << " " << -1 << " " << -1 << endl << endl;
	os << pe << "% " << "ejes" << endl;
	os << pl << "% " << "llaves" << endl;
	
}


void generarCarcel(int n, ostream& os, int pe, int pl){
	carcel c(n);
	generarEjes(n,c,pe);
	generarLlaves(n,c,pl);
	guardar(c,os);
}

void generarEjes(int n,carcel& c,int porcentaje){

	int cant = ((n*(n-1))/2) * porcentaje / 100;
	set<pair<int,int> > ejes = ejesAlAzar(0,n,cant);
	set<pair<int,int> >::iterator it;
	
	for(it = ejes.begin();it != ejes.end();it++){
		(*(c.pasillos))[it->first][it->second] = true;
		(*(c.pasillos))[it->second][it->first] = true;
	}
}


void generarLlaves(int n, carcel& c,int porcentaje){

	int cant = (n/2) * porcentaje / 100;
	set<pair<int,int> > llaves = llavesAlAzar(1,n-2,cant);
	set<pair<int,int> >::iterator it;

	for(it = llaves.begin();it != llaves.end();it++){
		(*(c.llaves))[it->first] = it->second;
		(*(c.puertas))[it->second] = true;
	}
}

int numeroAlAzar(int desde, int hasta, int x){

	int a = x;
	while(a == x){
		a = (rand() % (hasta-desde)) + desde;
	}

	return a;
}

set<pair<int,int> > ejesAlAzar(int desde, int hasta, int cant){

	int a = numeroAlAzar(desde,hasta,hasta);
	int b = numeroAlAzar(desde,hasta,a);
	pair<int,int> aux1(a,b);
	pair<int,int> aux2(b,a);
	
	set<pair<int,int> > res;
	
	for(int i = 0; i<cant; i++){
		while(res.count(aux1) != 0 || res.count(aux2) != 0){
			a = numeroAlAzar(desde,hasta,hasta);
			b = numeroAlAzar(desde,hasta,a);
			aux1.first = a;
			aux1.second = b;
			aux2.first = b;
			aux2.second = a;
		}
		res.insert(aux1);
	}
	return res;
}


set<pair<int,int> > llavesAlAzar(int desde, int hasta, int cant){

	int a;
	pair<int,int> aux1;
	
	set<pair<int,int> > res;
	set<int> habitaciones;
	set<int>::iterator it;

	for(int i = 1; i <= hasta ; i++){
		habitaciones.insert(i);
	}

	while(res.size() < cant){
		it = habitaciones.begin();
		a = numeroAlAzar(0,habitaciones.size(),habitaciones.size());
		for(int i = 1;i<a;i++){
			it++;
		}
		aux1.first = *it;
		habitaciones.erase(*it);

		it = habitaciones.begin();
		a = numeroAlAzar(0,habitaciones.size(),habitaciones.size());
		for(int i = 1;i<a;i++){
			it++;
		}
		aux1.second = *it;
		habitaciones.erase(*it);
		res.insert(aux1);		
	}


	return res;
}



void guardar(carcel& c, ostream& os){

	os << c.cantHabitaciones << " ";
	int p=0,m=0;
	//calculo p
	for(int i = 0 ; i < c.cantHabitaciones ; i++){
		if(c.tienePuerta(i)){
			p++;
		}
	}
	//calculo m
	for(int i = 0 ; i < c.cantHabitaciones ; i++){
		for(int j = i+1 ; j < c.cantHabitaciones ; j++){
			if(c.sonAdyacentes(i,j)){
				m++;
			}
		}
	}

	os << p << " " << m << endl;

	//guardo habitaciones con la info de llaves y puertas
	for(int i = 0 ; i < c.cantHabitaciones ; i++){
		if(c.tieneLlave(i)){
			os  << "  " << i+1 << " " << c.dameLlave(i)+1 << endl;
		}
	}

	//guardo ejes
	for(int i = 0 ; i < c.cantHabitaciones ; i++){
		for(int j = i+1 ; j < c.cantHabitaciones ; j++){
			if((*(c.pasillos))[i][j]){
				os << "    " << i+1 << " " << j+1 << endl;
			}
		}
	}

}
