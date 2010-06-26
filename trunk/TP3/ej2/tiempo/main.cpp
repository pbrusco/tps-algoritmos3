#include <iostream>
#include <fstream>
#include <sys/time.h>
#include "grafo.h"


using namespace std;
double resolver();
double timeval_diff(struct timeval& a, struct timeval& b); 	/* retorna "a - b " en microsegundos */


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
	double time = 0.0;
	struct timeval t1, t2;	

	entrada >> n;
	while(n != -1) {
		cout << n << endl;
		g.cargar(entrada,n);
		gettimeofday(&t1,NULL);
		g.maxClique(res);
		gettimeofday(&t2,NULL);
		int dif = timeval_diff(t2, t1);
		time += dif;
		salida << n << '\t' <<  dif << endl;
		res.clear();
		entrada >> n;
	}

	entrada.close();
	salida.close();
	return time;
}



double timeval_diff(struct timeval& a, struct timeval& b) {
  return (a.tv_sec + - b.tv_sec)*1000000 + (a.tv_usec  - b.tv_usec);
}
