#include <iostream>
#include <fstream>
#include <sys/time.h>
#include "grafo.h"


using namespace std;
double resolver();


int main(int argc, char** argv) {
	
	resolver();
	return 0;
}

	
double resolver() {
	Grafo g;
	int n;
	set<int> res;
	ifstream entrada;
	entrada.open("tp3.in");
	ofstream salida;
	salida.open("tiempo.out");
	
	entrada >> n;
	while(n != -1) {
		cout << n << endl;
		g.cargar(entrada,n);

		int cantOperaciones = g.maxClique(res);

		salida << n << '\t' <<  cantOperaciones << endl;
		res.clear();
		entrada >> n;
	}

	entrada.close();
	salida.close();
return 0.1;
}



