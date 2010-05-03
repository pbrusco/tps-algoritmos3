#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>//pair
#include <set>
#include <time.h>

#include "carcel.h"

using namespace std;

void generarEntrada(int cantCarceles, ostream& os);
void generarCarcel(int n, ostream& os);
void generarEjes(int n,carcel& c,int porcentaje);
void generarLlaves(int n, carcel& c,int porcentaje);
int numeroAlAzar(int desde, int hasta, int x);
set<pair<int,int> > ejesAlAzar(int desde, int hasta, int cant);
set<pair<int,int> > llavesAlAzar(int desde, int hasta, int cant);
void guardar(carcel& c, ostream& os);

int tiempo = 2;

int main(){

	
	srand(tiempo);

	ofstream os;
	os.open("entrada");

	generarEntrada(100,os);

	os.close();

	

	return 0;
}

void generarEntrada(int cantCarceles, ostream& os){

	int n = 5;
	for(int i = 0; i<cantCarceles; i++){
		generarCarcel(n+i,os);
		tiempo++;
		srand(tiempo);
	}
	os << -1 << " " << -1 << " " << -1;
}


void generarCarcel(int n, ostream& os){

	carcel c(n);
	generarEjes(n,c,50);
	generarLlaves(n,c,40);
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

	int cant = n * porcentaje / 100;
	set<pair<int,int> > llaves = llavesAlAzar(1,n-1,cant);
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
		if(res.count(aux1) == 0){
			res.insert(aux1);
		}
		else{
			res.insert(aux2);
		}
	}
	return res;
}


set<pair<int,int> > llavesAlAzar(int desde, int hasta, int cant){

	int a = numeroAlAzar(desde,hasta,hasta);
	int b = numeroAlAzar(desde,hasta,a);
	pair<int,int> aux1;
	
	set<pair<int,int> > res;
	set<int> habsConLlave,habsConPuerta;

//HACER ALGO PARA QUE ENCUENTRE RAPIDO 2 HABITACIONES DISPONIBLES!!!
	
	for(int i = 0; i<cant; i++){
		while( (habsConLlave.count(a) != 0 || habsConPuerta.count(b) != 0) || (habsConLlave.count(b) != 0 || habsConPuerta.count(a) != 0) ){
			a = numeroAlAzar(desde,hasta,hasta);
			b = numeroAlAzar(desde,hasta,a);
		}
		aux1.first = a;
		aux1.second = b;
		res.insert(aux1);
		habsConLlave.insert(a);
		habsConPuerta.insert(b);
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
