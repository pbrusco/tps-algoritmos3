#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <time.h>
#include <cassert>

#define forn(i, n) for(int i = 0; i < n; i++)
#define forall(it, X)	for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;


//*************************************************************** Declaración de funciones **************************************************************

list<pair<int,int> >* cargarDatos(istream& is);
long long potenciacion(long long b, long long n);
long long potenciacion2(long long base, long long exp, long long mod);


//************************************************************* Implementacion de funciones ***********************************************************

list<pair<int,int> >* cargarDatos(istream& is) {

	list<pair<int,int> >* res = new list<pair<int,int> >();
	int b = 0, n = 0;

	while(is.good()) {
		is >> b;
		is >> n;
		if (b != -1 and n != -1)
			res->push_back(make_pair(b,n));			
	}

	return res;	
}

long long potenciacion(long long b, long long n) {
	
	long long res = 1;
	long long p = b%n;				// resto de dividir a b por n
	if (p == 0) return 0;
	
	else {
		long long x = (p*p)%n;			// resto de dividir a b² por n	
	
		forn(i, n/2)
			res = (res*x)%n;				// multiplico los n/2 x's al tiempo que tomo módulo n
	
		if (n % 2)
			return (res*p)%n;				// si el número es impar, multiplico por p y tomo módulo n
	
		else
			return res;
	}
}


//**************************************************************** Algoritmo Principal ********************************************************************

int main(int argc, char** argv) {

	time_t start, end;
	double tiempo = 0.0;

	string filename = "Tp1Ej1.in";
	if (argc == 2) filename = argv[1];
	string filename2 = (filename.substr(0, filename.size()-3) + ".out");	
	
	ifstream infile; 
	infile.open(filename.c_str()); 
	assert(infile.is_open());
	list<pair<int,int> >* input = cargarDatos(infile);
	infile.close();
	
	ofstream outfile;
	outfile.open(filename2.c_str());
	assert(outfile.is_open());
		
	list<int> res;

	forall(it, *input) {
		time(&start);
		int temp = potenciacion(it->first, it->second);
		time(&end);
		tiempo += difftime(end, start);
		res.push_back(temp);
	}
	
	delete input;
	forall(it, res)
		outfile << *it << endl;

	outfile.close();
	printf ("El algoritmo tardó %.15lf segundos en procesar todos los datos.\n", tiempo );

	return 0;	
}
