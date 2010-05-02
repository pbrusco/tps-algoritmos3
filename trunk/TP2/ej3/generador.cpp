#include <iostream>
#include <pair>
#include <set>
#include <rand>
#include <time.h>

#include "carcel.h"

using namespace std;

void generarEntrada(int cantCarceles, ostream& os);
void generarCarcel(int n, ostream& os);
void generarEjes(int n,carcel& c,int porcentaje);
void generarLlaves(int n, carcel& c,int porcentaje);
int numeroAlAzar(int desde, int hasta, int x);
set<pair<int,int> > paresAlAzar(int desde, int hasta, int cant);

int main(){

	srand(time(NULL));

	return 0;
}

void generarEntrada(int cantCarceles, ostream& os){

	int n = 10;
	for(int i = 0; i<cantCarceles; i++){
		generarCarcel(n,os);
	}
}


void generarCarcel(int n, ostream& os){

	carcel c(n);
	generarEjes(n,c);
	generarLlaves(n,c);
	guardar(c,os);
}

void generarEjes(int n,carcel& c,int porcentaje){

	int cant = n * porcentaje / 100;
	set<pair<int,int> > ejes = paresAlAzar(0,n,cant);
	set<pair<int,int> >::iterator it;
	for(it = ejes.begin();it != ejes.end();it++){
		(c->pasillos)[(*it).first()][(*it).second()] = true;
		(c->pasillos)[(*it).second()][(*it).first()] = true;
	}
}


void generarLlaves(int n, carcel& c,int porcentaje){

	int cant = n * porcentaje / 100;
	set<pair<int,int> > ejes = paresAlAzar(0,n,cant);
	set<pair<int,int> >::iterator it;
	for(it = ejes.begin();it != ejes.end();it++){
		(c->llaves)[(*it).first()] = (*it).second();
		(c->puertas)[(*it).second()] = true;
	}
}

int numeroAlAzar(int desde, int hasta, int x){

	int a = x;

	while(a == x){
		a = (rand() % (hasta-desde)) + desde;	
	}

	return a;
}

set<pair<int,int> > paresAlAzar(int desde, int hasta, int cant){

	int a = numeroAlAzar(desde,hasta,hasta);
	int b = numeroAlAzar(desde,hasta,a);
	pair<int,int> aux1(a,b);
	pair<int,int> aux2(b,a);
	
	set<pair<int,int> > res;
	
	for(int i = 0; i<cant; i++){
		while(res.count(aux1) != 0 || res.count(aux2) != 0){
			a = numeroAlAzar(desde,hasta,hasta);
			b = numeroAlAzar(desde,hasta,a);
			aux1(a,b);
			aux2(b,a);
		}
		if(res.count(aux1) == 0) res.insert(aux1);
		else res.insert(aux2);
	}
	
	return res;
}