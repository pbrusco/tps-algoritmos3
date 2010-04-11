#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cassert>
#include <list>
#include <time.h>

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
	long long x = (p*p)%n;			// resto de dividir a b² por n	

	forn(i, n/2)
		res = (res*x)%n;				// multiplico los n/2 x's al tiempo que tomo módulo n
	
	if (n % 2)
		return (res*p)%n;				// si el número es impar, multiplico por p y tomo módulo n
	
	else
		return res;
}

long long potenciacion2(long long base, long long exp, long long mod) {
	
	long long res = 0;
	
	if (exp == 1)
		return (base % mod);

	else if (exp % 2 == 0) {
		long long temp = potenciacion2(base, exp/2, mod);
		res = (temp*temp) % mod;
	}
	
	else {
		long long temp = potenciacion2(base, (exp-1)/2, mod);
		res = (((temp*temp) % mod) * (base % mod)) % mod;
	}
	
	return res;
}

int main(int argc, char** argv) {

	string filename = "Tp1Ej1.in";
	if (argc = 2) filename = argv[1];

	time_t start, end;
	double tiempo = 0.0;

	ifstream infile; 
	infile.open(filename.c_str()); 
	assert(infile.is_open());
	list<pair<int,int> >* input = cargarDatos(infile);
	infile.close();
	
	ofstream outfile;
	outfile.open("./Tp1Ej1.out");
	assert(outfile.is_open());
		
	list<int> res;

	forall(it, *input) {
		time(&start);
		int temp = potenciacion(it->first, it->second);
//		int temp2 = potenciacion2(it->first, it->second, it->second);	
		time(&end);
		tiempo += difftime(end, start);
		res.push_back(temp);
	}
	
	delete input;
	forall(it, res)
		outfile << *it << endl;

	outfile.close();
	printf ("El algoritmo tardó %.2lf segundos en procesar todos los datos.\n", tiempo );

	return 0;	
}
