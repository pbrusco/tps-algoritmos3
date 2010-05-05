#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;


int numeroAlAzar(int desde, int hasta, int x);




int main(){
	ofstream salida;
	salida.open("Tp2Ej1.in");
	
	for(int tamSecuencia = 1;tamSecuencia < 250;tamSecuencia++){
		salida << tamSecuencia << " ";
		for(int j = 0;j<tamSecuencia;j++){		
			salida << numeroAlAzar(-1000000, 1000000, 0) <<" ";			
		}
		salida << endl;
	}
		
	salida << -1;

	salida.close();
	return 0;
}


int numeroAlAzar(int desde, int hasta, int x){

	int a = x;
	while(a == x){
		a = (rand() % (hasta-desde)) + desde;
	}

	return a;
}

