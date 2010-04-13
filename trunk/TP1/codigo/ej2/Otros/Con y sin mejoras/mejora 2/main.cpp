#include <iostream>
#include <fstream>
#include "Ronda.h"

using namespace std;


int main(){
	ifstream archivo;
	ofstream salida;
	archivo.open("entrada");
	salida.open("salida");
	Ronda ronda;
	bool res;
	
	int id = 0;
	archivo >> id;
	
	while(id != -1){
		ronda.cargarAmistades(archivo,id);
		res = ronda.resolver();
		if(res) salida<<"ronda"<<endl;
		else salida <<"no"<<endl;
		archivo >> id;
	}
	
	salida.close();
	archivo.close();
	return 0;
}
