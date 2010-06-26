#include <iostream>
#include <fstream>
#include <cassert>
#include <sys/time.h>
#include "grafo.h"

#define forn(i,n) for(int i=0; i<n; i++)
#define forall(it,X) for(typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)

using namespace std;


int resolverConstructiva(const string& input, const string& output, const string& outDebug);


int main(int argc, char** argv) {
	string input, output,outDebug;
	int time = 0.0;
	
	if (argc == 1) {
		input = "../../in/Tp3.in";
		output = "../../out/3 - CONSTRUCTIVA/Tp3.out";
		outDebug = "Tp3_Operaciones.ej3";
		time = resolverConstructiva(input,output,outDebug);
		cout << "El algortimo demoró " << time << " µseg en resolver las instancias del archivo " << input << endl;
	}
	else {
		forn(i, argc-1) {
			input = argv[i+1];
			int pos = input.rfind('/');
			output = input.substr(pos+1, input.size());
			pos = output.rfind(".in");
			outDebug = output;
			if (pos!=string::npos){
				output.replace(pos,3,".out");
				outDebug = outDebug.substr(0,outDebug.length()-3);
			}
			outDebug = outDebug + "_Operaciones.ej3";
			time = resolverConstructiva(input,output,outDebug);
			//cout << "El algortimo demoró " << time << " µseg en resolver las instancias del archivo " << input << endl;
		}
	}
	return 0;
}


int resolverConstructiva(const string& input, const string& output, const string& outDebug) {
	int n;
	unsigned long long int operaciones;
	Grafo g;
	set<int> res;
	ifstream is;	is.open(input.c_str());		assert(is.is_open());
	ofstream contar;	contar.open(outDebug.c_str());

	is >> n;
	while(n != -1) {
		operaciones = 0;
		g.cargar(is,n);
		g.cliqueConstructivo(res,operaciones);
		contar << n << '\t' << operaciones << endl;
		res.clear();
		is >> n;
	}

	is.close();
	contar.close();
	return 0;
}


