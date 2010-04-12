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

list<pair<long long int, long long int> >* cargarDatos(istream& is);
long long int potenciacion(long long int base, long long int exp, long long int mod);
void resolverInput(string& filename);

struct timeval t_i, t_f;


/*######################################################################################################################
#													Implementación de funciones													   # ######################################################################################################################*/

list<pair<long long int, long long int> >* cargarDatos(istream& is) {

	list<pair<long long int, long long int> >* res = new list<pair<long long int, long long int> >();
	int b = 0, n = 0;

	while(is.good()) {
		is >> b;
		is >> n;
		if (b == -1 and n == -1) break;
		res->push_back(make_pair(b,n));
	}
	
	return res;	
}

long long int potenciacion(long long int base, long long int exp, long long int mod) {

	long long int res = 0;
	
	while (base < 0)
		base += mod;

	base = base % mod;
	if (base == 0) return base;
	
	else if (exp == 1) return base;

	else if (exp % 2 == 0) {
		long long int temp = potenciacion(base, exp/2, mod);
		res = (temp*temp) % mod;
	}

	else {
		long long int temp = potenciacion(base, (exp-1)/2, mod);
		res = (((temp*temp) % mod) * base) % mod;
	}
	
	return res;
}

void resolverInput(string& filename) {

	/* Variables para medir el tiempo */
	double tiempo = 0.0, tiempo_tot = 0.0;
	
	/* Creo el nombre del archivo de salida*/
	string filename2 = (filename.substr(0, filename.size()-3) + ".out");	

	/* Creo el nombre del archivo con los datos necesios para graficar */
	string filename3 = ("./info graficos/" + filename.substr(0, filename.size()-3) + "_grafico.out");

	/* Abro el archivo con los datos de entrada */	
	ifstream infile; 
	infile.open(filename.c_str()); 
	assert(infile.is_open());

	/* Cargo los datos en la lista input */
	list<pair<long long int, long long int> >* input = cargarDatos(infile);

	/* Cierro el archivo de entrada */
	infile.close();

	/* Abro el archivo para guardar las respuestas*/
	ofstream outfile;
	outfile.open(filename2.c_str());
	assert(outfile.is_open());

	/* Abro un archivo para guardar los datos necesarios para graficar */
	ofstream data_grafico;
	data_grafico.open(filename3.c_str());
	assert(data_grafico.is_open());

	/* Lista donde voy a guardar los resultados */
	list<long long int> res;
	
	/* Lista donde voy a guardar los datos necesios para graficar */
	list<pair<long long int, double> > grafico;

	/* Calculo la respuesta y el tiempo que demoró en obtenerla para cada tupla de input*/
	forall(it, *input) {

		/* Mido el tiempo inicial */
		gettimeofday(&t_i, NULL);

		/* Calculo la respuesta para la tupla (b,n) en la que estoy parado */
		long long int temp = potenciacion(it->first, it->second, it->second);

		/* Mido el tiempo final */
		gettimeofday(&t_f, NULL);

		/* Calculo cuánto tardó el algoritmo */
		tiempo = ((t_f.tv_sec - t_i.tv_sec)*1000 + (t_f.tv_usec - t_i.tv_usec)/1000.0);
		
		/* Sumo el tiempo que tardó el algortimo al tiempo total */
		tiempo_tot += tiempo;
		
		/* Guardo el valor de n y el tiempo en que tardó en resolverse el problema en la lista grafico */
		grafico.push_back(make_pair(it->second, tiempo));
		
		/* Guardo el resultado en la lista de respuestas */
		res.push_back(temp);
	}

	delete input;

	forall(it, res)
		outfile << *it << endl;
	
	grafico.sort();
	
	forall(it, grafico)
		data_grafico << it ->first << '\t' << it -> second << endl;
		
	outfile.close();
	data_grafico.close();

	printf ("El algoritmo tardó %.15lf milisegundos en procesar todos los datos.\n", tiempo_tot );
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

