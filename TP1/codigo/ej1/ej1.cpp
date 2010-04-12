#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <sys/time.h>
#include <cassert>

#define forn(i, n) for(int i = 0; i < n; i++)
#define forall(it, X)	for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;



/*######################################################################################################################
#														Declaración de funciones													   # ######################################################################################################################*/

list<pair<int,int> >* cargarDatos(istream& is);
long long potenciacion(long long base, long long exp, long long mod);
void resolverInput(string& filename);

struct timeval t_i, t_f;


/*######################################################################################################################
#													Implementación de funciones													   # ######################################################################################################################*/

list<pair<int,int> >* cargarDatos(istream& is) {

	list<pair<int,int> >* res = new list<pair<int,int> >();
	int b = 0, n = 0;

	while(is.good()) {
		is >> b;
		is >> n;
		if (b == -1 and n == -1) break;
		res->push_back(make_pair(b,n));
	}
	
	return res;	
}

long long potenciacion(long long base, long long exp, long long mod) {

	long long res = 0;
	
	while (base < 0)
		base += mod;

	base = base % mod;
	if (base == 0) return base;
	
	else if (exp == 1) return base;

	else if (exp % 2 == 0) {
		long long temp = potenciacion(base, exp/2, mod);
		res = (temp*temp) % mod;
	}

	else {
		long long temp = potenciacion(base, (exp-1)/2, mod);
		res = (((temp*temp) % mod) * base) % mod;
	}
	
	return res;
}

void resolverInput(string& filename) {

	time_t start, end;
	double tiempo = 0.0;
	
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
		gettimeofday(&t_i, NULL);
		int temp = potenciacion(it->first, it->second, it->second);
		gettimeofday(&t_f, NULL);
		tiempo += ((t_f.tv_sec - t_i.tv_sec)*1000 + (t_f.tv_usec - t_i.tv_usec)/1000.0);
		res.push_back(temp);
	}

	delete input;

	forall(it, res)
		outfile << *it << endl;

	outfile.close();
	printf ("El algoritmo tardó %.15lf milisegundos en procesar todos los datos.\n", tiempo );
}



/*######################################################################################################################
#														Algoritmo Principal													   		    #
######################################################################################################################*/

int main(int argc, char** argv) {

	string filename = "Tp1Ej1.in";

	if (argc > 1) {
		forn(i, argc-1) {
			filename = argv[i+1];
			resolverInput(filename);
		}
	}

	else
		resolverInput(filename);
		
	return 0;	
}

