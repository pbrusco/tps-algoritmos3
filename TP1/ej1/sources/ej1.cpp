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

/* Variable global para medir la cantidad de operaciónes del algoritmo "potenciación"*/
long long int cantOp = 0;


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
	cantOp++;					// contabilizo la asignación
	
	base = base % mod;
	cantOp++;					// contabilizo el módulo

	if (base == 0) {
		cantOp++;				// contabilizo la comparación del if
		return base;
	}
	
	else if (exp == 1) {
		cantOp += 2;			// contabilizo las comparaciones de los 2 if's
		return base;
	}

	else if (exp % 2 == 0) {
		cantOp += 4;			// contabilizo las comparaciones de los 2 if's anteriores, el módulo y la comparación del if actual
		long long int temp = potenciacion(base, exp/2, mod);
		cantOp ++; 			// contabilizo la asignación
		res = (temp*temp) % mod;
		cantOp += 3;			// contabilizo el producto, el módulo y la asignación
	}

	else {
		cantOp += 4;		// contabilizo las operaciones de la guardas de los if's anteriores
		long long int temp = potenciacion(base, (exp-1)/2, mod);
		cantOp++; 			// contabilizola asignación
		res = (((temp*temp) % mod) * base) % mod; 
		cantOp += 5;		// contabilizo los 3 productos, los 2 módulos y la asignación
	}
	
	return res;
}

void resolverInput(string& filename) {

	/* Acumulador de la cantidad de operaciones necesarias para resolver la totalidad del input*/
	long long int cantOp_tot = 0;

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
	list<pair<long long int, long long int> > grafico;

	/* Calculo la respuesta y cantidad de operaciones que se necesitaron para obtenerla para cada una de las tupla de input*/
	forall(it, *input) {

		/* Reseto la cantidad de operaciones */		
		cantOp = 0;
	
		/* Calculo la respuesta para la tupla (b,n) en la que estoy parado */
		long long int temp = potenciacion(it->first, it->second, it->second);

		/* Sumo la cantidad de operaciones que tardó el algortimo al acumulador total */
		cantOp_tot += cantOp;	
				
		/* Guardo el valor de n y la cantidad de operaciónes que usó para resolver el problema en la lista grafico */
		grafico.push_back(make_pair(it->second, cantOp));
		
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

	printf ("El algoritmo tardó %d operaciones en procesar todos los datos.\n", cantOp_tot );
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

