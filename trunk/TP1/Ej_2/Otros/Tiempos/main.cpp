#include <iostream>
#include <fstream>
#include "Ronda.h"
#include <sys/time.h>
using namespace std;


int main(){
	ifstream archivo;
	ofstream salida;
	ofstream tiempos;

	archivo.open("entrada");
	salida.open("salida");
	tiempos.open("tiempos");

	Ronda ronda;
	bool res;
	
	
	
	//TIEMPO
		//declaro variables para el tiempo
		struct timeval t1,t2;
		double tiempo;
	//
	
	
	
	int id = 0;
	archivo >> id;
	
	while(id != -1){
		ronda.cargarAmistades(archivo,id);
		
		
		gettimeofday(&t1,NULL);
		res = ronda.resolver();
		gettimeofday(&t2,NULL);
		tiempo = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
		tiempos << id << " " << tiempo << endl;	
		if(res) salida<<"ronda"<<endl;
		else salida <<"no"<<endl;
		archivo >> id;
		cout << id << endl;

	}
	
	salida.close();
	archivo.close();
	tiempos.close();
	return 0;
}
